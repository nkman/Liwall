#ifndef _HEADER_SORT_H
#define _HEADER_SORT_H

/*functions defined*/
unsigned int partition(unsigned int *, int , int );
void Quick_sort(unsigned int *, int , int );
void _swap_(unsigned int *, unsigned int *);
/**/

unsigned int partition(unsigned int *a, int start, int end){
	unsigned int pivot;
	int index, i;
	i = index = start;
	pivot = a[end];
	while(i < end){
		if(a[i] <= pivot){	
			_swap_(&(a[i]), &(a[index]));
			index++;
		}
		i++;
	}
	_swap_(&(a[index]), &(a[end]));
	return index;
}

void Quick_sort(unsigned int *a, int start, int end){
	int index;
	if(start < end){
		index = partition(a, start, end);
		Quick_sort(a, start, index-1);
		Quick_sort(a, index+1 , end);
	}
	return;
}


void _swap_(unsigned int *i, unsigned int *j){
	unsigned int temp;
	temp = (*i);
	(*i) = (*j);
	(*j) = temp;
}

#endif /* _HEADER_FUNCTIONS_H */