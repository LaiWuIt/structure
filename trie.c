#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define CHARACTER_NUM  26

/*字典树结构*/
typedef struct trie{
	struct trie *dict[CHARACTER_NUM];
	void *character;
	int flag;
}trie;


trie *dictTrieCreate(char *str);                        /*字典树的创建*/
trie *dictTrieAddNode(trie *strie, char *str);    		/*添加节点*/
int  dictTrieSearchNode(trie *strie, char *str);  		/*查找节点*/
int  dictTrieDeleteNode(trie *strie, char *str);		/*删除节点*/

/*字典树的创建*/
trie *dictTrieCreate(char *str){
	trie *dict;
	int i;
	if((dict = (trie *)malloc(sizeof(*dict))) == NULL)
		return NULL;
	dict->flag = 0;										//区分该节点与其祖先节点能否成为一个单词 0.否 1.是
	dict->character = str;
	for(i = 0; i < CHARACTER_NUM; i++){
		dict->dict[i] = NULL;
	}

	return dict;
}

/*添加节点*/
trie *dictTrieAddNode(trie *strie, char *str){
	trie *dict,*node;
	dict = strie;
	int flag = 0;
	while(*str != '\0'){
		if(dict->dict[*str-'a'] != NULL){
			dict = dict->dict[*str-'a'];
			str++;
		}else{
			if((node = (trie *)malloc(sizeof(*node))) == NULL)
				return NULL;
			node->character = str;
			node->flag = 0;
			int i;
			for(i = 0; i < CHARACTER_NUM; i++){
				node->dict[i] = NULL;
			}
			
			dict->dict[*str-'a'] = node;
			dict = dict->dict[*str-'a'];
			str++;
		}
	}
	if(dict->flag == 0) dict->flag = 1;					//区分该节点与其祖先节点能否成为一个单词

	return strie;
}

/*查找节点 -1:不存在 0:存在*/
int dictTrieSearchNode(trie *strie, char *str){
	trie *node = strie;
	
	while(*str != '\0'){
		if(node->dict[*str-'a'] == NULL){
			return -1;
		}
		node = node->dict[*str-'a'];
		str++;
	}
	return 0;
}

/*删除节点*/
int  dictTrieDeleteNode(trie *strie, char *str){
	int flag = -1,i,len;
	len = strlen(str);
	if(strie->dict[*str-'a'] == NULL){
		return -1;
	}else{
		if(strlen(str) == 1){							//仅有一个单词时
			if(strie->dict[*str-'a']->flag){
				trie *parent = strie->dict[*str-'a'];
				for(i = 0; i < CHARACTER_NUM; i++){
					if(parent->dict[i] != NULL){
						flag = -1;break;
					}else{flag = 0;} 
				}
				if(flag == 0){						   //节点里不存在其他节点
					free(strie->dict[*str-'a']);
					strie->dict[*str-'a'] = NULL;
				}else{
					strie->dict[*str-'a']->flag = 0;
				}
			}else{
				return -1;
			}
		}else{
			flag = dictTrieDeleteNode(strie->dict[*str-'a'], str+1);
			trie *parent = strie->dict[*str-'a'];
			for(i = 0; i < CHARACTER_NUM; i++){
				if(parent->dict[i] != NULL){
					flag = -1;break;
				}else{flag = 0;} 
			}
			if(flag == 0 && !strie->dict[*str-'a']->flag){			//节点里不存在其他节点
				free(strie->dict[*str-'a']);
				strie->dict[*str-'a'] = NULL;
			}
		}
		return flag;
	}
}

int main(){
	trie *dict = dictTrieCreate("/");
	dictTrieAddNode(dict, "hello");
	dictTrieAddNode(dict, "world");
	dictTrieAddNode(dict, "worldss");
	printf("%d",dictTrieSearchNode(dict, "worldss"));
	return 0;
}



