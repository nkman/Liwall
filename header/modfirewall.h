#ifndef _HEADER_MODFIREWALL_H
#define _HEADER_MODFIREWALL_H


void concat_(char *, char );

struct WebSitesToBlock{
	__be32 Address;
	struct WebSitesToBlock *next;
};

typedef struct WebSitesToBlock restricted;

#endif /* _HEADER_MODFIREWALL_H */