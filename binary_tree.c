#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define getTreeNodeNum(l) ((l)->num)			

/*二叉查找树结构*/
typedef struct child{
	void *value;
	struct child *left;
	struct child *right;
}child;

typedef struct tree{
	child *root;
	int num;
}tree;

tree *binaryTreeCreate(void);                       /*二叉树的创建*/
tree *binaryTreeAddNode(tree *stree, void *data);   /*二叉树添加节点*/
void prePrintNode(child *root);						/*先序遍历*/
void midPrintNode(child *root);						/*中序遍历*/
void afterPrintNode(child *root);					/*后序遍历*/
int findNodeIsExist(tree *stree, int key);			/*查找节点是否存在*/
tree *treeDelNode(child *root, int key);			/*删除二叉树中指定节点*/		

/*二叉树的创建*/
tree *binaryTreeCreate(void){
	tree *stree;
	if((stree = (tree *)malloc(sizeof(*stree))) == NULL)
		return NULL;
	stree->root = NULL;
	stree->num = 0;
	return stree;
}

/*二叉树添加节点*/
tree *binaryTreeAddNode(tree *stree, void *data){
	child *node;
	child *parent = stree->root;
	if((node = (child *)malloc(sizeof(*node))) == NULL)
		return NULL;
	node->value = data;
	node->left = node->right = NULL;
	if(stree->root == NULL){
		stree->root = node;
	}else{
		while(parent != NULL){
			if(*((int *)data) < *((int *)(parent->value))){
				if(parent->left == NULL){
					parent->left = node;break;
				} else{
					parent = parent->left;
				} 
			}else{
				if(parent->right == NULL){
					parent->right = node;break;
				}else{
					parent = parent->right;
				}
			}
		}
	}
	stree->num++;
	return stree;
}

/*先序遍历*/
void prePrintNode(child *root){
	if(root != NULL){
		printf("%3d", *((int *)(root->value)));
		prePrintNode(root->left);
		prePrintNode(root->right);
	}
}

/*中序遍历*/
void midPrintNode(child *root){
	if(root != NULL){
		midPrintNode(root->left);
		printf("%3d", *((int *)(root->value)));
		midPrintNode(root->right);
	}
}

/*后序遍历*/
void afterPrintNode(child *root){
	if(root != NULL){
		afterPrintNode(root->left);
		afterPrintNode(root->right);
		printf("%3d", *((int *)(root->value)));
	}
}

/*查找值是否存在*/
int findNodeIsExist(tree *stree, int key){
	child *root = stree->root;
	while(root != NULL){
		if(key == *((int *)(root->value))){
			return 0;
		}else if(key < *((int *)(root->value))){
			root = root->left;
		}else{
			root = root->right;
		}
	}

	return -1;
}

/*删除二叉树中指定节点*/
tree *treeDelNode(child *root, int key){
	child *parent = root;
	if(root == NULL) return;
	if(root->left == NULL && root->right == NULL){
		free(root);return;
	}else{
		while(root != NULL){
			if(key == *((int *)(root->value))){
				if(root->right == NULL){
					parent->left = root->left;
				}else if(root->left == NULL){
					parent->right = root->right;
				}else{
					parent->left = root->left;
					root->left->right = root->right;
				}
				return;
			}else if(key < *((int *)(root->value))){
				parent = root;
				root = root->left;
			}else{
				parent = root;
				root = root->right;
			}
		}
	} 
}

int main(){
	tree *stree = binaryTreeCreate();
	int num = 24,num2 = 13, num3 = 25, num4 = 11, num5 = 14, num6 = 30, num7 = 8, num8 = 26;
	binaryTreeAddNode(stree, &num);
	binaryTreeAddNode(stree, &num2);
	binaryTreeAddNode(stree, &num3);
	binaryTreeAddNode(stree, &num4);
	binaryTreeAddNode(stree, &num5);
	binaryTreeAddNode(stree, &num6);
	binaryTreeAddNode(stree, &num7);
	binaryTreeAddNode(stree, &num8);
	treeDelNode(stree->root, 26);
	int status = findNodeIsExist(stree, 26);
	printf("求值是否存在: %d\n",status );
	printf("先序遍历：");
	prePrintNode(stree->root);
	printf("\n中序遍历：");
	midPrintNode(stree->root);
	printf("\n后序遍历：");
	afterPrintNode(stree->root);
	return 0;
}

