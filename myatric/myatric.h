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
#define MAX_TYPES 128

#define ISSYMBOL(a) (((a)>=48 && (a)<=57)||((a)>=65 && (a)<=90)||((a)>=97 && (a)<=122)||((a)==95))
#define NESYMBOL(a) ((a)!='\r' && (a)!='\t' && (a)!=' ' && (a)!='\n')

// interface

// myatric
void readfile();
void process_buf(); // take buffer, make magic

// element - char seq that can be id, func, type or smth else
void element_add(char* name0, int* counter0, char t); // i've nothin' to say
void element_tryadd(char* name0, char t); // oh rly?
void element_destuction(); // how can I clean this with fork?

// eis - stack of expected identificators
typedef struct eis {
	char expected_type;
	char action;
	struct eis* next;
} eis;
void eis_push(char type, char act); // push baby push
eis* eis_pop(); // wanna take some data from eis?
