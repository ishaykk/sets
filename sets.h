// Final Ex by Ishay Kaplan, class 43/6
#include <stdio.h>
#include <string.h>
#include <math.h>
#define LENGTH(array) (sizeof(array) / sizeof(*(array)))
#define MAX_GROUPS 6
#define MAX_VALUES 128
#define MAX_GRP_PER_CMD 3
// set struct
typedef struct set {
	int values[MAX_VALUES];
	int empty;
}Set;
void read_set(Set sets[], int grp, int *arr, int v_count);
void operations(Set sets[], int g_count, int grp[], int cmd_i);
int decidingFunc(Set sets[], int grp[], int i, int cmd_i, int flag1, int flag2);
void cleanSet(Set sets[], int index);
void adapter(Set sets[], int cmd_i, int *values, int g_count, int g_arr[], int v_count);
int isCmdValid(char *cmd);
int is_a_num(char ch);
int isInRange(int num);
int * reallocTmpArray(int *arr, int size);
int printErrors(int index, int val);
int is_a_num(char ch);
int grp_input(char str[], int grp[]);
int * val_input(char str[], int *v_count, int *values, int *flag);
void splitter(Set sets[], char cmd[]);
void menu(Set sets[]);