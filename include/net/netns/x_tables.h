#ifndef __NETNS_X_TABLES_H
#define __NETNS_X_TABLES_H

#include <linux/list.h>
#include <linux/netfilter.h>

struct ebt_table;

struct netns_xt {
	struct list_head tables[NFPROTO_NUMPROTO];
#if defined(CONFIG_BRIDGE_NF_EBTABLES) || \
    defined(CONFIG_BRIDGE_NF_EBTABLES_MODULE)
	struct ebt_table *broute_table;
	struct ebt_table *frame_filter;
	struct ebt_table *frame_nat;
/*
 * TBS_TAG: 
 * Desc: Added table func for EBT 
 */
    struct ebt_table *proute_table;
    struct ebt_table *aroute_table;
/*
 * TBS_END_TAG
 */
#endif
};
#endif
