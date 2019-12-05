#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define LIST_INSERT_AFTER	1
#define LIST_INSERT_BEFORE	0
#define listLength(l) ((l)->len)


/*单向链表结构*/
typedef struct lnode{
	void *value;
	struct lnode *next;
}lnode;

typedef struct list{
	lnode *head;
	lnode *tail;
	int len;
}list;

list *listCreate(void);									/*链表初始化*/
list *listAddNodeHead(list *slist, void *value);		/*链表头添加节点*/
list *listAddNodeTail(list *slist, void *value);		/*链表尾添加节点*/
list *listAddNodeMiddle(list *slist, lnode *node, void *value, int after);		/*链表指定位置添加节点*/
list *listReserve(list *slist);							/*链表翻转*/
lnode *listIndex(list *slist, int index);				/*查找链表中指定位置的值*/
list *listDelNode(list *slist, lnode *node);			/*删除链表中节点*/
void printList(list *slist);							/*打印链表*/

/*链表初始化*/
list *listCreate(void){
	list *slist;
	if((slist = (list *)malloc(sizeof(*slist))) == NULL)
		return NULL;
	slist->head = slist->tail = NULL;
	slist->len = 0;
	return slist;
}

/*链表头添加节点*/
list *listAddNodeHead(list *slist, void *value){
	lnode *node;
	if((node = (lnode *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(slist->len == 0){
		node->next = NULL;
		slist->head = slist->tail = node;
	}else{
		node->next = slist->head;
		slist->head = node; 
	}
	slist->len++;
	return slist;
}

/*链表尾添加节点*/
list *listAddNodeTail(list *slist, void *value){
	lnode *node;
	if((node = (lnode *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(slist->len == 0){
		slist->head = slist->tail = node;
	}else{
		node->next = NULL;
		slist->tail->next = node; 
		slist->tail = node;
	}
	slist->len++;
	return slist;
}
/*链表指定位置添加节点*/
list *listAddNodeMiddle(list *slist, lnode *old_node, void *value, int after){
	lnode *node;
	if((node = (lnode *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(after){
		node->next = NULL;
		slist->tail->next = node;
	}else{
		node->next = old_node->next;
		old_node->next = node;
	}

	if(node->next == NULL){
		slist->tail->next = node;
	}
	slist->len++;
	return slist;
}

/*链表翻转*/
list *listReserve(list *slist){
	lnode *p,*q,*m;
	if(slist->len <= 1) return;
	p = slist->head;
	q = slist->head->next;
	while(m != NULL){
		m = q->next;
		q->next = p;
		p = q;
		q = m;
	}
	slist->tail = slist->head;
	slist->tail->next = NULL;
	slist->head = p;
	return slist;
}

/*查找链表中指定位置的值*/
lnode *listIndex(list *slist, int index){
	lnode *node = slist->head;
	if(index < 0)
		index = slist->len+index;
	while(index-- && node) node = node->next;
	return node;
}

/*删除链表中节点*/
list *listDelNode(list *slist, lnode *node){
	if(node == NULL || slist->len == 0) return NULL;
	lnode *head,*n;
	head = slist->head;
	if(slist->len == 1){
		free(node);
		slist->head = slist->tail = NULL;
	}else if(slist->head == node){
		slist->head = node->next;
	}else{
		while(head != NULL){
			if(*((int *)(head->value)) == *((int *)(node->value))){
				n->next = node->next;
				free(node);
				break;
			}
			n = head;
			head = head->next;
		}
	}
	return slist;
}

/*打印链表*/	
void printList(list *slist){
	lnode *node = slist->head;
	while(node != NULL){
		printf("%2d",*((int *)(node->value)));
		node = node->next;
	}
	printf("\n");
}	

int main(){
	list *slist = listCreate();
	int num = 1,num2 = 2,num3 = 3,num4 = 4,num5 = 5;
	listAddNodeHead(slist, &num);
	listAddNodeHead(slist, &num2);
	listAddNodeHead(slist, &num3);
	listAddNodeTail(slist, &num4);
	listAddNodeMiddle(slist, slist->head->next, &num5, LIST_INSERT_AFTER);
	listAddNodeMiddle(slist, slist->head->next, &num5, LIST_INSERT_BEFORE);
	printList(slist);
	listReserve(slist);
	listDelNode(slist, slist->head->next);
	lnode *node = listIndex(slist, 1);
	printf("%d\n",*((int *)(node->value)));
	return 0;
}
