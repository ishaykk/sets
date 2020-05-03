// Final Ex by Ishay Kaplan, class 43/6
#include "sets.h"
char operators[][14] = { "read_set", "print_set", "union_set", "intersect_set", "sub_set", "comp_set" };
int maxGroupsPerCmd[] = { 1,1,3,3,3,2 }; // max group count per command (e.g. read set is 1, print_set 1, union_set 3 etc...)

// func receive sets array, group index, values array (input from user), values count
// if set isn't empty, initialize set to zeroes with cleanSet()
// then loop on values array, initialize the set accordingly to values array (arr) 
// if v_count > 0 init set to not empty (0), else init set to 1
void read_set(Set sets[], int grp, int *arr, int v_count) {
	if (sets[grp].empty == 0)
		cleanSet(sets, grp);
	for (int i = 0; i < v_count; i++)
		sets[grp].values[arr[i]] = 1; 
	if (v_count)
		sets[grp].empty = 0; 
	else
		sets[grp].empty = 1;
}

// func recive a set and group index (0 is A, 1 is B etc...)
// if set is not empty func will print set values
void print_set(Set set, int grp) {
	int count = 0, i;
	if (set.empty == 0) {
		for (i = 0; i < MAX_VALUES; i++) {
			if (grp >= 0 && set.values[i]) {
				printf("%-3d ", i);
				count++;
			}
			if (count == 16) { // new line after 16 values
				printf("\n");
				count = 0;
			}
		}
		printf("\n");
	}
	else
		printf("%c is an empty set!\n", grp + 'A');
}
// func receive sets array, group count, group array, command index
// func make a temporary set and print it or save it in a set accordingly to the command
void operations(Set sets[], int g_count, int grp[], int cmd_i) {
	Set tmp = { {0},1 }; // temp set, values array initialize to zero and empty field to 1
	int i, flag1 = 1, flag2 = 1, atleast1 = 0;
	if (sets[grp[0]].empty) // check if first set is empty
		flag1 = 0;
	if (g_count > 1 && sets[grp[1]].empty) // if group count is more than 1 check second check if empty
		flag2 = 0;
	if (flag1 || flag2 || cmd_i == 5) { // step in if at least 1 group is not empty or command is comp_set (cmd_i == 5)
		for (i = 0; i < MAX_VALUES; i++) {
			if (decidingFunc(sets, grp, i, cmd_i, flag1, flag2)) { // get a answer from dicidingFunc if logical action was true or false
				tmp.values[i] = 1; // logical action was true
				atleast1 = 1;
			}
		}
		if (atleast1)
			tmp.empty = 0; // if there is atleast one "1" in tmp set then change empty field to 0
	}
	if (g_count == 3 || (cmd_i == 5 && g_count == 2)) { // if group count is 3 or if command was comp_set 
		if (cmd_i == 5) // command == comp_set, save tmp set in 2nd set
			sets[grp[1]] = tmp;
		else
			sets[grp[2]] = tmp; // command was union_set/intersect_set/sub_set, save tmp set in 3rd set
	}
	else if (!tmp.empty) // if tmp set is not empty print it
		print_set(tmp, 0);
}

// func recive sets array, groups array, command index, flag1 (set1 is empty or not), flag2( set2 is empty or not)
// func do the logical action accordingly to command index, e.g. if cmd_i == 2 do a union logical action
// func returns 1 or 0 accordingly to the logical action
int decidingFunc(Set sets[], int grp[], int i, int cmd_i, int flag1, int flag2) {
	int res = 0;
	switch (cmd_i) {
	case 2: if (flag1 && sets[grp[0]].values[i] || flag2 && sets[grp[1]].values[i])
		res = 1;
		break;
	case 3: if (sets[grp[0]].values[i] && sets[grp[1]].values[i])
		res = 1;
		break;
	case 4: if (sets[grp[0]].values[i] && !sets[grp[1]].values[i])
		res = 1;
		break;
	case 5: if (!sets[grp[0]].values[i])
		res = 1;
		break;
	default: printf("invalid func index\n");
	}
	return res;
}

