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

void rules(){
	char e_type = 0;
	while(loir_take_type()){
		switch (loir_take_type()) {
		case TYPE_ID:
			if(!e_type) e_type = TYPE_ID;
			element_tryadd(loir_take_str(), e_type);
		break;
		case TYPE_NUM:
			
		break;
		case TYPE_OPERATOR:
			inc_op();
		break;
		case TYPE_SPECIAL:
			if(loir_take_type() == '(')
			eis_push(TYPE_FUNC, ACTION_CREATE_ELEMENT);
		break;
		}
		
		if(eis_take_action() == ACTION_CREATE_ELEMENT) {
			e_type = eis_take_type();
			eis_pop();
		}
		
	//	printf("%d: %s\n", loir_take_type(), loir_take_str());
		loir_pop();
	}
	
}

