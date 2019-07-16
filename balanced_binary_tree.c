#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// /*平衡二叉树结构*/
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








// #include<stdio.h>
// #include<stdlib.h>

// #define EH 0            /*等高*/
// #define LH 1            /*左高*/
// #define RH -1            /*右高*/
    
// typedef int ElemType;                 /*数据类型*/

// typedef struct BiTree{
//     ElemType data;                    /*数据元素*/
//     int BF;                         /*平衡因子*/
//     struct BiTree *lchild,*rchild;     /*左右子女指针*/
// }*Bitree,BitreeNode;


// int InsertAVL(Bitree *T,ElemType e);
// void LeftBalance(Bitree *T);
// void RightBalance(Bitree *T);
// void R_Rotate(Bitree *T);
// void L_Rotate(Bitree *T);
// //bool *taller=(bool*)malloc(sizeof(bool));

// int main(void)
// {
//     int data;
//     Bitree T=NULL;
//     // while(1)
//     // {
//     //     printf("enter the number(zero to exit):");
//     //     scanf("%d",&data);
//     //     if(0==data)break;
//     //     InsertAVL(&T,data,taller);
        
//     // }
    
//     int arr[] = {1,2};
//     // for(i = 0; i <= 2; i++){
//     // 	InsertAVL(&T,i);
//     // }
    
//     int i = 1,j = 2,k = 3;
//     //printf("%p\n",&T);
//     InsertAVL(&T,i);
//     //printf("%p\n",&T);
//     InsertAVL(&T,j);
//     //printf("%p\n",&T);
//     InsertAVL(&T,k);
//     //InsertAVL(&T,4);
//     return 0;
// }

// int InsertAVL(Bitree *T,ElemType e){

// 	int flag; 
// 	if(!*T)                /*插入新结点，树“长高”，置taller 为TURE*/
//     {	
//         (*T)=(Bitree)malloc(sizeof(BitreeNode));
        
//         (*T)->data = e;
//         (*T)->lchild = (*T)->rchild = NULL;
//         (*T)->BF = EH;
//         printf("data=%d,addr=%p\n",(*T)->data,T);
//         flag = 1;
//         if((*T)->data == 1) printf("\n");
//     }
//     else{
//     	if(e==(*T)->data)        /*树中存在和e 有相同关键码的结点，不插入*/
//         {
//             return 0;
//         }
//         if(e<(*T)->data){
//         	if(!InsertAVL(&(*T)->lchild,e))	return 0;
//         }else{
//         	printf("rs=%d&data=%daddr=%p\n",(*T)->BF,(*T)->data,T);
//         	if(!InsertAVL(&(*T)->rchild,e))    return 0; 
//         	printf("bf=%d&data=%d\n",(*T)->BF,(*T)->data);
        	
//         	//if(flag){
//         		// switch((*T)->BF)
// 	         //    {     
// 	         //        case EH :     
// 	         //        	/*原本左、右子树等高，因左子树增高使树增高*/
// 	         //            (*T)->BF=RH;
// 	         //            printf("EH=%d&data=%d,addr=%p\n",(*T)->BF,(*T)->data,T);
// 	         //         	flag = 1;
// 	         //            break;
	                
// 	         //        case LH :   
// 	         //        	(*T)->BF = EH;                 /*原本左子树高，需作左平衡处理*/
// 	         //            printf("LH=%d&data=%d,addr=%p\n",(*T)->BF,(*T)->data,T);
// 	         //            flag = 0;
// 	         //            break;
	                
// 	         //        case RH :  
// 	         //        	//RightBalance(root);                  /*原本右子树高，使左、右子树等高*/
// 	         //            (*T)->BF=EH; 
// 	         //           	printf("RH=%d&data=%d,addr=%p\n",(*T)->BF,(*T)->data,T);
// 	         //           	flag = 0;
// 	         //            break;
// 	         //    }
//         	//}
        	
//         }
//     }
// }

// void LeftBalance(Bitree *T)
// {
//     Bitree L=(*T)->lchild,Lr;             /*L 指向*T左子树根结点*/
//     switch(L->BF)                /*检查L 平衡度，并作相应处理*/
//     {
//         case LH:                    /*新结点插在*p 左子树的左子树上，需作单右旋转处理*/
//             (*T)->BF=L->BF=EH;
//              R_Rotate(T);
//              break;
//         case EH:             /*原本左、右子树等高，因左子树增高使树增高*/
//             (*T)->BF=LH;    //这里的EH好像没有写的必要 
             
