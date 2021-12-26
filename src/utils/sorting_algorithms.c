#include"../headers/sorting_algorithms.h"

typedef long long unsigned int llui;

void swap(llui* old, llui* new){
	llui hold = *old;
	*old = *new;
	*new = hold;
}
void llui_bubble_sort(llui* arr, llui n){
	llui swapped, i, j;
	for (i=0; i<n-1; ++i){
		swapped = 0;
		for(j=0; j<n-1-i; ++j){
			if ( arr[j] > arr[j+1] ){
				swap(&arr[j], &arr[j+1]);
				swapped = 1;
			}
		}
		if ( ! swapped ) return;
	}
}
void llui_selection_sort(llui* arr, llui n){
	llui min, i, j;
	for(i=1; i<n-1; ++i){
		min = i;
		for(j=i; j<n; ++j)
			if (arr[j] < arr[min]) min = j;
		swap(&arr[i], &arr[min]);
	}
}
void llui_insertion_sort(llui* arr, llui n){
	llui  i, j;
	for(i=1; i<n-1; ++i){
		for(j=i; j>0 && (arr[j-1] > arr[j]); --j)
			swap(&arr[j], &arr[j-1]);
	}
}
