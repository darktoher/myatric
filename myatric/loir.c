#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myatric.h"

typedef struct loir{
	char* str;
	char size;
	char type;
	struct loir* next;
} loir;

loir* loir_head = NULL;
loir* loir_subhead = NULL;

void loir_add(char* str, char size0, char type0){
	loir* tdm = loir_subhead = loir_head;
	char i;
	
	loir_subhead = loir_head = (loir*)malloc(sizeof(loir));
	loir_head->str = (char*)malloc(size0);
	for(i=0;i<size0;i++) *(loir_head->str + i) = *(str + i);
	loir_head->size = size0;
	loir_head->type = type0;
	loir_head->next = tdm;
}

void loir_clean(){
	for(loir_subhead=NULL;loir_head!=NULL;loir_head=loir_head->next){
		if(loir_subhead){
			free(loir_subhead->str);
			free(loir_subhead);
		}
		loir_subhead = loir_head;
	}
	if(loir_subhead){
		free(loir_subhead->str);
		free(loir_subhead);
	}
	loir_subhead = loir_head = NULL;
}

char loir_take_type(){
	return loir_subhead->type;
}

char* loir_take_str(){
	return loir_subhead->str;
}

void loir_pop(){
	loir_subhead = loir_subhead->next;
	if(!loir_subhead) loir_clean();
}
