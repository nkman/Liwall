#ifndef _HEADER_FUNCTIONS_H
#define _HEADER_FUNCTIONS_H

#include <header/sort.h>

// static void InsertInBlockList(restricted ** , __be32);
/*sets counter to zero*/
static void ResetCounter(void);

/*Memory allocation to different varibles*/
static int AssignMem(void);

/*Start function*/
static int startThings(void);

/*Read from file*/
static unsigned int ReadFileAndInsertInBlockList(void);

/*Concatenate string with char*/
void concatenate(char *, char , int);

/*Ip match function
static unsigned int found(__be32 );
*/

/*Free the allocated memory*/
static void Empty(void);

/*Assign string to zero*/
void zero(char *);

/*Printind buff*/
// static void print_buff(void);

/*Ip match function*/
static unsigned int binary_search(__be32 );

static int startThings(void){
	int memAlloc = AssignMem();
	if(memAlloc){
		ReadFileAndInsertInBlockList();
		Quick_sort(buff, 0, buffsize-1);
		// print_buff();
		return 1;
	}
	else{
		return 0;
	}
}

/*
static void print_buff(){
	int i=0;
	for(i=0;i<buffsize;i++)
		printk(KERN_INFO "buff[%d] is %u\n", i, buff[i]);
	return;
}
*/
static int AssignMem(void){
	int i;
	buff = kmalloc(sizeof(unsigned int *)*MaxList, GFP_KERNEL);
	if(buff == NULL){
		printk(KERN_ALERT "Error allocating size to buff. So not loading.");
		return 0;
	}
	else{
		for(i=0;i<MaxList;i++)
			buff[i] = 0;
		return 1;
	}
}

static unsigned int ReadFileAndInsertInBlockList(){
	struct file *f;
	mm_segment_t fs;
	char *buf, *temp_buff;
	int i,cursize;
	buffsize = cursize = 0;

	buf = kmalloc(sizeof(char)*MaxList, GFP_KERNEL);	/* Max MaxList bytes !*/
	temp_buff = kmalloc(sizeof(char)*iplength, GFP_KERNEL);
	for(i=0;i<MaxList;i++){
		buf[i] = 0;
	}

	for(i=0;i<iplength;i++){
		temp_buff[i] = 0;
	}

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
	i = 0;
	// temp_buff = "\0";
	while(buf[i]){
		if(buf[i] == '\n'){
			buff[buffsize] = in_aton(temp_buff);
			// printk(KERN_INFO "buff[%d] is %u and temp_buff is %s\n", buffsize, buff[buffsize], temp_buff);
			buffsize++;
			cursize=0;
			zero(temp_buff);
		}
		else{
			concatenate(temp_buff, buf[i], cursize);
			cursize++;
		}
		i++;
	}
	kfree(buf);
	kfree(temp_buff);
	return 1;
}

void zero(char *temp_buff){
	int i;
	for(i=0;i<iplength;i++)
		temp_buff[i] = 0;
}

void concatenate(char *(dest), char sour, int cursize){
	dest[cursize] = sour;
	return;
}

/*Incoming hook function*/
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
		return binary_search(iph->saddr);
	}
	else
		return NF_DROP;
}

/*
static unsigned int found(__be32 addr){
	int i;
	for(i=0;i<buffsize;i++){
		if(buff[i] == addr){
			printk(KERN_INFO "Blocked %u\n", buff[i]);
			return NF_DROP;
		}
	}
	printk(KERN_INFO "Accepting %pI4, %u\n", &(addr), addr);
	printk(KERN_INFO "Received Packet number %u\n",Counter);
	return NF_ACCEPT;
}
*/

static unsigned int binary_search(__be32 addr){
	int first, last, middle;
	first = 0; 
	last = buffsize-1; 
	middle = (first+last)/2;
	while(first <= last){
		if(addr == buff[middle]){
			printk(KERN_INFO "Blocked %pI4\n", &(addr));
			return NF_DROP;
		}
		else if(addr > buff[middle])
			first = middle + 1;
		else
			last = middle - 1;
		middle = (first+last)/2;
	}
	printk(KERN_INFO "Accepting %pI4\n", &(addr));
	return NF_ACCEPT;
}


static void ResetCounter(void){
	Counter = 0;
}

static void Empty(void){
	kfree(buff);
	printk(KERN_INFO "Freed buff !\n");
	return;
}

#endif /* _HEADER_FUNCTIONS_H */