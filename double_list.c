#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define LIST_INSERT_AFTER	1
#define LIST_INSERT_BEFORE	0
#define listLength(l) ((l)->len)					    /*求双链表的长度*/

/* 双向链表结构 */
typedef struct lnode{
	void *value;
	struct lnode *prev;
	struct lnode *next;
}lnode;

typedef struct list{
	lnode *head;
	lnode *tail;
	int len;
}list;

list *listCreate(void);									/*创建双向链表*/
list *listAddNodeHead(list *slist, void *value);		/*双向链表头部插入元素*/
list *listAddNodeTail(list *slist, void *value);		/*双向链表尾部插入元素*/
list *listInsertNode(list *slist, lnode *old_node, void *value, int after);			/*指定节点插入元素*/
list *listDelLastNode(list *slist);						/*删除双链表的最后一个元素*/
list *listDelFirstNode(list *slist);					/*删除双链表的第一个元素*/
void printfList(list *slist);							/*打印双向链表*/
void listRotate(list *slist);							/*逆置双链表*/
lnode *listIndex(list *slist, int index);				/*查找双向链表中指定位置的值*/			

/*创建双向链表*/
list *listCreate(void){
	list *slist;
	if((slist = (list *)malloc(sizeof(*slist))) == NULL)
		return NULL;
	slist->head = slist->tail = NULL;
	slist->len = 0;
	return slist;
}

/*头插法*/
list *listAddNodeHead(list *slist, void *value){
	lnode *node;
	if((node = (lnode *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(slist->len == 0){
		slist->head = slist->tail = node;
		node->prev = node->next = NULL;
	}else{
		node->prev = NULL;
		node->next = slist->head;
		slist->head->prev = node;
		slist->head = node;
	}
	slist->len++;
	return slist;
}

/*尾插法*/
list *listAddNodeTail(list *slist, void *value){
	lnode *node;
	if((node = (lnode *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(slist->len == 0){
		slist->head = slist->tail = node;
		node->prev = node->next = NULL;
	}else{
		node->next = NULL;
		node->prev = slist->tail;
		slist->tail->next = node;
		slist->tail = node;
	}
	slist->len++;
	return slist;
}

/*指定节点插入*/
list *listInsertNode(list *slist, lnode *old_node, void *value, int after) {
	lnode *node;
	if((node = (lnode *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = value;
	if(after){
		node->prev = old_node;
		node->next = old_node->next;
		if(slist->tail == old_node){
			slist->tail = node;
		}
	}else{
		node->prev = old_node->prev;
		node->next = old_node;
		if(slist->head == old_node){
			slist->head = node;
		}
	}

	if (node->prev != NULL) {
        node->prev->next = node;
    }
    if (node->next != NULL) {
        node->next->prev = node;
    }
	slist->len++;
	return slist;
}

/*删除双链表的最后一个元素*/
list *listDelLastNode(list *slist){
	lnode *node;
	if(slist->len == 0) return NULL;
	if(slist->len == 1){
		slist->head = slist->tail = NULL;
	}else{
		node = slist->tail;
		slist->tail = node->prev;
		slist->tail->next = NULL;
		free(node);
	}
	slist->len--;
	return slist;
}

/*删除双链表的第一个元素*/
list *listDelFirstNode(list *slist){
	lnode *node;
	if(slist->len == 0) return NULL;
	if(slist->len == 1){
		slist->head = slist->tail = NULL;
	}else{
		node = slist->head;
		slist->head = node->next;
		slist->head->prev = NULL;
		free(node);
	}
	slist->len--;
	return slist;
}

/*旋转双向链表*/
void listRotate(list *slist){
	//只需将头结点指向尾节点即可
	lnode *tail = slist->tail;
	if(slist->len <= 1) return;
	slist->tail = tail->prev;
	slist->tail = NULL;

	tail->next->prev = tail;
	tail->prev = NULL;
	tail->next = slist->head;
	slist->head = tail;
}

/*根据指定位置查找元素*/
lnode *listIndex(list *slist, int index){
	lnode *node;
	if(index < 0){
		index = (-index)-1;
		node = slist->tail;
		while(index-- && node) node = node->prev;
	}else{
		node = slist->head;
		while(index-- && node) node = node->next;
	}

	return node;
}

/*删除节点*/
list *listDelNode(list *slist, lnode *node){
	if(node == NULL || slist->len == 0) return NULL;
	if(slist->len == 1){
		free(node);
		slist->head = slist->tail = NULL;
	}else{
		if(slist->tail == node){
			node->next = NULL;
			slist->tail = node;
		}else{
			node->prev = node;
		}
	}
	slist->len--;
	return slist; 
}

/*打印链表*/
void printfList(list *slist){
	lnode *node;
	node = slist->head;
	while(node != NULL){
		printf("%2d",*((int *)(node->value)));
		node = node->next;
	}
	printf("\n");
}

int main(){
	list *list = listCreate();
	int num = 1, num2 = 2, num3 = 3, num4 = 4;
	listAddNodeHead(list,&num);
	listAddNodeHead(list,&num2);
	listAddNodeHead(list,&num3);
	/*在第二个节点中间插入数据*/
	listInsertNode(list,list->head->next,&num4,1);
	printf("length=%d\n",listLength(list));
	printfList(list);
	/*根据指定位置查找元素*/
	lnode *node = listIndex(list, 1);
	printf("%2d",*((int *)(node->value)));
	/*删除双链表的最后一个元素*/
	listDelLastNode(list);
	/*删除双链表的第一个元素*/
	listDelFirstNode(list);
	return 0;
}