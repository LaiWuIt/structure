#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*B树节点结构*/
typedef struct node{
	int num;					/*节点中关键字个数*/
	int *key;					/*关键字*/
	struct node **child;
	struct node *parent;		/*父节点*/
}tnode;

typedef struct btree{
	int max;			/*单个节点最大关键字个数 m阶 max = m -1*/
	int min;			/*单个节点最小关键字个数 ceil(m/2) -1 */
	int sidx;
	tnode *root;		/*B树根节点地址*/
}btree;

btree *btreeCreate(int m);                       		/*B树的创建*/
btree *btreeAddNode(btree *sbtree, int data);   		/*B树添加节点*/
int   btreeSplitNode(btree *sbtree,tnode *node);		/*B树分裂节点*/
tnode *createNode();									/*创建节点*/

btree *btreeCreate(int m){
	btree *sbtree;
	if((sbtree = (btree *)malloc(sizeof(sbtree))) == NULL)
		return NULL;

	sbtree->max = m -1;
	sbtree->min = m / 2;
	if(m%2 != 0)	sbtree->min++;				/*此处最小关键字为 ceil(m/2)-1*/
	sbtree->min--;
	sbtree->sidx = m/2;
	sbtree->root = NULL;

	return sbtree;
} 

btree *btreeAddNode(btree *sbtree, int data){
	tnode *node = NULL;
	tnode *btnode = sbtree->root;
	if(btnode == NULL){
		if((node = (tnode *)malloc(sizeof(node))) == NULL)
			return NULL;
		node->num = 1;
		node->key = (int *)calloc(sbtree->max+1,sizeof(int));
		node->key[0] = data;
		node->parent = NULL;
		node->child = (tnode **)calloc(sbtree->max+2, sizeof(tnode *));
		sbtree->root = node;
	}else{
		int i,j;
		while(btnode != NULL){
			//寻找插入位置
			for(i = 0; i < btnode->num; i++){
				if(btnode->key[i] == data){
					printf("The node is exist");
				}else if(data < btnode->key[i]){
					break;
				}
			}

			if(btnode->child[i] != NULL)
				btnode = btnode->child[i];
			else
				break;
		}
		
		//插入数据
		for(j = btnode->num; j > 0; j--){
			btnode->key[j] = btnode->key[j-1];
		}
		btnode->key[i] = data;
		btnode->num++;

		if(btnode->num > sbtree->max){
			//分裂
			int res = btreeSplitNode(sbtree,btnode);
			if(res == 0){
				return sbtree; 
			}
		}
	}

	return sbtree;
}	

int btreeSplitNode(btree *sbtree,tnode *btnode){
	tnode *parent = NULL;
	int sidx = sbtree->sidx;
	while(btnode->num > sbtree->max){
		int num = btnode->num;
		tnode *node = createNode(sbtree);
		if(node == NULL)	return -1;

		memcpy(node->key,btnode->key+sidx+1,(num-sidx-1)*sizeof(int));
		memcpy(node->child,btnode->child+sidx+1,(num - sidx)*sizeof(tnode *));

		node->num = btnode->num-sidx-1;
		node->parent = btnode->parent;

		btnode->num = sidx;
		parent = btnode->parent;

		if(parent == NULL){
			parent = createNode(sbtree);
			if(parent == NULL)	return -1;

			sbtree->root = parent;
			parent->child[0] = btnode;
			btnode->parent = parent;
			node->parent = parent;

			parent->key[0] = btnode->key[sidx];
			parent->child[1] = node;
			parent->num++;
		}else{
			int i;
			for(i = parent->num; i > 0; i--){
				if(btnode->key[sidx] < parent->key[i]){
					parent->key[i] = parent->key[i-1];
					parent->child[i+1] = parent->child[i];
					continue;
				}
				break;
			}

			parent->key[i] = btnode->key[sidx];
			parent->child[i+1] = node;
			node->parent = parent;
			parent->num++;
		}

		memset(btnode->key+sidx,0,(num-sidx) * sizeof(int));
		memset(btnode->key+sidx+1,0,(num-sidx) * sizeof(tnode *));

		int j;
		for(j = 0; j <= node->num; j++){
			if(node->child[j] != NULL){
				node->child[j]->parent = node;
			}
		}
		btnode = parent;
	}
	return 0;
}

tnode *createNode(btree *sbtree){
	tnode *node;
	if((node = (tnode *)malloc(sizeof(node))) == NULL)
		return NULL;
	node->num = 0;
	node->key = (int *)calloc(sbtree->max+1,sizeof(int));
	node->child = (tnode **)calloc(sbtree->max+2,sizeof(tnode *));
	return node;
}

int main(){
	btree *sbtree = btreeCreate(4);
	btreeAddNode(sbtree, 45);
	btreeAddNode(sbtree, 24);
	btreeAddNode(sbtree, 53);
	btreeAddNode(sbtree, 90);
	btreeAddNode(sbtree, 46);
	btreeAddNode(sbtree, 47);
	btreeAddNode(sbtree, 15);
	btreeAddNode(sbtree, 18);
	btreeAddNode(sbtree, 48);
	btreeAddNode(sbtree, 49);
	btreeAddNode(sbtree, 50);
	return 0;
}




