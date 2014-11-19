#include <stdio.h>
#include <stdlib.h>
//~ #include <string.h>
#include "myatric.h"

void rules_init(){
	element_add((char*)"if", &ifz, TYPE_ID);
	element_add((char*)"switch", &ifz, TYPE_ID);
	element_add((char*)"for", &cyclez, TYPE_ID);
	element_add((char*)"while", &cyclez, TYPE_ID);
	
	element_tryadd((char*)"break", TYPE_ID);
	element_tryadd((char*)"continue", TYPE_ID);
	element_tryadd((char*)"goto", TYPE_ID);
	
	element_tryadd((char*)"void", TYPE_TYPE);
	element_tryadd((char*)"char", TYPE_TYPE);
	element_tryadd((char*)"int", TYPE_TYPE);
	element_tryadd((char*)"float", TYPE_TYPE);
	element_tryadd((char*)"double", TYPE_TYPE);
}

void rules(char* buf){
	
}
