#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//在C语言标准(C89)没有定义布尔类型，gcc运行会报错.C99提供了一个头文件<stdbool.h>定义了bool，true代表1,false代表0.只要导入stdbool.h，就能非常方便的操作布尔类型了

/**
*	冒泡排序
*	@param  Pointer  arr
*	@param  Int  	len
*/
int *bubbleSort(int *arr,int len){
	int i,j,tmp;
	for( i = 0; i < len-1; i++ ){
		for( j = 0; j < len-i-1; j++ ){
			if( arr[j] > arr[j+1] ){
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}

	return arr;
}

/**
*	冒泡排序(进阶)
*	@param  Pointer  arr
*	@param  Int  	len
*/
int *bubbleAdvanceSort(int *arr,int len){
	int i,j,tmp;
	
	for( i = 0; i < len-1; i++ ){
		bool flag = false;
		for( j = 0; j < len-i-1; j++ ){
			if( arr[j] > arr[j+1] ){
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
				flag = true;
			}
		}

		if(!flag)  break;
	}

	return arr;
}
void main(){
	int arr[] = {29,3,45,21,30,65,38};
	int len = sizeof(arr)/sizeof(int);
	//冒泡排序(未优化)
	int *ary = bubbleSort(arr,len);
	int i;
	printf("----------优化前----------\n");
	for(i = 0; i < len; i++){
		printf("%3d", ary[i]);
	}
	//冒泡排序(优化后)
	ary = bubbleAdvanceSort(arr,len);
	printf("\n---------优化后---------\n");
	for(i = 0; i < len; i++){
		printf("%3d", ary[i]);
	}
}
