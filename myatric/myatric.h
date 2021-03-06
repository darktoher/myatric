#define STATE_ZERO 0
#define STATE_COMM 1
#define STATE_COMM_BLOCK 2
#define STATE_STRING 3
#define STATE_STRING_MINI 4

#define TYPE_ID 5
#define TYPE_FUNC 6
#define TYPE_TYPE 7
#define TYPE_OPERATOR 8
#define TYPE_SPECIAL 14
#define TYPE_NUM 15

#define ACTION_NOTHING 9
#define ACTION_CHECK_FUNC 10
#define ACTION_PROBABLE_BLOCK 11
#define ACTION_CREATE_ELEMENT 12
#define ACTION_DROP_LINE 13

#define BUF_SIZE 256
#define MAX_ID 64
#define MAX_PATH 64

#define ISSYMBOL(a) (((a)>=48 && (a)<=57)||((a)>=65 && (a)<=90)||((a)>=97 && (a)<=122)||((a)==95))
#define NESYMBOL(a) ((a)!='\r' && (a)!='\t' && (a)!=' ' && (a)!='\n')
#define NMSYMBOL(a) ((a)>='0' && (a)<='9')
#define BNSYMBOL(a) (((a)>='0' && (a)<='9') || ((a)>='A' && (a)<='Z'))

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  ______          __                     ___                           *
 * /\__  _\        /\ \__                /'___\                          *
 * \/_/\ \/     ___\ \ ,_\    __   _ __ /\ \__/   __      ___     __     *
 *    \ \ \   /' _ `\ \ \/  /'__`\/\`'__\ \ ,__\/'__`\   /'___\ /'__`\   *
 *     \_\ \__/\ \/\ \ \ \_/\  __/\ \ \/ \ \ \_/\ \L\.\_/\ \__//\  __/   *
 *     /\_____\ \_\ \_\ \__\ \____\\ \_\  \ \_\\ \__/.\_\ \____\ \____\  *
 *     \/_____/\/_/\/_/\/__/\/____/ \/_/   \/_/ \/__/\/_/\/____/\/____/  *
 *                                                                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// myatric
void readfile();
void process_buf(); // take buffer, make magic
char get_type(char c);
void inc_op();
void inc_func();

// element - char seq that can be id, func, type or smth else
void element_add(char* name0, int* counter0, char t); // i've nothin' to say
void element_tryadd(char* name0, char t); // oh rly?
void element_destuction(); // how can I clean this with fork?
void element_reset_counter(); // reset counter of last added element

// eis - stack of expected identifiers
void eis_push(char type, char act); // push baby push
void eis_pop(); // nothing but delete last pushed eis
char eis_take_action(); // wanna take some data from eis?
char eis_take_type();   // take it.

// rules - list of rules, just some ancient magic
void rules_init(int* ifz, int* cyclez); // some initial elements
void rules(); // push to eis if you need to

// loir - list of identifiers to be ruled
void loir_add(char* str, char size0, char type0);
char loir_take_type();
char* loir_take_str();
void loir_pop();
