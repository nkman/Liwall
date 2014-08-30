#include <header/headers.h>

int init_module(){
	if(startThings()){
		nfho.hook = (hook_function_incoming);
		nfho.hooknum = NF_INET_PRE_ROUTING;
		nfho.pf = PF_INET;
		nfho.priority = NF_IP_PRI_FIRST;
		nf_register_hook(&nfho);
		printk(KERN_INFO "simple firewall loaded by nkman\n");
		return 0;
	}
	else{
		printk(KERN_INFO "Not loading !! Errors encountered.\n");
		return -1;
	}
}

void cleanup_module(){
	printk(KERN_INFO "Removing This Firewall.\n");
	Empty();
	nf_unregister_hook(&nfho);
}