// function receive sets array and index (of set)
// func initialize that set values to zeroes
void cleanSet(Set sets[], int index) {
	for (int i = 0; i < MAX_VALUES; i++)
		sets[index].values[i] = 0;
}

// func recive command index and group count
// func compares group count and maxGroupPerCmd array
// if group array is larger returns false, else returns true
int isNumGroupsValid(int cmd_i, int g_count) {
	if (maxGroupsPerCmd[cmd_i] >= g_count)
		return 1;
	printErrors(4, 0);
	return 0;
}

// func recive sets array, command index, values arr, group count, group array, and values count
// func launch read_set if cmd_i=0, print_set if cmd_i = 1, else launch opertaions() for union_set, intersect_set, sub_set and comp_set
void adapter(Set sets[], int cmd_i, int *values, int g_count, int g_arr[], int v_count) {
	switch (cmd_i) {
	case 0: read_set(sets, g_arr[0], values, v_count);
		break;
	case 1: print_set(sets[g_arr[0]], g_arr[0]);
		break;
	case 2:
	case 3:
	case 4:
	case 5: operations(sets, g_count, g_arr, cmd_i);
		break;
	}
}

// func receive and string and check if it appear in operators array
// if yes returns operator index + 1
// if not returns 0;
int isCmdValid(char *cmd) { // check if command is valid, returns true or false
	for (int i = 0; i < LENGTH(operators); i++) { // check input groups A,B,C,D,E,F...
		if (!strcmp(cmd, operators[i]))
			return i + 1;
	}
	printf("No such command!\n");
	return 0;
}

// func receive a number and returns true if it's between 0-127, else returs false
int isInRange(int num) {
	return (num >= 0 && num <= 127) ? 1 : 0;
}

// func receive an int pointer (dynamic array) and size
// func realloc dynamic array to new size
// func return new pointer if realloc succeded, else returns null
int * reallocTmpArray(int *arr, int size) {
	int *p = (int*)realloc(arr, size * sizeof(int));
	if (!p)
		printf("Error Reallocating memory, please try again\n");
	return p;
}
// func print error accordingly to index that was send and returns zero
int printErrors(int index, int val) {
	switch (index) {
	case 1: printf("%d is out of range\n", val);
		break;
	case 2: printf("Error Allocating memory");
		break;
	case 3: printf("invalid values, please try again\n");
		break;
	case 4: printf("No such command\n");
		break;
	case 5: printf("Set didn't end with -1\n");
		break;
	case 6: printf("No such set\n");
		break;
	}
	return 0;
}

// func receive a char and returns true if its a numeric number, else 0
int is_a_num(char ch) {
	return (ch >= '0' && ch <= '9') ? 1 : 0;
}

// func receive a string and group array
// func returns group count if group syntax is valid
// else print error and returns 0
int grp_input(char str[], int grp[]) {
	int flag = 1, g_count = 0;
	while (str && flag > 0) {
		if (str[0] >= 'A' && str[0] <= 'Z') {
			if (str[0] > 'F') {
				flag = printErrors(6, 0); 
				g_count = 0;
			}
			else
				grp[g_count++] = str[0] - 'A';
			str++;
		}
		else if (str[0] == ' ' || str[0] == ',')
			str++;
		else if (str[0] == '\0' || is_a_num(str[0])) // str ends or str[0] is a number
			flag = 0;
		else if (str[0] != ',')
			flag = printErrors(6, 0);
	}
	return g_count;
}

