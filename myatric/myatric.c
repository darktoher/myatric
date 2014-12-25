#include <stdio.h>
#include <stdlib.h>
#include "myatric.h"
#include <string.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                       Just a program for                            *
 *                            metering programs.                       *
 * Warning: it can't cure cancer.                                      *
 * Version 0.9.4                                                       *
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

int num_op;
int num_func;


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
			case '{':
				curr_depth++;
				if(curr_depth > max_depth) max_depth = curr_depth;
			break;
			case '}':
				curr_depth--;
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
	empty_flag = 1;
	char m_type = 0;
	char* str = (char*)malloc(32);
	int stri = 0;
	
	if(state==STATE_ZERO)
	for(i=0;i<ind;i++){
		if(!m_type){
			switch (get_type(*(buf+i))){
			case TYPE_NUM:
				m_type = TYPE_NUM;
				*(str+stri++) = *(buf+i);
			break;
			case TYPE_ID:
				m_type = TYPE_ID;
				*(str+stri++) = *(buf+i);
			break;
			case TYPE_SPECIAL:
				loir_add(buf+i, 1, TYPE_SPECIAL);
			break;
			case TYPE_OPERATOR:
				m_type = TYPE_OPERATOR;
				*(str+stri++) = *(buf+i);
			break;
			}
		}
		else{
			if( (m_type == get_type(*(buf+i))) || (m_type==TYPE_ID && get_type(*(buf+i))==TYPE_NUM) || (m_type==TYPE_NUM && get_type(*(buf+i))==TYPE_ID) ){
				*(str+stri++) = *(buf+i);
			}
			else{
				loir_add(str, stri, m_type);
				m_type = 0;
				stri = 0;
				i--;
			}
		}
		
	}
	
	for(i=0;i<ind;i++)
		if(NESYMBOL(*(buf+i))) {
			empty_flag = 0;
			break;
		}
	
	if(empty_flag) elinez++;	
	ind = 0;
	
	if(!empty_flag && state==STATE_ZERO) rules();
	
	free(str);
}

char get_type(char c){
	if(NMSYMBOL(c)) return TYPE_NUM;
	if(ISSYMBOL(c)) return TYPE_ID;
	if(c=='{' || c=='}' || c=='(' || c==')' || c=='#' || c=='[' || c==']' || c==';') return TYPE_SPECIAL;
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='=' || c=='|' || c=='&' || c=='%' || c=='!' || c=='<' || c=='>' || c=='?') return TYPE_OPERATOR;
	return 0;
}

void inc_op() { num_op++; }
void inc_func() { num_func++; }

int main(int argc, char** argv){
	if((f = fopen(*(argv+1),"r")) == NULL) { printf("Error: can't read file\n"); exit(1); }
	
	elinez = commz = ifz = cyclez = max_depth = curr_depth = num_op = num_func = 0;
	linez = 1;
	state = STATE_ZERO;
	buf = (char*)malloc(BUF_SIZE);
	ind = 0;
	empty_flag = 1;
	
	rules_init(&ifz, &cyclez);
		
	readfile();
	
	printf("Lines: %d\nNon-empty lines: %d\nComments: %d\nIfs: %d\nCycles: %d\nMax depth: %d\n",
		linez, linez-elinez-1, commz, ifz, cyclez, max_depth);
	//~ printf("Lines: %d\nEmpty lines: %d\nComments: %d\nIfs: %d\nCycles: %d\nMax depth: %d\n",
		//~ linez, elinez, commz, ifz, cyclez, max_depth);
	
	
	element_destuction();
	
	return 0;
}



