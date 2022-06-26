/*
 * This is a module which is used for logging packets.
 */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/skbuff.h>
#include <linux/if_arp.h>
#include <linux/ip.h>
#include <net/icmp.h>
#include <net/udp.h>
#include <net/tcp.h>
#include <net/route.h>

#include <linux/netfilter.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_ipv4/ipt_LOG.h>
#include <net/netfilter/nf_log.h>
#include <linux/ctype.h>


static int accessSrcIPaddr = 0;


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Xtables: IPv4 packet logging to syslog");

/* Modify by kuagnsuwen, use scrlog_printk instead printk to record system event */
#if defined (CONFIG_TBS_PRINTK_LOG_FUNC)
extern int scrlog_printk(const char *fmt, ...);
#define printk scrlog_printk
#endif


#if 0
#define MYDEBUG(fmt, args...) printk("%s:%4d %20s: " fmt, __FILE__, __LINE__, __func__, ##args);
#else
#define MYDEBUG(fmt, args...)
#endif


#if 0
int strnicmp(const char * cs,const char * ct,size_t count)
{
	register signed char __res = 0;

	while (count)
	{
		if ((__res = toupper( *cs ) - toupper( *ct++ ) ) != 0 || !*cs++)
		{
			break;
		}
		count--;
	}
	return __res;
}
#endif
static char *strnistr(const char *s, const char *find, size_t slen)
{
	char c, sc;
	size_t len;


	if ((c = *find++) != '\0') 
	{
		len = strlen(find);
		do
		{
			do
			{
      				if (slen < 1 || (sc = *s) == '\0')
				{
      					return (NULL);
				}
      				--slen;
      				++s;
      			}
			while ( toupper(sc) != toupper(c));
      			
			if (len > slen)
			{
      				return (NULL);
			}
      		}
		while (strnicmp(s, find, len) != 0);
      		
		s--;
      	}
      	return ((char *)s);
}

static int http_match(const unsigned char* packet_data, int packet_length)
{
	int test = 0; 
	unsigned char *ipaddr = NULL;
	//scrlog_printk(KERN_EXTRA_WARNING"[2][2] http_match=%d\n",__LINE__); 

	/* first test if we're dealing with a web page request */
	if(strnicmp((char*)packet_data, "GET ", 4) == 0 || strnicmp(  (char*)packet_data, "POST ", 5) == 0 || strnicmp((char*)packet_data, "HEAD ", 5) == 0)
	{
		MYDEBUG("found a  web page request\n"); 
		char path[625] = "";
		char host[625] = "";
		int path_start_index;
		int path_end_index;
		int last_header_index;
		char last_two_buf[2];
		int end_found;
		char* host_match;
		char* test_prefixes[6];
		int prefix_index;
	//scrlog_printk(KERN_EXTRA_WARNING"[2][2] http_match=%d\n",__LINE__); 
		/* get path portion of URL */
		path_start_index = (int)(strstr((char*)packet_data, " ") - (char*)packet_data);
		while( packet_data[path_start_index] == ' ')
		{
			path_start_index++;
		}
		path_end_index= (int)(strstr( (char*)(packet_data+path_start_index), " ") -  (char*)packet_data);
		if(path_end_index > 0) 
		{
			int path_length = path_end_index-path_start_index;
			path_length = path_length < 625 ? path_length : 624; /* prevent overflow */
			memcpy(path, packet_data+path_start_index, path_length);
			path[ path_length] = '\0';
		}
		
		/* get header length */
		last_header_index = 2;
		memcpy(last_two_buf,(char*)packet_data, 2);
		end_found = 0;
		while(end_found == 0 && last_header_index < packet_length)
		{
			char next = (char)packet_data[last_header_index];
			if(next == '\n')
			{
				end_found = last_two_buf[1] == '\n' || (last_two_buf[0] == '\n' && last_two_buf[1] == '\r') ? 1 : 0;
			}
			if(end_found == 0)
			{
				last_two_buf[0] = last_two_buf[1];
				last_two_buf[1] = next;
				last_header_index++;
			}
		}
		//scrlog_printk(KERN_EXTRA_WARNING"[2][2] http_match=%d\n",__LINE__); 
		/* get host portion of URL */
		host_match = strnistr( (char*)packet_data, "Host:", last_header_index);
		if(host_match != NULL)
		{
			int host_end_index;
			host_match = host_match + 5; /* character after "Host:" */
			while(host_match[0] == ' ')
			{
				host_match = host_match+1;
			}
			
			host_end_index = 0;
			while(	host_match[host_end_index] != '\n' && 
				host_match[host_end_index] != '\r' && 
				host_match[host_end_index] != ' ' && 
				host_match[host_end_index] != ':' && 
				((char*)host_match - (char*)packet_data)+host_end_index < last_header_index 
				)
			{
				host_end_index++;
			}
			memcpy(host, host_match, host_end_index);
			host_end_index = host_end_index < 625 ? host_end_index : 624; /* prevent overflow */
			host[host_end_index] = '\0';

			
		}
	
		 MYDEBUG("host = \"%s\", path =\"%s\"\n", host, path); 
		 unsigned char *ipaddr = NULL;
		 ipaddr = (unsigned char *)(&(accessSrcIPaddr)); 
		 scrlog_printk(KERN_EXTRA_WARNING"[2][2] Wb site access host=%s from %d.%d.%d.%d.\n",host,ipaddr[0],ipaddr[1],ipaddr[2],ipaddr[3]); 
		 //scrlog_printk(KERN_EXTRA_WARNING"[2][2] path=%s\n",path); 
	}
	//scrlog_printk(KERN_EXTRA_WARNING"[2][2] http_match=%d\n",__LINE__); 

	return test;
}



