#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define listLength(l) ((l)->len)

typedef struct lnode{
	void *value;
	struct lnode *next;
}lnode;

typedef struct lstack{
	lnode *top;			/*栈顶指针*/
	lnode *bottom;		/*栈底指针*/
	int len;			/*链式栈高度*/
}lstack;

/*初始化链式栈*/
lstack *linkStackCreate(void){
	lstack *slstack;
	if ((slstack = (lstack *)malloc(sizeof(lstack))) == NULL)
        return NULL;
    slstack->top = slstack->bottom = NULL;
    slstack->len = 0;
    return slstack;
}

/*插入链式栈*/
lstack *linkStackAddNode(lstack *slstack, void *value){
	lnode *node;

    if ((node = (lnode *)malloc(sizeof(*node))) == NULL)
        return NULL;
    node->value = value;
   	if(slstack->len == 0){
   		slstack->top = slstack->bottom = node;
   	}else{
   		node->next = slstack->top;
   		slstack->top = node;
   	}
   	slstack->len++;
   	return slstack;
}

/*出链式栈*/
lnode *linkStackPopNode(lstack *lstack){
	lnode *node,*snode;
	if(listLength(lstack) < 1)
		return NULL;
	snode = lstack->top;
	if(lstack->top == lstack->bottom){
		lstack->top = lstack->bottom = NULL;
	}else{
		lstack->top = lstack->top->next;
	}
	lstack->len--;
	return snode;
}

/*清空链式栈*/
void clearLinkStack(lstack *lstack){
	lnode *del;
	while(lstack->top != NULL){
		del = lstack->top->next;
		free(lstack->top);
		lstack->top = del;
		lstack->len--;
	}
}

int main(){
	lstack *lstack = linkStackCreate();
	int num = 1,num2 = 2, num3 = 3;
	linkStackAddNode(lstack,&num);
	linkStackAddNode(lstack,&num2);
	linkStackAddNode(lstack,&num3);
	printf("%d\n",listLength(lstack));
	lnode *node = linkStackPopNode(lstack);
	printf("%d\n",*((int *)(node->value)));
	clearLinkStack(lstack);
	printf("%d\n",listLength(lstack));
	return 0;
}