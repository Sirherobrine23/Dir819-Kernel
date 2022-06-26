/*
 *
 * sshaudit_tables.c
 *
 * Author: Markku Rossi <mtr@ssh.fi>
 *
 *  Copyright:
 *          Copyright (c) 2002, 2003 SFNT Finland Oy.
 *               All rights reserved.
 *
 * Keyword tables to give printable names for audit events.
 *
 */

#include "sshincludes.h"
#include "sshaudit.h"

/* Mapping from SshAuditEvent to their names. */
const SshKeywordStruct ssh_audit_event_names[] =
{
  { "AH_ICV_FAILURE", SSH_AUDIT_AH_ICV_FAILURE },
  { "AH_IP_FRAGMENT", SSH_AUDIT_AH_IP_FRAGMENT },
  { "AH_SA_LOOKUP_FAILURE", SSH_AUDIT_AH_SA_LOOKUP_FAILURE },
  { "AH_SEQUENCE_NUMBER_FAILURE", SSH_AUDIT_AH_SEQUENCE_NUMBER_FAILURE },
  { "AH_SEQUENCE_NUMBER_OVERFLOW", SSH_AUDIT_AH_SEQUENCE_NUMBER_OVERFLOW },
  { "AUDIT_FLOOD",    SSH_AUDIT_FLOOD },
  { "AUDIT_RESOURCE_FAILURE",    SSH_AUDIT_RESOURCE_FAILURE },
  { "CIFS-OPERATION",     SSH_AUDIT_CIFS_OPERATION },
  { "CIFS-SESSION START", SSH_AUDIT_CIFS_SESSION_START },
  { "CIFS-SESSION STOP",  SSH_AUDIT_CIFS_SESSION_STOP },
  { "CORRUPT_PACKET", SSH_AUDIT_CORRUPT_PACKET },
  { "ENGINE_SESSION_END", SSH_AUDIT_ENGINE_SESSION_END },
  { "ENGINE_SESSION_START", SSH_AUDIT_ENGINE_SESSION_START },
  { "ESP_ICV_FAILURE", SSH_AUDIT_ESP_ICV_FAILURE },
  { "ESP_IP_FRAGMENT", SSH_AUDIT_ESP_IP_FRAGMENT },
  { "ESP_SA_LOOKUP_FAILURE", SSH_AUDIT_ESP_SA_LOOKUP_FAILURE },
  { "ESP_SEQUENCE_NUMBER_FAILURE", SSH_AUDIT_ESP_SEQUENCE_NUMBER_FAILURE },
  { "ESP_SEQUENCE_NUMBER_OVERFLOW", SSH_AUDIT_ESP_SEQUENCE_NUMBER_OVERFLOW },
  { "HTTP_REQUEST",   SSH_AUDIT_HTTP_REQUEST },
  { "IKE_BAD_PROPOSAL_SYNTAX", SSH_AUDIT_IKE_BAD_PROPOSAL_SYNTAX },
  { "IKE_CERTIFICATE_TYPE_UNSUPPORTED",
    SSH_AUDIT_IKE_CERTIFICATE_TYPE_UNSUPPORTED },
  { "IKE_CERTIFICATE_UNAVAILABLE", SSH_AUDIT_IKE_CERTIFICATE_UNAVAILABLE },
  { "IKE_DELETE_PAYLOAD_RECEIVED", SSH_AUDIT_IKE_DELETE_PAYLOAD_RECEIVED },
  { "IKE_INVALID_ATTRIBUTES", SSH_AUDIT_IKE_INVALID_ATTRIBUTES },
  { "IKE_INVALID_CERTIFICATE", SSH_AUDIT_IKE_INVALID_CERTIFICATE },
  { "IKE_INVALID_CERTIFICATE_AUTHORITY",
    SSH_AUDIT_IKE_INVALID_CERTIFICATE_AUTHORITY },
  { "IKE_INVALID_CERTIFICATE_TYPE", SSH_AUDIT_IKE_INVALID_CERTIFICATE_TYPE },
  { "IKE_INVALID_COOKIE", SSH_AUDIT_IKE_INVALID_COOKIE },
  { "IKE_INVALID_DOI", SSH_AUDIT_IKE_INVALID_DOI },
  { "IKE_INVALID_EXCHANGE_TYPE", SSH_AUDIT_IKE_INVALID_EXCHANGE_TYPE },
  { "IKE_INVALID_FLAGS", SSH_AUDIT_IKE_INVALID_FLAGS },
  { "IKE_INVALID_HASH_INFORMATION", SSH_AUDIT_IKE_INVALID_HASH_INFORMATION },
  { "IKE_INVALID_HASH_VALUE", SSH_AUDIT_IKE_INVALID_HASH_VALUE },
  { "IKE_INVALID_ID_INFORMATION", SSH_AUDIT_IKE_INVALID_ID_INFORMATION },
  { "IKE_INVALID_VERSION", SSH_AUDIT_IKE_INVALID_VERSION },
  { "IKE_INVALID_KEY_INFORMATION", SSH_AUDIT_IKE_INVALID_KEY_INFORMATION },
  { "IKE_INVALID_MESSAGE_ID", SSH_AUDIT_IKE_INVALID_MESSAGE_ID },
  { "IKE_INVALID_MESSAGE_TYPE", SSH_AUDIT_IKE_INVALID_MESSAGE_TYPE },
  { "IKE_INVALID_NEXT_PAYLOAD", SSH_AUDIT_IKE_INVALID_NEXT_PAYLOAD },
  { "IKE_INVALID_PROPOSAL", SSH_AUDIT_IKE_INVALID_PROPOSAL },
  { "IKE_INVALID_PROTOCOL_ID", SSH_AUDIT_IKE_INVALID_PROTOCOL_ID },
  { "IKE_INVALID_RESERVED_FIELD", SSH_AUDIT_IKE_INVALID_RESERVED_FIELD },
  { "IKE_INVALID_SIGNATURE_INFORMATION",
    SSH_AUDIT_IKE_INVALID_SIGNATURE_INFORMATION },
  { "IKE_INVALID_SIGNATURE_VALUE", SSH_AUDIT_IKE_INVALID_SIGNATURE_VALUE },
  { "IKE_INVALID_SITUATION", SSH_AUDIT_IKE_INVALID_SITUATION },
  { "IKE_INVALID_SPI", SSH_AUDIT_IKE_INVALID_SPI },
  { "IKE_INVALID_TRANSFORM", SSH_AUDIT_IKE_INVALID_TRANSFORM },
  { "IKE_INVALID_TRANSFORM_TYPE", SSH_AUDIT_IKE_INVALID_TRANSFORM_TYPE },
  { "IKE_NOTIFICATION_PAYLOAD_RECEIVED",
    SSH_AUDIT_IKE_NOTIFICATION_PAYLOAD_RECEIVED },
  { "IKE_RETRY_LIMIT_REACHED", SSH_AUDIT_IKE_RETRY_LIMIT_REACHED },
  { "IKE_UNEQUAL_PAYLOAD_LENGTHS", SSH_AUDIT_IKE_UNEQUAL_PAYLOAD_LENGTHS },
  { "IKE_INVALID_TRANSFORM_TYPE", SSH_AUDIT_IKE_INVALID_TRANSFORM_TYPE },
  { "IKE_INVALID_TRAFFIC_SELECTORS", SSH_AUDIT_IKE_INVALID_TRAFFIC_SELECTORS },
  { "IKE_INVALID_AUTHETICATION_METHOD", 
    SSH_AUDIT_IKE_INVALID_AUTHETICATION_METHOD },
  { "IKE_BAD_PAYLOAD_SYNTAX", SSH_AUDIT_IKE_BAD_PAYLOAD_SYNTAX }, 
  { "IKE_INVALID_KEY_TYPE", SSH_AUDIT_IKE_INVALID_KEY_TYPE },
  { "IKE_PACKET_INVALID_PORT", SSH_AUDIT_IKE_PACKET_INVALID_PORT },
  { "IKE_UNSUPPORTED_CRITICAL_PAYLOAD",
    SSH_AUDIT_IKE_UNSUPPORTED_CRITICAL_PAYLOAD },
 
 { "NEW_CONFIGURATION", SSH_AUDIT_NEW_CONFIGURATION },
  { "NOTICE",           SSH_AUDIT_NOTICE },
  { "PM_ESP_NULL_NULL_NEGOTIATION", SSH_AUDIT_PM_ESP_NULL_NULL_NEGOTIATION },
  { "PROTOCOL_ERROR",   SSH_AUDIT_PROTOCOL_PARSE_ERROR },
  { "RULE_MATCH",       SSH_AUDIT_RULE_MATCH },
  { "SESSION_END",      SSH_AUDIT_APPGW_SESSION_END},
  { "SESSION_START",    SSH_AUDIT_APPGW_SESSION_START},
  { "WARNING",          SSH_AUDIT_WARNING},
  { "FTP_IP_CHANGE",    SSH_AUDIT_FTP_IP_CHANGE},
  { "CHECKSUM_COVERAGE_FIELD_INVALID",
    SSH_AUDIT_CHECKSUM_COVERAGE_FIELD_INVALID},
  {"HARDWARE_ACCELERATOR_INITIALIZED", 
   SSH_AUDIT_HWACCEL_INITIALIZED},
  { "HARDWARE_ACCELERATOR_INITIALIZATION_FAILED",
    SSH_AUDIT_HWACCEL_INITIALIZATION_FAILED},
  { NULL, 0 },
};