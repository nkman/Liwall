#ifndef _HEADER_SORT_H
#define _HEADER_SORT_H

/*functions defined*/
unsigned int partition(unsigned int *, unsigned int , unsigned int );
void Quick_sort(unsigned int *, unsigned int , unsigned int );
// void swap(unsigned int , unsigned int );
/**/

unsigned int partition(unsigned int *a, unsigned int start, unsigned int end){
	unsigned int pivot = a[end], index = start, i=0, temp;
	while(i<end){
		if(a[i] < pivot){	
			temp = a[i];
			a[i] = a[index];
			a[index] = temp;
			index++;
		}
		i++;
	}
	temp = a[index];
	a[index] = a[end];
	a[end] = temp;
	return index;
}

void Quick_sort(unsigned int *a, unsigned int start, unsigned int end){
	unsigned int index;
	if(start < end){
		index = partition(a, start, end);
		Quick_sort(a, start, index-1);
		Quick_sort(a, index+1 , end);
	}
	return;
}

/*
void swap(unsigned int a, unsigned int b){
	unsigned int temp;
	temp = a;
	a = b;
	b = temp;
}
*/
#endif /* _HEADER_FUNCTIONS_H */