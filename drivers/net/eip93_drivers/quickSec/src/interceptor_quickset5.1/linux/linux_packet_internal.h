/*

  linux_packet_internal.h

  Copyright:
        Copyright (c) 2002 - 2006 SFNT Finland Oy.
  	All rights reserved

*/

#ifndef LINUX_PACKET_INTERNAL_H
#define LINUX_PACKET_INTERNAL_H

#include "kernel_includes.h"

/* Internal packet structure, used to encapsulate the kernel structure
   for the generic packet processing engine. */

typedef struct SshInterceptorInternalPacketRec 
{
  /* Generic packet structure */
  struct SshInterceptorPacketRec packet;

  /* Backpointer to interceptor */
  SshInterceptor interceptor;

  /* Kernel skb structure. */
  struct sk_buff *skb;

  /* The processor from which this packet was allocated from the freelist */
  unsigned int cpu;

  size_t iteration_offset;
  size_t iteration_bytes;

  /* These are SshUInt32's for export/import */
  SshUInt32 original_ifnum;

  SshUInt16 borrowed : 1; /* From spare resource, free after use */
} *SshInterceptorInternalPacket;


/* Typical needed tailroom: ESP trailer (worstcase ~27B).
   Typical needed headroom: media, IPIP, ESP (~60B for IPv4, ~80B for IPv6)
   Worstcase headroom:      media, UDP(8), NAT-T(12), IPIP(~20), ESP(22)  */

/* The amount of headroom reserved for network interface processing. The 
   interceptor ensures that all packets passed to NIC driver will have atleast
   this much headroom. */
#ifndef SSH_IPSEC_IP_ONLY_INTERCEPTOR
/* With media level interceptor the SSH_INTERCEPTOR_PACKET_HARD_HEAD_ROOM
   includes the media header length. Let us use up the full skb if necessary. 
   This is important for reducing overhead in the forwarding case. */
#define SSH_INTERCEPTOR_PACKET_HARD_HEAD_ROOM 0
#else
/* Ensure that packet has always enough headroom for an aligned 
   ethernet header. */
#define SSH_INTERCEPTOR_PACKET_HARD_HEAD_ROOM 16
#endif /* !SSH_IPSEC_IP_ONLY_INTERCEPTOR */

#ifdef SSH_IPSEC_HWACCEL_CONFIGURED
/* Amount of head- and tailroom to reserve when allocating or duplicating
   a packet. These values are optimised for IPsec processing. */
#define SSH_INTERCEPTOR_PACKET_HEAD_ROOM \
  (SSH_INTERCEPTOR_PACKET_HARD_HEAD_ROOM+128)
#define SSH_INTERCEPTOR_PACKET_TAIL_ROOM (128)

/* Some hw accelerators require DMA memory. */
#define SSH_LINUX_ALLOC_SKB_GFP_MASK   (GFP_ATOMIC | GFP_DMA)

#else /* !SSH_IPSEC_HWACCEL_CONFIGURED */

/* Amount of head- and tailroom to reserve when allocating or duplicating
   a packet. These values are optimised for IPsec processing. */
#define SSH_INTERCEPTOR_PACKET_HEAD_ROOM      (80)
#define SSH_INTERCEPTOR_PACKET_TAIL_ROOM      (30)

#define SSH_LINUX_ALLOC_SKB_GFP_MASK (GFP_ATOMIC)
#endif /* SSH_IPSEC_HWACCEL_CONFIGURED */

#endif /* LINUX_PACKET_INTERNAL_H */
