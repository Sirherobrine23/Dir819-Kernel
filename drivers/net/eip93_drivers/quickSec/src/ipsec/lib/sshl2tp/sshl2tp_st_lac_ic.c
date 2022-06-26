/*
 *
 * sshl2tp_st_lac_ic.c
 *
 * Author: Markku Rossi <mtr@ssh.fi>
 *
*  Copyright:
*          Copyright (c) 2002, 2003 SFNT Finland Oy.
 *               All rights reserved.
 *
 * LAC incoming call establishment.
 *
 */

#include "sshincludes.h"
#include "sshl2tp_internal.h"

#define SSH_DEBUG_MODULE "SshL2tpStLacIc"

/******************************** FSM states ********************************/

#define SSH_L2TP_DATA           \
  SshL2tp l2tp = fsm_context;   \
  SshL2tpSession session = thread_context


SSH_FSM_STEP(ssh_l2tp_fsm_lac_ic_idle)
{
  /* We could do something here but our initiator (at the C level) has
     already ordered a tunnel establishment.  Let's just wait for the
     tunnel. */
  SSH_FSM_SET_NEXT(ssh_l2tp_fsm_lac_ic_wait_tunnel);
  return SSH_FSM_CONTINUE;
}

SSH_FSM_STEP(ssh_l2tp_fsm_lac_ic_wait_tunnel)
{
  SSH_L2TP_DATA;

  /* Wait the tunnel to open. */
  if (!session->tunnel->established)
    SSH_FSM_CONDITION_WAIT(session->tunnel->condition);

  /* Send ICRQ. */
  ssh_l2tp_send(l2tp, NULL, session->tunnel, session, SSH_L2TP_CTRL_MSG_ICRQ);

  SSH_FSM_SET_NEXT(ssh_l2tp_fsm_lac_ic_wait_reply);

  return SSH_FSM_CONTINUE;
}

SSH_FSM_STEP(ssh_l2tp_fsm_lac_ic_wait_reply)
{
  SshL2tpControlMessage message;
  SSH_L2TP_DATA;

  /* Wait for message. */
  if (session->message_queue.head == NULL)
    SSH_FSM_CONDITION_WAIT(session->message_queue_cond);

  message = ssh_l2tp_message(&session->message_queue);

  if (message->type == SSH_L2TP_CTRL_MSG_ICRP)
    {
      /* Update our session. */
      session->info.remote_id = message->assigned_session_id;

      /* Message handled. */
      ssh_l2tp_message_handled(l2tp, thread, &session->message_queue);

      /* Send ICCN. */
      ssh_l2tp_send(l2tp, NULL, session->tunnel, session,
                    SSH_L2TP_CTRL_MSG_ICCN);

      /* The session is established.  Let's notify our user. */

      session->established = 1;

      ssh_operation_unregister(session->initiator_handle);
      session->initiator_handle = NULL;

      if (session->initiator_status_cb)
        (*session->initiator_status_cb)(&session->info,
                                        SSH_L2TP_SESSION_OPENED,
                                        session->initiator_status_cb_context);

      /* Move to the established state. */
      SSH_FSM_SET_NEXT(ssh_l2tp_fsm_session_established);
      return SSH_FSM_CONTINUE;
    }

  if (message->type != SSH_L2TP_CTRL_MSG_CDN
      && message->type != SSH_L2TP_CTRL_MSG_ICCN)
    {
      /* Send CDN. */
      SSH_L2TP_SET_STATUS(l2tp, SSH_L2TP_SESSION_RESULT_ADMINISTRATIVE, 0,
                          NULL, 0);
      SSH_L2TP_COPY_STATUS(&session->info, l2tp);
      ssh_l2tp_send(l2tp, NULL, session->tunnel, session,
                    SSH_L2TP_CTRL_MSG_CDN);
    }

  /* ACK everything. */
  ssh_l2tp_zlb(l2tp, session->tunnel);

  /* Store the possible status and error codes. */
  if (message->type == SSH_L2TP_CTRL_MSG_STOPCCN
      || message->type == SSH_L2TP_CTRL_MSG_CDN)
    {
      SSH_L2TP_COPY_STATUS(&session->info, message);
      SSH_L2TP_COPY_Q931_STATUS(&session->info, message);
    }

  /* Message handled. */
  ssh_l2tp_message_handled(l2tp, thread, &session->message_queue);

  /* And clean up this session. */
  SSH_FSM_SET_NEXT(ssh_l2tp_fsm_session_clean_up);

  return SSH_FSM_CONTINUE;
}
