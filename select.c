#include <stdio.h>
#include <stdlib.h>

/**
*	选择排序
*	@param 	Pointer arr
*	@param  Int  len
*/
int *selectSort(int *arr,int len){
	int i,j,min,tmp;
	for(i = 0; i < len-1; i++){
		min = i;
		for(j = i + 1; j < len; j++){
			if(arr[j] < arr[min]){
				min = j;
			}
		}
		tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
	}

	return arr;
}

void main(){
	int arr[] = {29,3,45,21,30,65,38};
	int len = sizeof(arr) / sizeof(int);
	int *sry = selectSort(arr,len);
	int i;
	for(i = 0; i < len; i++){
		printf("%3d", sry[i]);
	}
}