// func receive a string, pointer to value count, values dynamic array, pointer to flag
// func valide values and if it's valid returns it
// else it will return null
int * val_input(char str[], int *v_count, int *values, int *flag) {
	int i, j, tmp_num_count = 0, tmpsum = 0;
	int *tmp_num = (int*)malloc(sizeof(int)); // dynamic arr for each character (e.g. 123 is {{1},{2},{3})
	(*flag) = 1;
	if (tmp_num != NULL && values) { // if allocations succeded
		if (str[0] == '\0') // check if str is empty
			(*flag) = printErrors(4, 0);
		while (str[0] && str[1] && (*flag) > 0) {
			if (str[0] >= '0' && str[0] <= '9') {
				if (tmp_num = reallocTmpArray(tmp_num, tmp_num_count + 1)) // change tmp_num array size
					tmp_num[tmp_num_count++] = str[0] - '0'; // convert ascii to decimal and init in tmp_num array
				else (*flag) = printErrors(2, 0); // if realloc failed prit error and change flag
			}
			else if (str[0] == ' ' || str[0] == ',') {
				if (str[0] == ',' && str[1] == ',') // check for double comma 
					(*flag) = printErrors(3, 0); // change flag to 0 and print error
				if ((*flag) && tmp_num_count) { // if flag isn't 0 and there is a numeric value
					if (values = reallocTmpArray(values, (*v_count) + 1)) {
						for (tmpsum = 0, i = tmp_num_count, j = 0; i > 0; i--, j++)
							tmpsum += tmp_num[j] * pow(10, i - 1); // convert ascii to decimal
						if (isInRange(tmpsum)) { // check if value is in rage 0-127
							values[(*v_count)++] = tmpsum; // init value in values array
							tmp_num_count = 0; // reset tmp_num count to 0
						}
						else
							(*flag) = printErrors(1, tmpsum); // value is not in range
					}
					else
						(*flag) = printErrors(2, 0); // allocation failed
				}
			}
			else if (str[0] == '-' && str[1] == '1')  (*flag) = -1; // -1 is in string, stop loop
			else (*flag) = printErrors(3, 0); // invalid char was entered, change flag and print error
			if ((*flag) > 0)
				str++; // mov pointer to next char
		}
	}
	free(tmp_num); // free tmp_num array
	if (flag > -1) { // if values don't contain -1 print error
		printErrors(5, 0);
	}
	return values; // return pointer to dynamic array
}

//func receive sets array and string (input from user)
// func validates input (command, groups (and values in read_set))
// if all the input is valid send it to adapter() for further actions
void splitter(Set sets[], char cmd[]) {
	char *p;
	int *values, flag = -1, group_arr[4], cmd_i, grp_counter = 0, val_count = 0;
	if (values = (int*)malloc(sizeof(int))) { // allocate memory for dynamic values array
		p = strtok(cmd, " "); // p is string until space, command only (e.g. read_set)
		if (cmd_i = isCmdValid(p)) { // get cmd index (e.g. read_set is 1, print_set 2 etc...)
			p = strtok(NULL, "\n"); // p is string untill end (\n) (e.g. A,1,2,3,-1)
			grp_counter = grp_input(p, group_arr); // get group count
			if (grp_counter && isNumGroupsValid(cmd_i - 1, grp_counter)) { // check if group count isn't 0 and group count is valid to the command
				if (cmd_i - 1 == 0) { // if command was read_set
					values = val_input(++p, &val_count, values, &flag); // validate values and put it in values dynamic arr
					if (values == NULL)
						flag = printErrors(2, 0); // if allocation failed change flag and print error
				}
				if (flag == -1) // there was -1 in values or command was not read_set
					adapter(sets, cmd_i - 1, values, grp_counter, group_arr, val_count); // launch function according to command
			}
		}
	}
	else printErrors(2, 0); // allocation failed
	free(values); // free values dynamic array
}

// menu func
void menu(Set sets[]) {
	char cmd[256]; 
	printf("Commands are: ");
	for (int i = 0; i < LENGTH(operators); i++)
		printf("%s ", operators[i]);
	printf("\nRange of values 0-127, end set with -1\n");
	printf("To exit type :halt\n@");
	gets(cmd);
	while (strcmp(cmd, ":halt")) {
		if (strcmp(cmd, "")) // user pressed ENTER
			splitter(sets, cmd);
		printf("@");
		gets(cmd);
	}
}