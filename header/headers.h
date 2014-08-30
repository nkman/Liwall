#ifndef _HEADER_HEADERS_H
#define _HEADER_HEADERS_H


#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/netfilter/x_tables.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/if_ether.h>
#include <linux/rbtree.h>
#include <linux/kref.h>
#include <linux/time.h>
#include <linux/inet.h> //in_aton() --> defined in http://lxr.free-electrons.com/source/net/core/utils.c#L55

#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_ecache.h>

#include <linux/slab.h> //useing kmalloc.
#include <linux/fs.h>      // Needed by filp
#include <asm/uaccess.h>   // Needed by segment descriptors

#include <header/modfirewall.h>
#include <header/driverdescription.h>
#include <header/variables.h>
#include <header/functions.h>

#endif /* _HEADER_HEADERS_H */