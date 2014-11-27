#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myatric.h"

// List Of Libs that Included
typedef struct loli {
	char* name;
	struct loli* next;
} loli; // so kawaii~

loli* loli_head = NULL;

int loli_check(char* name0){
	loli* curr;
	int size;
	for(curr=loli_head;curr!=NULL;curr=curr->next){
		size = strlen(curr->name);
		if(!strncmp(curr->name, name0, size)) return 0;
	}
	return 1;
}

void loli_add(char* name0){
	int size = strlen(name0);
	loli* new_loli = (loli*)malloc(sizeof(loli)); // so much lolies :3
	new_loli->name = (char*)malloc(size);
	strncpy(new_loli->name, name0, size);
	new_loli->next = loli_head;
	loli_head = new_loli;
}

FILE* open_lib(char* name, int local_flag){
	char* fn = (char*)malloc(MAX_PATH);
	FILE* f;
	sprintf(fn, "%s%s%d", local_flag ? "./" : "/usr/includes/", name, 0);
	printf("Try open %s lib... ", name);
	if((f = fopen(fn, "r"))==NULL) {
		printf("error.\n");
		return NULL;
	}
	printf("done.\n");
	return f;
}

void include_check(char* str){
	
}
