#include <stdio.h>
#include <stdlib.h>

/**
*	插入排序
*/
int *insertSort(int *arr,int len){
	int i,j,key,k;
	for(i = 1; i < len; i++){
		key = arr[i];
		for(j = i-1; j >= 0; j--){
			if(key < arr[j]){
				arr[j+1] = arr[j];
				arr[j] = key;
			}
		}
	}

	return arr;
}

void main(){
	int arr[] = {29,3,45,21,30,65,38};
	int len = sizeof(arr) / sizeof(int);
	int *sry = insertSort(arr,len);
	int i;
	for(i = 0; i < len; i++){
		printf("%3d", sry[i]);
	}
}

