#include <stdio.h>
#include <stdlib.h>
#include "myatric.h"

eis* eis_head = NULL;
// konsolidacii mnozhestva rabochih nagruzkov

void eis_push(char type, char act){
	eis* tdm = eis_head;
	
	eis_head = (eis*)malloc(sizeof(eis));
	eis_head->expected_type = type;
	eis_head->action = act;
	eis_head->next = tdm;
}

eis* eis_pop(){
	eis* tdm = eis_head;
	
	if(eis_head==NULL) return NULL;
	eis_head = eis_head->next;
	
	return tdm;
}





