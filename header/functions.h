#ifndef _HEADER_FUNCTIONS_H
#define _HEADER_FUNCTIONS_H

// static void InsertInBlockList(restricted ** , __be32);
static void ResetCounter(void);
static int AssignMem(void);
static int startThings(void);
static int ReadFileAndInsertInBlockList(void);
void concatenate(char *, char , int);
static unsigned int found(__be32 );
static void Empty(void);
static int buffsize;

static unsigned int hook_function_incoming(unsigned int hooknum, struct sk_buff *skb, 
	const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *)){
	
	struct iphdr *iph = NULL;
	if(skb != NULL){
		iph = ip_hdr((skb));
		Counter++;
		if(Counter > MaxCounterValue)
			ResetCounter();

		if(iph->protocol == IPPROTO_ICMP){
			char * ipp = "127.0.0.1";
			if(iph->saddr == in_aton(ipp))
				return NF_ACCEPT;
			else
				printk(KERN_INFO "Blocked ICMP Request from %pI4\n", &(iph->saddr));
			return NF_DROP;
		}
		return found(iph->saddr);
	}
	else
		return NF_DROP;
}

static unsigned int found(__be32 addr){
	int i;
	for(i=0;i<buffsize;i++){
		// printk("in_aton(%s) = %u, addr = %u\n",buff[i], in_aton(buff[i]), addr);
		if(in_aton(buff[i]) == addr){
			printk(KERN_INFO "Blocked %s\n", buff[i]);
			return NF_DROP;
		}
	}
	printk(KERN_INFO "Accepting %pI4, %u\n", &(addr), addr);
	printk(KERN_INFO "Received Packet number %u\n",Counter);
	return NF_ACCEPT;
}

static void ResetCounter(void){
	Counter = 0;
}

static int AssignMem(void){
	int i,j;
	buff = kmalloc(sizeof(char *)*MaxList, GFP_KERNEL);
	if(buff == NULL){
		printk(KERN_ALERT "Error allocating size to buff. So not loading.");
		return 0;
	}
	else{
		printk(KERN_INFO "Memory Allocated to buff1 is : %lu", sizeof(buff));
		for(i=0;i<MaxList;i++){
			buff[i] = kmalloc((iplength+1), GFP_KERNEL);
			if(buff[i] == NULL){
				printk(KERN_ALERT "Error allocating size to buff[i]. So not loading.");
				return 0;
			}
			for(j=0;j<(iplength+1);j++)
				buff[i][j] = 0;
		}
		printk(KERN_INFO "Memory Allocated to buff2 is : %lu", sizeof(buff));
		return 1;
	}
}

/*
void InsertInBlockList(restricted **node, __be32 ip){
	restricted *temp = NULL;
	temp = kmalloc(sizeof(restricted), GFP_KERNEL);

	if(*node == NULL){
		temp -> Address = ip;
		temp -> next = NULL;
		(*node) = temp;
		return;
	}

	Inserting in Front	-->	Less code, more efficient while Insertion.	
	temp -> Address = ip;
	temp -> next = (*node);
	*node = temp;
}
*/

static void Empty(void){
	int i;
	printk(KERN_INFO "Freeing em !\n");
	for(i=0;i<MaxList;i++){
		kfree(buff[i]);
	}
	printk(KERN_INFO "Freed buff[i] !\n");
	kfree(buff);
	printk(KERN_INFO "Freed buff !\n");
	return;
}

static int startThings(void){
	int memAlloc = AssignMem();
	if(memAlloc){
		ReadFileAndInsertInBlockList();
		return 1;
	}
	else{
		return 0;
	}
}

void concatenate(char *(dest), char sour, int cursize){
	dest[cursize] = sour;
	return;
}

static int ReadFileAndInsertInBlockList(){
	struct file *f;
	mm_segment_t fs;
	char *buf;
	int i,j,cursize;
	buffsize = cursize = 0;

	buf = kmalloc(sizeof(char)*MaxList, GFP_KERNEL);	/* Max MaxList bytes !*/
	for(i=0;i<MaxList;i++)
		buf[i] = 0;
	f = filp_open(IpFile, O_RDONLY, 0);

	if(f == NULL){
		printk(KERN_ALERT "Ha Unable to open File.\n");
		return 0;
	}
	else{
		fs = get_fs(); /* Segment Descriptor. */
		set_fs(get_ds());
		f->f_op->read(f, buf, MaxList, &f->f_pos);
		set_fs(fs);
	}
	filp_close(f,NULL);
	i = j = 0;
	
	while(buf[i]){
		if(buf[i] == '\n'){
			printk(KERN_INFO "buff[%d] is %s\n", buffsize, buff[buffsize]);
			buffsize++;
			cursize=0;
		}
		else{
			concatenate(buff[buffsize], buf[i], cursize);
			cursize++;
		}
		i++;
	}
	return 1;
}

#endif /* _HEADER_FUNCTIONS_H */