static bool match(const struct sk_buff *skb)
{
    int test = 0;
	struct iphdr* iph = NULL;

	
	//scrlog_printk(KERN_EXTRA_WARNING"[2][2] match=%d\n",__LINE__); 

	/* linearize skb if necessary */
	struct sk_buff *linear_skb;
	int skb_copied;
	if(skb_is_nonlinear(skb))
	{
		linear_skb = skb_copy(skb, GFP_ATOMIC);
		skb_copied = 1;
	}
	else
	{
		linear_skb = (struct sk_buff*)skb;
		skb_copied = 0;
	}

	

	/* ignore packets that are not TCP */
	/* ignore packets that are not TCP */
	iph = (struct iphdr*)(skb_network_header(skb));
		
	accessSrcIPaddr = (iph->saddr);
	//scrlog_printk(KERN_EXTRA_WARNING"[2][2] match=%d iph->protocol= 0x%x iph->saddr=0x%x\n",__LINE__,iph->protocol,iph->saddr); 

	if(iph->protocol == IPPROTO_TCP)
	{
		/* get payload */
		struct tcphdr* tcp_hdr		= (struct tcphdr*)( ((unsigned char*)iph) + (iph->ihl*4) );
		unsigned short payload_offset 	= (tcp_hdr->doff*4) + (iph->ihl*4);
		unsigned char* payload 		= ((unsigned char*)iph) + payload_offset;
		unsigned short payload_length	= ntohs(iph->tot_len) - payload_offset;
		//scrlog_printk(KERN_EXTRA_WARNING"[2][2] match=%d payload_offset=%d\n",__LINE__,payload_offset); 
		//scrlog_printk(KERN_EXTRA_WARNING"[2][2] match=%d ntohs(iph->tot_len)=%d\n",__LINE__,ntohs(iph->tot_len)); 

	
	//scrlog_printk(KERN_EXTRA_WARNING"[2][2] match=%d iph->protocol= 0x%x payload_length=%d\n",__LINE__,iph->protocol,payload_length); 

		/* if payload length <= 10 bytes don't bother doing a check, otherwise check for match */
		if(payload_length > 10)
		{
		    //scrlog_printk(KERN_EXTRA_WARNING"[2][2] match=%d\n",__LINE__); 
			test = http_match(payload, payload_length);
		}
	}
	
	/* free skb if we made a copy to linearize it */
	if(skb_copied == 1)
	{
		kfree_skb(linear_skb);
	}


	 MYDEBUG("returning %d from weburl\n\n\n", test); 
	return test;
}



/* Use lock to serialize, so printks don't overlap */
static DEFINE_SPINLOCK(log_lock);