//               break;
//         case RH:                     /*新结点插在*T 左孩子的右子树上，需作先左后右双旋处理*/
//             Lr=L->rchild;             /*Lr 指向*p 左孩子的右子树根结点*/    
//             switch(Lr->BF)         /*修正*T 及其左子树的平衡因子*/
//             {
//                 case LH:
//                     (*T)->BF = RH;
//                     L->BF = EH;
//                     break;
//                 case EH:
//                     (*T)->BF = L->BF= EH;
//                     break;
//                 case RH:
//                     (*T)->BF = EH;
//                     L->BF = LH;
//                     break;
                
//             }
//             Lr->BF = EH;
//             L_Rotate(&L);        /*对*T 的左子树作左旋转处理*/
//             R_Rotate(T);        /*对*T 作右旋转处理*/
//     }
// }

// void R_Rotate(Bitree *T)
// { 
//     Bitree L=(*T)->lchild;                 /*L 指向*T 左子树根结点*/
//     (*T)->lchild=L->rchild;                 /*L 的右子树挂接*T 的左子树*/
//     L->rchild=*T; *T=L;             /* *L 指向新的根结点*/
// }

// void L_Rotate(Bitree *T)
// { 
//     Bitree Lr=(*T)->rchild;                 /*Lr 指向*T 右子树根结点*/
//     (*T)->rchild=Lr->lchild;                 /*L 的左子树挂接*p 的右子树*/
//     Lr->lchild=*T; 
//     *T=Lr;                                     /* *L 指向新的根结点*/
// }
/*若在平衡的二叉排序树T 中不存在和e 有相同关键码的结点，则插入一个数据元素为e 的*/
/*新结点，并反回1，否则反回0。若因插入而使二叉排序树失去平衡，则作平衡旋转处理，*/        
/*布尔型变量taller 反映T 长高与否*/    
// int InsertAVL(Bitree *T,ElemType e,bool *taller)
// {
//     if(!*T)                /*插入新结点，树“长高”，置taller 为TURE*/
//     {
//     	printf("%d\n",e );
//         (*T)=(Bitree)malloc(sizeof(BitreeNode));
//         (*T)->data = e;
//         (*T)->lchild = (*T)->rchild = NULL;
//         (*T)->BF = EH;
//         //*taller = true;
//     }
//     else
//     {
//         if(e==(*T)->data)        /*树中存在和e 有相同关键码的结点，不插入*/
//         {
//             *taller = false;
//             return 0;
//         }    
//         if(e<(*T)->data)
//         {
//             if(!InsertAVL(&(*T)->lchild,e,taller))    return 0;  /*未插入*/
//             if(*taller)
            // switch((*T)->BF)
            // {    
            //     case EH :                    /*原本左、右子树等高，因左子树增高使树增高*/
            //         (*T)->BF=LH;
            //         *taller=true;
            //         break;
                
            //     case LH :                    /*原本左子树高，需作左平衡处理*/
            //         LeftBalance(T);
            //         *taller=false;
            //         break;
                
            //     case RH :                    /*原本右子树高，使左、右子树等高*/
            //         (*T)->BF=EH; 
            //         *taller=false;
            //         break;
                    
            // }
            
//         }
//         else
//         {
//             if(!InsertAVL(&(*T)->rchild,e,taller))    return 0;  /*未插入*/
//             if(*taller)
//             switch((*T)->BF)
//             {    
//                 case EH :                    /*原本左、右子树等高，因右子树增高使树增高*/
//                     (*T)->BF=RH;
//                     *taller=true;
//                     break;
                
//                 case LH :                    /*原本左子树高，使左、右子树等高*/
//                     (*T)->BF=EH; 
//                      *taller=false;
//                      break;
                
//                 case RH :                    /*原本右子树高，需作右平衡处理*/
//                     RightBalance(T);
//                     *taller=false;
//                      break;
                    
//             }
//         }
//     }
//     return 1;
// }



/*对以*p 指向的结点为根的子树，作左平衡旋转处理，处理之后，*p 指向的结点为子树的新根*/
