#define STATE_ZERO 0
#define STATE_COMM 1
#define STATE_COMM_BLOCK 2
#define STATE_STRING 3
#define STATE_STRING_MINI 4

#define TYPE_ID 5
#define TYPE_FUNC 6
#define TYPE_TYPE 7

#define ACTION_NOTHING 8
#define ACTION_CHECK_FUNC 9
#define ACTION_PROBABLE_BLOCK 10
#define ACTION_CREATE_ELEMENT 11

#define BUF_SIZE 256
#define MAX_ID 64
#define MAX_PATH 64

#define ISSYMBOL(a) (((a)>=48 && (a)<=57)||((a)>=65 && (a)<=90)||((a)>=97 && (a)<=122)||((a)==95))
#define NESYMBOL(a) ((a)!='\r' && (a)!='\t' && (a)!=' ' && (a)!='\n')
#define NMSYMBOL(a) ((a)>='0' && (a)<='9')
#define BNSYMBOL(a) (((a)>='0' && (a)<='9') || ((a)>='A' && (a)<='Z'))

// interface

// myatric
void readfile();
void process_buf(); // take buffer, make magic
void lf_bracket(int i, char* type); // looking for bracket

// element - char seq that can be id, func, type or smth else
void element_add(char* name0, int* counter0, char t); // i've nothin' to say
void element_tryadd(char* name0, char t); // oh rly?
void element_destuction(); // how can I clean this with fork?
void element_reset_counter(); // reset counter of last added element
void element_typeadd(char* name0, char t); // for remembering types from includes

// eis - stack of expected identificators
typedef struct eis {
	char expected_type;
	char action;
	struct eis* next;
} eis;
void eis_push(char type, char act); // push baby push
eis* eis_pop(); // wanna take some data from eis?

// rules - list of rules, just some ancient magic
void rules_init(int* ifz, int* cyclez);
int rules(char* buf);
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                        int rules(char* buf)                         *
 * Return 1 if u should break buf processing, 0 else                   *
 *      This func push to eis if you need to                           *
 *           Also it can use include_check                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// include_cheker - check includes recursively.
// also it's most kawaii file of this project, nya~
void include_check(char* str); // str like <lib.h> or "lib.h"