/* One level of recursion won't kill us */
static void dump_packet(const struct nf_loginfo *info,
			const struct sk_buff *skb,
			unsigned int iphoff,
			const char *prefix)
{
	struct iphdr _iph;
	const struct iphdr *ih;
	unsigned int logflags;

	struct net_device *dev = skb->dev;
	
	if (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;
	else
		logflags = NF_LOG_MASK;

	ih = skb_header_pointer(skb, iphoff, sizeof(_iph), &_iph);
	if (ih == NULL) {
		printk("TRUNCATED");
		return;
	}

	/* Important fields:
	 * TOS, len, DF/MF, fragment offset, TTL, src, dst, options. */
	/* Max length: 40 "SRC=255.255.255.255 DST=255.255.255.255 " */
	printk("SRC=%pI4 DST=%pI4 ",
	       &ih->saddr, &ih->daddr);

	/* Max length: 46 "LEN=65535 TOS=0xFF PREC=0xFF TTL=255 ID=65535 " */
	printk("LEN=%u TOS=0x%02X PREC=0x%02X TTL=%u ID=%u ",
	       ntohs(ih->tot_len), ih->tos & IPTOS_TOS_MASK,
	       ih->tos & IPTOS_PREC_MASK, ih->ttl, ntohs(ih->id));


	switch (dev->type) 
	{
		case ARPHRD_ETHER:
			if(net_ratelimit())
			{
                 scrlog_printk(KERN_EXTRA_WARNING"[2][2] %s SRC=%pI4 DST=%pI4 MACSRC=%pM MACDST=%pM MACPROTO=%04x \n",
			 	    prefix, &ih->saddr, &ih->daddr,eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest,ntohs(eth_hdr(skb)->h_proto));
			}
		break;
	}
	
	/* Max length: 6 "CE DF MF " */
	if (ntohs(ih->frag_off) & IP_CE)
		printk("CE ");
	if (ntohs(ih->frag_off) & IP_DF)
		printk("DF ");
	if (ntohs(ih->frag_off) & IP_MF)
		printk("MF ");

	/* Max length: 11 "FRAG:65535 " */
	if (ntohs(ih->frag_off) & IP_OFFSET)
		printk("FRAG:%u ", ntohs(ih->frag_off) & IP_OFFSET);

	if ((logflags & IPT_LOG_IPOPT) &&
	    ih->ihl * 4 > sizeof(struct iphdr)) {
		const unsigned char *op;
		unsigned char _opt[4 * 15 - sizeof(struct iphdr)];
		unsigned int i, optsize;

		optsize = ih->ihl * 4 - sizeof(struct iphdr);
		op = skb_header_pointer(skb, iphoff+sizeof(_iph),
					optsize, _opt);
		if (op == NULL) {
			printk("TRUNCATED");
			return;
		}

		/* Max length: 127 "OPT (" 15*4*2chars ") " */
		printk("OPT (");
		for (i = 0; i < optsize; i++)
			printk("%02X", op[i]);
		printk(") ");
	}

	switch (ih->protocol) {
	case IPPROTO_TCP: {
		struct tcphdr _tcph;
		const struct tcphdr *th;

		/* Max length: 10 "PROTO=TCP " */
		printk("PROTO=TCP ");

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		th = skb_header_pointer(skb, iphoff + ih->ihl * 4,
					sizeof(_tcph), &_tcph);
		if (th == NULL) {
			printk("INCOMPLETE [%u bytes] ",
			       skb->len - iphoff - ih->ihl*4);
			break;
		}

		/* Max length: 20 "SPT=65535 DPT=65535 " */
		printk("SPT=%u DPT=%u ",
		       ntohs(th->source), ntohs(th->dest));
		/* Max length: 30 "SEQ=4294967295 ACK=4294967295 " */
		if (logflags & IPT_LOG_TCPSEQ)
			printk("SEQ=%u ACK=%u ",
			       ntohl(th->seq), ntohl(th->ack_seq));
		/* Max length: 13 "WINDOW=65535 " */
		printk("WINDOW=%u ", ntohs(th->window));
		/* Max length: 9 "RES=0x3F " */
		printk("RES=0x%02x ", (u8)(ntohl(tcp_flag_word(th) & TCP_RESERVED_BITS) >> 22));
		/* Max length: 32 "CWR ECE URG ACK PSH RST SYN FIN " */
		if (th->cwr)
			printk("CWR ");
		if (th->ece)
			printk("ECE ");
		if (th->urg)
			printk("URG ");
		if (th->ack)
			printk("ACK ");
		if (th->psh)
			printk("PSH ");
		if (th->rst)
			printk("RST ");
		if (th->syn)
			printk("SYN ");
		if (th->fin)
			printk("FIN ");
		/* Max length: 11 "URGP=65535 " */
		printk("URGP=%u ", ntohs(th->urg_ptr));

		if ((logflags & IPT_LOG_TCPOPT) &&
		    th->doff * 4 > sizeof(struct tcphdr)) {
			unsigned char _opt[4 * 15 - sizeof(struct tcphdr)];
			const unsigned char *op;
			unsigned int i, optsize;

			optsize = th->doff * 4 - sizeof(struct tcphdr);
			op = skb_header_pointer(skb,
						iphoff+ih->ihl*4+sizeof(_tcph),
						optsize, _opt);
			if (op == NULL) {
				printk("TRUNCATED");
				return;
			}

			/* Max length: 127 "OPT (" 15*4*2chars ") " */
			printk("OPT (");
			for (i = 0; i < optsize; i++)
				printk("%02X", op[i]);
			printk(") ");
		}
		break;
	}
	case IPPROTO_UDP:
	case IPPROTO_UDPLITE: {
		struct udphdr _udph;
		const struct udphdr *uh;

		if (ih->protocol == IPPROTO_UDP)
			/* Max length: 10 "PROTO=UDP "     */
			printk("PROTO=UDP " );
		else	/* Max length: 14 "PROTO=UDPLITE " */
			printk("PROTO=UDPLITE ");

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		uh = skb_header_pointer(skb, iphoff+ih->ihl*4,
					sizeof(_udph), &_udph);
		if (uh == NULL) {
			printk("INCOMPLETE [%u bytes] ",
			       skb->len - iphoff - ih->ihl*4);
			break;
		}

		/* Max length: 20 "SPT=65535 DPT=65535 " */
		printk("SPT=%u DPT=%u LEN=%u ",
		       ntohs(uh->source), ntohs(uh->dest),
		       ntohs(uh->len));
		break;
	}
	case IPPROTO_ICMP: {
		struct icmphdr _icmph;
		const struct icmphdr *ich;
		static const size_t required_len[NR_ICMP_TYPES+1]
			= { [ICMP_ECHOREPLY] = 4,
			    [ICMP_DEST_UNREACH]
			    = 8 + sizeof(struct iphdr),
			    [ICMP_SOURCE_QUENCH]
			    = 8 + sizeof(struct iphdr),
			    [ICMP_REDIRECT]
			    = 8 + sizeof(struct iphdr),
			    [ICMP_ECHO] = 4,
			    [ICMP_TIME_EXCEEDED]
			    = 8 + sizeof(struct iphdr),
			    [ICMP_PARAMETERPROB]
			    = 8 + sizeof(struct iphdr),
			    [ICMP_TIMESTAMP] = 20,
			    [ICMP_TIMESTAMPREPLY] = 20,
			    [ICMP_ADDRESS] = 12,
			    [ICMP_ADDRESSREPLY] = 12 };

		/* Max length: 11 "PROTO=ICMP " */
		printk("PROTO=ICMP ");

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		ich = skb_header_pointer(skb, iphoff + ih->ihl * 4,
					 sizeof(_icmph), &_icmph);
		if (ich == NULL) {
			printk("INCOMPLETE [%u bytes] ",
			       skb->len - iphoff - ih->ihl*4);
			break;
		}

		/* Max length: 18 "TYPE=255 CODE=255 " */
		printk("TYPE=%u CODE=%u ", ich->type, ich->code);

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		if (ich->type <= NR_ICMP_TYPES &&
		    required_len[ich->type] &&
		    skb->len-iphoff-ih->ihl*4 < required_len[ich->type]) {
			printk("INCOMPLETE [%u bytes] ",
			       skb->len - iphoff - ih->ihl*4);
			break;
		}

		switch (ich->type) {
		case ICMP_ECHOREPLY:
		case ICMP_ECHO:
			/* Max length: 19 "ID=65535 SEQ=65535 " */
			printk("ID=%u SEQ=%u ",
			       ntohs(ich->un.echo.id),
			       ntohs(ich->un.echo.sequence));
			break;

		case ICMP_PARAMETERPROB:
			/* Max length: 14 "PARAMETER=255 " */
			printk("PARAMETER=%u ",
			       ntohl(ich->un.gateway) >> 24);
			break;
		case ICMP_REDIRECT:
			/* Max length: 24 "GATEWAY=255.255.255.255 " */
			printk("GATEWAY=%pI4 ", &ich->un.gateway);
			/* Fall through */
		case ICMP_DEST_UNREACH:
		case ICMP_SOURCE_QUENCH:
		case ICMP_TIME_EXCEEDED:
			/* Max length: 3+maxlen */
			if (!iphoff) { /* Only recurse once. */
				printk("[");
				dump_packet(info, skb,
					    iphoff + ih->ihl*4+sizeof(_icmph), prefix);
				printk("] ");
			}

			/* Max length: 10 "MTU=65535 " */
			if (ich->type == ICMP_DEST_UNREACH &&
			    ich->code == ICMP_FRAG_NEEDED)
				printk("MTU=%u ", ntohs(ich->un.frag.mtu));
		}
		break;
	}
	/* Max Length */
	case IPPROTO_AH: {
		struct ip_auth_hdr _ahdr;
		const struct ip_auth_hdr *ah;

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		/* Max length: 9 "PROTO=AH " */
		printk("PROTO=AH ");

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		ah = skb_header_pointer(skb, iphoff+ih->ihl*4,
					sizeof(_ahdr), &_ahdr);
		if (ah == NULL) {
			printk("INCOMPLETE [%u bytes] ",
			       skb->len - iphoff - ih->ihl*4);
			break;
		}

		/* Length: 15 "SPI=0xF1234567 " */
		printk("SPI=0x%x ", ntohl(ah->spi));
		break;
	}
	case IPPROTO_ESP: {
		struct ip_esp_hdr _esph;
		const struct ip_esp_hdr *eh;

		/* Max length: 10 "PROTO=ESP " */
		printk("PROTO=ESP ");

		if (ntohs(ih->frag_off) & IP_OFFSET)
			break;

		/* Max length: 25 "INCOMPLETE [65535 bytes] " */
		eh = skb_header_pointer(skb, iphoff+ih->ihl*4,
					sizeof(_esph), &_esph);
		if (eh == NULL) {
			printk("INCOMPLETE [%u bytes] ",
			       skb->len - iphoff - ih->ihl*4);
			break;
		}

		/* Length: 15 "SPI=0xF1234567 " */
		printk("SPI=0x%x ", ntohl(eh->spi));
		break;
	}
	/* Max length: 10 "PROTO 255 " */
	default:
		printk("PROTO=%u ", ih->protocol);
	}

	/* Max length: 15 "UID=4294967295 " */
	if ((logflags & IPT_LOG_UID) && !iphoff && skb->sk) {
		read_lock_bh(&skb->sk->sk_callback_lock);
		if (skb->sk->sk_socket && skb->sk->sk_socket->file)
			printk("UID=%u GID=%u ",
				skb->sk->sk_socket->file->f_cred->fsuid,
				skb->sk->sk_socket->file->f_cred->fsgid);
		read_unlock_bh(&skb->sk->sk_callback_lock);
	}

	/* Max length: 16 "MARK=0xFFFFFFFF " */
	if (!iphoff && skb->mark)
		printk("MARK=0x%x ", skb->mark);

	/* Proto    Max log string length */
	/* IP:      40+46+6+11+127 = 230 */
	/* TCP:     10+max(25,20+30+13+9+32+11+127) = 252 */
	/* UDP:     10+max(25,20) = 35 */
	/* UDPLITE: 14+max(25,20) = 39 */
	/* ICMP:    11+max(25, 18+25+max(19,14,24+3+n+10,3+n+10)) = 91+n */
	/* ESP:     10+max(25)+15 = 50 */
	/* AH:      9+max(25)+15 = 49 */
	/* unknown: 10 */

	/* (ICMP allows recursion one level deep) */
	/* maxlen =  IP + ICMP +  IP + max(TCP,UDP,ICMP,unknown) */
	/* maxlen = 230+   91  + 230 + 252 = 803 */
}

static void dump_mac_header(const struct nf_loginfo *info,
			    const struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	unsigned int logflags = 0;

	if (info->type == NF_LOG_TYPE_LOG)
		logflags = info->u.log.logflags;

	if (!(logflags & IPT_LOG_MACDECODE))
		goto fallback;

	switch (dev->type) {
	case ARPHRD_ETHER:
		printk("MACSRC=%pM MACDST=%pM MACPROTO=%04x ",
		       eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest,
		       ntohs(eth_hdr(skb)->h_proto));
		return;
	default:
		break;
	}

fallback:
	printk("MAC=");
	if (dev->hard_header_len &&
	    skb->mac_header != skb->network_header) {
		const unsigned char *p = skb_mac_header(skb);
		unsigned int i;

		printk("%02x", *p++);
		for (i = 1; i < dev->hard_header_len; i++, p++)
			printk(":%02x", *p);
	}
	printk(" ");
}

static struct nf_loginfo default_loginfo = {
	.type	= NF_LOG_TYPE_LOG,
	.u = {
		.log = {
			.level    = 5,
			.logflags = NF_LOG_MASK,
		},
	},
};

static void
ipt_log_packet(u_int8_t pf,
	       unsigned int hooknum,
	       const struct sk_buff *skb,
	       const struct net_device *in,
	       const struct net_device *out,
	       const struct nf_loginfo *loginfo,
	       const char *prefix)
{
	if (!loginfo)
		loginfo = &default_loginfo;

	spin_lock_bh(&log_lock);
#if 0 /* Modified by zj, expand log level to record system event, (16 << 3) + original level, format is not defined */
		printk("<%d>%sIN=%s OUT=%s ", loginfo->u.log.level,
			   prefix,
			   in ? in->name : "",
			   out ? out->name : "");
#else
		

		printk("<%d>%sIN=%s OUT=%s ", loginfo->u.log.level + (16 << 3),
			   prefix,
			   in ? in->name : "",
			   out ? out->name : "");
#endif
#ifdef CONFIG_BRIDGE_NETFILTER
	if (skb->nf_bridge) {
		const struct net_device *physindev;
		const struct net_device *physoutdev;

		physindev = skb->nf_bridge->physindev;
		if (physindev && in != physindev)
			printk("PHYSIN=%s ", physindev->name);
		physoutdev = skb->nf_bridge->physoutdev;
		if (physoutdev && out != physoutdev)
			printk("PHYSOUT=%s ", physoutdev->name);
	}
#endif

	/* MAC logging for input path only. */
	if (in && !out)
		dump_mac_header(loginfo, skb);

	dump_packet(loginfo, skb, 0, prefix);
	printk("\n");
	spin_unlock_bh(&log_lock);
}

static unsigned int
log_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ipt_log_info *loginfo = par->targinfo;
	struct nf_loginfo li;

	li.type = NF_LOG_TYPE_LOG;
	li.u.log.level = loginfo->level;
	li.u.log.logflags = loginfo->logflags;
	match(skb);

    //if (printk_ratelimit())
    {
        ipt_log_packet(NFPROTO_IPV4, par->hooknum, skb, par->in, par->out, &li,
        	       loginfo->prefix);
    }
	return XT_CONTINUE;
}

