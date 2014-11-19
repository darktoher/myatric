#include <stdio.h>
#include <stdlib.h>
#include "myatric.h"

#include <string.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                       Just a program for                            *
 *                            metering programs.                       *
 * Warning: it can't cure cancer.                                      *
 * Version 0.8.2                                                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// global
int linez;
int elinez;
int commz;
int ifz;
int cyclez;
int max_depth;

int state;
int curr_depth;

char* buf;
int ind;
char empty_flag;

FILE* f;


void readfile(){	
	char c, b=0;
	
	while(fscanf(f, "%c", &c) != EOF ){
		*(buf+ind) = c;
		ind++;
		
		switch (state) {
		case STATE_ZERO:
			switch (c) {
			case '\n':
				linez++;
				process_buf();
			break;
			case '\"':
				process_buf();
				state = STATE_STRING;
			break;
			case '\'':
				process_buf(); 
				state = STATE_STRING_MINI;
			break;
			case '/':
				if(b == '/') { commz++; process_buf(); state = STATE_COMM; }
			break;
			case '*':
				if(b == '/') { commz++; process_buf(); state = STATE_COMM_BLOCK; }
			break;
			}
		break;
		case STATE_COMM:
			switch (c) {
			case '\n':
				linez++;
				process_buf();
				state = STATE_ZERO;
			break;
			}
		break;
		case STATE_COMM_BLOCK:
			switch (c) {
			case '\n':
				linez++;
				process_buf();
			break;
			case '/':
				if(b == '*') { process_buf(); state = STATE_ZERO; }
			break;
			}
		break;
		case STATE_STRING:
			switch (c) {
			case '\n':
				linez++;
				process_buf();
			break;
			case '\"':
				if(b != '\\') { process_buf(); state = STATE_ZERO; }
			break;
			}
		break;
		case STATE_STRING_MINI:
			switch (c) {
			case '\n':
				linez++;
				process_buf();
			break;
			case '\'':
				if(b != '\\') { process_buf(); state = STATE_ZERO; }
			break;
			}
		break;
		}
		
		
		
		b = c;
	}
	
	
	
}

void process_buf(){	
	int i;
	char* id_buf = (char*)malloc(32);
	char ind0 = 0;
	char m_type = TYPE_TYPE;
	
	empty_flag = 1;
/*	printf("state = %d, ind = %d, buf = ", state, ind);
	for(i=0;i<ind;i++) printf("%d,", *(buf+i));
	printf("\n");*/
	
	for(i=0;i<ind;i++)
		if(NESYMBOL(*(buf+i))) {
			printf("i = %d\n", i);
			empty_flag = 0;
			break;
		}
	
	if(empty_flag) elinez++;
	
	if(state==STATE_ZERO) {
		for(i=0; i<ind;i++){
			if(ISSYMBOL(*(buf+i))) {
				*(id_buf+ind0) = *(buf+i);
				if(ind0++ > 31) { printf("Error: impossibru identificator's size\n"); exit(1); }
			}
			else {
				if(ind0) { *(id_buf+ind0)=0; ind0=0; element_tryadd(id_buf, m_type); }
			}
		}
		
	}
	
	ind = 0;
}

void lf_bracket(int i, char* type){
	int j=0;
	
	*type = TYPE_ID;
	if(ISSYMBOL(*(buf+j))) { printf("Error: lf worked uncorrently\n"); exit(1); }
	
	for(j=i;j<ind;j++){
		if(!NESYMBOL(*(buf+j))) continue;
		if(*(buf+j) == '(') { *type = TYPE_FUNC; return; }
		else return;
	}
}

int main(int argc, char** argv){
	if((f = fopen(*(argv+1),"r")) == NULL) { printf("Error: can't read file\n"); exit(1); }
	
	elinez = commz = ifz = cyclez = max_depth = curr_depth = 0;
	linez = 1;
	state = STATE_ZERO;
	buf = (char*)malloc(BUF_SIZE);
	ind = 0;
	empty_flag = 1;
	
	//~ aladdin_head = NULL;
	//~ eis_head = NULL;
	
	rules_init();
	
	element_tryadd((char*)"if", 0);
	
	readfile();
	
	//~ printf("t_%d\ns_%d\nr_%d\nn_%d\n", '\t', ' ', '\r', '\n'); 
	
	//~ printf("a_%d\nz_%d\nA_%d\nZ_%d\n__%d\n1_%d\n9_%d\n0_%d\n", 'a', 'z', 'A', 'Z', '_', '1', '9', '0'); 
	
	printf("Lines: %d\nNon-empty lines: %d\nComments: %d\nIfs: %d\nCycles: %d\nMax depth: %d\n",
		linez, linez-elinez, commz, ifz, cyclez, max_depth);
	//~ int i;
	//~ for(i=1;i<=122;i++)
		//~ printf("-- N_%d, S_%c, sym=%d, fk=%d\n", i, i, ISSYMBOL(i), NESYMBOL(i));
	
	//~ char aa[] = {'a', 'b', 'c'};
	//~ char* aa = (char*)"abc";
	//~ printf("%d, %d, %d, %d,0 %d, %d, %d, %d, %d\n", *aa, *(aa+1), *(aa+2), *(aa+3), *(aa+4), *(aa+5), *(aa+6), *(aa+7), *(aa+8));
	
	//~ printf("%d\n%s\n", (int)strlen(aa), aa);
	
	element_destuction();
	
	return 0;
}



