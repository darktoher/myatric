#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myatric.h"

typedef struct element {
	char* name;
	int* counter;
	char type;
	char t_flag;
	struct element* next;
} element;

element* aladdin_head = NULL;

void element_add(char* name0, int* counter0, char t){
	int size = strlen(name0);
	if(NMSYMBOL(*name0)) return;
	if(aladdin_head==NULL) {
		aladdin_head = (element*)malloc(sizeof(element));
		aladdin_head->name = (char*)malloc(size);
		strncpy(aladdin_head->name, name0, size);
		aladdin_head->counter = counter0;
		*(aladdin_head->counter) = 0;
		aladdin_head->type = t;
		aladdin_head->t_flag = 0;
		aladdin_head->next = NULL;
		return;
	}
	element* curr;
	curr = (element*)malloc(sizeof(element));
	curr->name = (char*)malloc(size);
	strncpy(curr->name, name0, size);
	curr->counter = counter0;
	*(curr->counter) = 0;
	curr->type = t;
	curr->t_flag = 0;
	curr->next = aladdin_head;
	
	aladdin_head = curr;
}

void element_tryadd(char* name0, char t){
	int size = strlen(name0);
	if(NMSYMBOL(*name0)) return;
	if(aladdin_head==NULL) {
		aladdin_head = (element*)malloc(sizeof(element));
		aladdin_head->name = (char*)malloc(size);
		strncpy(aladdin_head->name, name0, size);
		aladdin_head->counter = (int*)malloc(sizeof(int));
		*(aladdin_head->counter) = 1;
		aladdin_head->type = t;
		aladdin_head->t_flag = 1;
		aladdin_head->next = NULL;
		return;
	}
	// find in names
	element* curr;
	for(curr = aladdin_head; curr != NULL; curr = curr->next){
		if(!strcmp(curr->name, name0)) {
			(*(curr->counter))++;
			return;
		}
	}
	// np, so just add new
	curr = (element*)malloc(sizeof(element));
	curr->name = (char*)malloc(size);
	strncpy(curr->name, name0, size);
	curr->counter = (int*)malloc(sizeof(int));
	*(curr->counter) = 0;
	curr->type = t;
	curr->t_flag = 1;
	curr->next = aladdin_head;
	
	aladdin_head = curr;
}

void element_destuction(){
	element* curr;
	while(aladdin_head != NULL){
		curr = aladdin_head;
		aladdin_head = aladdin_head->next;
		
		printf("=--=%s, %d\n",curr->name, curr->type);
				
		free(curr->name);    // forget your name.
		if(curr->t_flag)     // if others give you a price
		free(curr->counter); // forget your price.
		free(curr);          // forget yourself.
		                     // now you totally free.
	}
}

