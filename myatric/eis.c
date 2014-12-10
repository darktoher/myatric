#include <stdio.h>
#include <stdlib.h>
#include "myatric.h"

typedef struct eis {
	char expected_type;
	char action;
	struct eis* next;
} eis;

eis* eis_head = NULL;
// konsolidacii mnozhestva rabochih nagruzkov

void eis_push(char type, char act){
	eis* tdm = eis_head;
	
	eis_head = (eis*)malloc(sizeof(eis));
	eis_head->expected_type = type;
	eis_head->action = act;
	eis_head->next = tdm;
}

void eis_pop(){
	eis* tdm = eis_head;
	
	if(eis_head==NULL) return;
	eis_head = eis_head->next;
	
	free(tdm);
}

char eis_take_action(){
	if(eis_head == NULL) return ACTION_NOTHING;
	return eis_head->action;
}

char eis_take_type(){
	if(eis_head == NULL) { printf("Error: try take eis type from nowhere\n"); exit(1); }
	return eis_head->action;
}



