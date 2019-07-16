#include <stdio.h>
#include <stdlib.h>
/*平衡二叉树结构*/
typedef struct btree{
	void *value;
	int bf;															/*平衡因子*/
	struct btree *left;
	struct btree *right;
}btree;

int binaryBalanTreeAddNode(btree **sbtree, void *data);   			/*平衡二叉树添加节点*/
void lLotate(btree **sroot);										/*左旋*/
void rRotate(btree **sroot);										/*右旋*/
void rightBalance(btree **root);									/*右平衡*/
void leftBalance(btree **root);										/*左平衡*/
void midPrintNode(btree *sbtree);									/*中序遍历*/

void lLotate(btree **sroot){
	btree *r = (*sroot)->right;
	(*sroot)->right = r->left;
	r->left = (*sroot);
	(*sroot) = r;
}

void rRotate(btree **sroot){
	btree *l = (*sroot)->left;
	(*sroot)->left = l->right;
	l->right = (*sroot);
	(*sroot) = l;
}

void rightBalance(btree **sroot){
	btree *r = (*sroot)->right;
	if(r->bf == -1){
		(*sroot)->bf = r->bf = 0;
		lLotate(sroot);
	}

	if(r->bf == 1){
		switch(r->left->bf){
			case -1:
				(*sroot)->bf = 1;
				r->bf = 0;
				break;
			case 0:
				(*sroot)->bf = r->bf = 0;
				break;
			case 1:
				(*sroot)->bf = 0;
				r->bf = -1;
				break;
		}
		r->left->bf = 0;
		rRotate(&(*sroot)->right);
		lLotate(sroot);
	}
}

void leftBalance(btree **sroot){
	btree *l = (*sroot)->left;
	if(l->bf == 1){
		(*sroot)->bf = l->bf = 0;
		rRotate(sroot);
	}

	if(l->bf == -1){
		switch(l->right->bf){
			case -1:
				(*sroot)->bf = 0;
				l->bf = 1;
				break;
			case 0:
				(*sroot)->bf = l->bf = 0;
				break;
			case 1:
				(*sroot)->bf = -1;
				l->bf = 0;
				break;
		}
		l->right->bf = 0;
		lLotate(&(*sroot)->left);
		rRotate(sroot);
	}
}

int binaryBalanTreeAddNode(btree **sbtree, void *data){
	if((*sbtree) == NULL){
		if(((*sbtree) = (btree *)malloc(sizeof(btree))) == NULL)
			return -1;
		(*sbtree)->bf = 0;
		(*sbtree)->value = data;
		(*sbtree)->left = (*sbtree)->right = NULL;
	}else{
		if(*((int *)data) < *((int *)((*sbtree)->value))){
			if(binaryBalanTreeAddNode(&(*sbtree)->left,data) == -1)	return -1;
			switch((*sbtree)->bf){
				case -1:
					(*sbtree)->bf = 0;
					break;
				case  0:
					(*sbtree)->bf = 1;
					break;
				case  1:
					leftBalance(sbtree);
					break;
			}
		}else if(*((int *)data) > *((int *)((*sbtree)->value))){
			if(binaryBalanTreeAddNode(&(*sbtree)->right,data) == -1)	return -1;
			switch((*sbtree)->bf){
				case -1:
					rightBalance(sbtree);
					break;
				case  0:
					(*sbtree)->bf = -1;
					break;
				case  1:
					(*sbtree)->bf = 0;
					break;
			}
		}
	}
	
	return 0;
} 

/*中序遍历*/
void midPrintNode(btree *sbtree){
	if(sbtree != NULL){
		midPrintNode(sbtree->left);
		printf("%3d,%3d\n", *((int *)(sbtree->value)),sbtree->bf);
		midPrintNode(sbtree->right);
	}
}

int main(){
	btree *root = NULL;
	int num = 1,num2 = 23,num3 = 45,num4 = 34,num5 = 98,num6 = 9,num7 = 4,num8 = 35,num9 = 23;
	binaryBalanTreeAddNode(&root, &num);
	binaryBalanTreeAddNode(&root, &num2);
	binaryBalanTreeAddNode(&root, &num3);
	binaryBalanTreeAddNode(&root, &num4);
	binaryBalanTreeAddNode(&root, &num5);
	binaryBalanTreeAddNode(&root, &num6);
	binaryBalanTreeAddNode(&root, &num7);
	binaryBalanTreeAddNode(&root, &num8);
	midPrintNode(root);
	return 0;
}