static int log_tg_check(const struct xt_tgchk_param *par)
{
	const struct ipt_log_info *loginfo = par->targinfo;

	if (loginfo->level >= 8) {
		pr_debug("level %u >= 8\n", loginfo->level);
		return -EINVAL;
	}
	if (loginfo->prefix[sizeof(loginfo->prefix)-1] != '\0') {
		pr_debug("prefix is not null-terminated\n");
		return -EINVAL;
	}
	return 0;
}

static struct xt_target log_tg_reg __read_mostly = {
	.name		= "LOG",
	.family		= NFPROTO_IPV4,
	.target		= log_tg,
	.targetsize	= sizeof(struct ipt_log_info),
	.checkentry	= log_tg_check,
	.me		= THIS_MODULE,
};

static struct nf_logger ipt_log_logger __read_mostly = {
	.name		= "ipt_LOG",
	.logfn		= &ipt_log_packet,
	.me		= THIS_MODULE,
};

static int __init log_tg_init(void)
{
	int ret;

	ret = xt_register_target(&log_tg_reg);
	if (ret < 0)
		return ret;
	nf_log_register(NFPROTO_IPV4, &ipt_log_logger);
	return 0;
}

static void __exit log_tg_exit(void)
{
	nf_log_unregister(&ipt_log_logger);
	xt_unregister_target(&log_tg_reg);
}

module_init(log_tg_init);
module_exit(log_tg_exit);
