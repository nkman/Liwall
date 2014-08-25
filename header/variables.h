#ifndef _HEADER_VARIABLES_H
#define _HEADER_VARIABLES_H

/* Hook function varible. */
struct nf_hook_ops nfho;

/* buff = ["127.0.0.1","78.56.52.12"] */
/*static char **buff;*/

static unsigned int *buff;
#define MaxCounterValue 999999	/* Please don't overflow Int value. Ha*/
#define MaxList 1016	/* Increase this */ /* Fix This.*/
#define IpFile "/home/nkman/Desktop/Work/Liwall/list.txt"
#define iplength 16
static unsigned int Counter = 0;

#endif /* _HEADER_VARIABLES_H */