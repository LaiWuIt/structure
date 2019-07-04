#include <stdio.h>
#include <stdlib.h>
#define queueLength(l) ((l)->len)

/*链式队列结构*/
typedef struct lnode{
	void *value;
	struct lnode *next;
}lnode;

typedef struct lqueue{
	lnode *front;			/*指向头结点*/
	lnode *rear;			/*指向尾节点*/
	int len;				/*队列长度*/
}lqueue;

/*初始化链式队列*/
lqueue *linkQueueCreate(void){
	lqueue *queue;
	if ((queue = (lqueue *)malloc(sizeof(*queue))) == NULL)
		return NULL;
	queue->front = queue->rear = NULL;	/*避免成为野指针*/
	queue->len = 0;
	return queue;
}

/*链式队列添加元素*/
lqueue *linkQueueAddNode(lqueue *slqueue, void *value){
	lnode *node;
	if ((node = (lnode *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	node->next = NULL;
	if(slqueue->len == 0){
		slqueue->front = slqueue->rear = node;
	}else{
		slqueue->rear->next = node;
		slqueue->rear = node;
	}
	slqueue->len++;
	return slqueue;
}

/*出链式队列*/
lnode *linkQueuePopNode(lqueue *slqueue){
	lnode *node,*snode;
	if(slqueue->len < 1)
		return NULL;
	snode = slqueue->front;
	if(slqueue->front == slqueue->rear){
		slqueue->front = slqueue->rear = NULL;
	}else{
		slqueue->front = slqueue->front->next;
	}
	slqueue->len--;
	return snode;
}

/*遍历链式队列*/
void printfLinkQueueNode(lqueue *slqueue){
	lnode *node = slqueue->front;
	while(slqueue->len >= 1){
		printf("%2d",*((int *)(node->value)));
		node = node->next;
		slqueue->len--;
	}
}

int main(){
	lqueue *queue = linkQueueCreate();
	int num = 1, num2 = 2, num3 = 3, num4 = 4;
	linkQueueAddNode(queue, &num);
	linkQueueAddNode(queue, &num2);
	linkQueueAddNode(queue, &num3);
	linkQueueAddNode(queue, &num4);
	printf("Length = %d\n",queueLength(queue));
	/*打印队列*/
	printfLinkQueueNode(queue);
	/*出队列*/
	lnode *node = linkQueuePopNode(queue);
	printf("%d",*((int *)(node->value)));
	return 0;
}