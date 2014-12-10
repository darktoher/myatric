#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myatric.h"

void rules_init(int* ifz, int* cyclez){
	element_add((char*)"if", ifz, TYPE_ID);
	element_add((char*)"switch", ifz, TYPE_ID);
	element_add((char*)"for", cyclez, TYPE_ID);
	element_add((char*)"while", cyclez, TYPE_ID);
	
	element_tryadd((char*)"break", TYPE_ID);    element_reset_counter();
	element_tryadd((char*)"continue", TYPE_ID); element_reset_counter();
	element_tryadd((char*)"goto", TYPE_ID);     element_reset_counter();
	
	element_tryadd((char*)"void", TYPE_TYPE);   element_reset_counter();
	element_tryadd((char*)"char", TYPE_TYPE);   element_reset_counter();
	element_tryadd((char*)"int", TYPE_TYPE);    element_reset_counter();
	element_tryadd((char*)"float", TYPE_TYPE);  element_reset_counter();
	element_tryadd((char*)"double", TYPE_TYPE); element_reset_counter();
}

void rules(char* buf){
	char* str;
	int size = strlen(buf);
	int i,j;	
	
	for(i=0;i<size;i++){
		if(NESYMBOL(*(buf+i))) break;
	}
	
	if(i == size) return; // empty string
	
	str = (char*)malloc(size-i);
	for(j=0;j<size-i;j++) *(str+j) = *(buf+j+i);
	
	// check some # sequences
	if(*(str) == '#') {
		// #define - next word labeled as identifier
		if(!strncmp(str, "#define", 7) {
			eis_push(0, ACTION_DROP_LINE);
			eis_push(TYPE_ID, ACTION_CREATE_ELEMENT);
			return;
		}
		// all others ignored
		else {
			eis_push(0, ACTION_DROP_LINE);
			free(str);
			return;
		}
	}
	
	return 0;
}
