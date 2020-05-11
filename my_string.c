#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>



MY_STRING my_string_init_default() {
	My_string* pString;
	pString = malloc(sizeof(My_string));
	if (pString != NULL) {
		pString->capacity = 7;
		pString->size = 0;
		pString->data = (char*)(malloc(sizeof(char)*(pString->capacity)));
		if (pString->data == NULL) {
			free(pString); pString = NULL;
		}
		return pString;
	}
	return NULL;
}
MY_STRING my_string_init_c_string(const char* c_string) {
	int i;
	My_string* pString;
	pString = malloc(sizeof(My_string));
	if (pString == NULL) {
		free(pString); pString = NULL;
		return pString;
	}
	for (i = 0; c_string[i] != '\0'; i++);
	pString->capacity = (i + 1);
	pString->size = i;
	pString->data = (char*)malloc(sizeof(char)*pString->capacity);
	if (pString->data == NULL) {
		free(pString->data); pString->data = NULL;
		return pString->data;
	}
	for (i = 0; i < pString->capacity; i++) {
		pString->data[i] = c_string[i];
	}
	return pString;
}
void my_string_destroy(Item_ptr* pItem_ptr) {
	My_string* pString = (My_string*)*pItem_ptr;
	free(pString->data); pString->data = NULL;
	free(pString); pString = NULL;
	*pItem_ptr = NULL;
	return;
}
int my_string_get_capacity(MY_STRING hMy_string) {
	My_string* pString = (My_string*)hMy_string;
	return pString->capacity;
}
int my_string_get_size(MY_STRING hMy_string) {
	My_string* pString = (My_string*)hMy_string;
	return pString->size;
}
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;
	int i;
	for (i = 0; i < pLeft_string->size && i < pRight_string->size; i++) {
		if (pLeft_string->data[i] < pRight_string->data[i]) {
			return -1;
			break;
		}
		else if (pLeft_string->data[i] > pRight_string->data[i]) {
			return 1;
			break;
		}
	}

	return 0;
}
char* my_string_at(MY_STRING hMy_string, int index) {
	My_string* pMy_string = (My_string*)hMy_string;
	if (!(index < 0 || index > pMy_string->size)) { //If it's inbounds
		return &pMy_string->data[index];
	}

	return NULL;

}
char* my_string_c_str(MY_STRING hMy_string) {
	char* tempArray;
	int i;
	My_string* pMy_string = (My_string*)hMy_string;
	if (pMy_string->size + 1 > pMy_string->capacity) { //resize
		tempArray = (char*)malloc(sizeof(char) * 2 * pMy_string->capacity);
		if (tempArray == NULL) {
			free(tempArray);
			return tempArray;
		}
		for (i = 0; i < pMy_string->capacity; i++) {
			tempArray[i] = pMy_string->data[i];
		}
		free(pMy_string->data); pMy_string->data = NULL;
		pMy_string->data = tempArray;
		tempArray = NULL;
		pMy_string->capacity *= 2;
	}
	pMy_string->data[pMy_string->size] = '\0';
	return pMy_string->data;
}
Boolean my_string_empty(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	//if (pMy_string == NULL || pMy_string->data == NULL) {
	if (pMy_string == NULL) {
		return TRUE;
	}
	if (pMy_string->size == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
	My_string* pMy_string = (My_string*)hMy_string;
	int i = 0;
	while (i < pMy_string->size) {
		fprintf(fp, "%c", pMy_string->data[i]);
		i++;
	}
	return SUCCESS;
}
Status my_string_push_back(MY_STRING hMy_string, char item) {
	char* tempArray;
	int i;
	My_string* pMy_string = (My_string*)hMy_string;
	if (pMy_string->size + 1 >= pMy_string->capacity) { //resize
		tempArray = (char*)malloc(sizeof(char) * 2 * pMy_string->capacity);
		if (tempArray == NULL) {
			free(tempArray);
			return FAILURE;
		}
		for (i = 0; i < pMy_string->capacity; i++) {
			tempArray[i] = pMy_string->data[i];
		}
		free(pMy_string->data); pMy_string->data = NULL;
		pMy_string->data = tempArray;
		tempArray = NULL;
		pMy_string->capacity *= 2;
	}
	pMy_string->data[pMy_string->size] = item;
	pMy_string->size++;
	return SUCCESS;
}
Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {

	int num_of_conversions, i, count = 0;
	char c;
	char* tempArray;
	My_string* pMy_string = (My_string*)(hMy_string);

	num_of_conversions = fscanf(fp, " %c", &c);
	if (num_of_conversions == 1 && num_of_conversions != EOF) {
		while (c != ' ' && c != EOF && c != '\n') {
			pMy_string->data[count] = c;
			pMy_string->size = count + 1;
			count++;
			if (pMy_string->capacity <= pMy_string->size) {
				tempArray = (char*)malloc(sizeof(char) * 2 * pMy_string->capacity);
				if (tempArray == NULL) {
					free(tempArray);
				}
				for (i = 0; i< pMy_string->capacity; i++) {
					tempArray[i] = pMy_string->data[i];
				}
				free(pMy_string->data); pMy_string->data = NULL;
				pMy_string->data = tempArray;
				tempArray = NULL;
				pMy_string->capacity *= 2;
			}
			c = fgetc(fp);
		}
		ungetc(c, fp);
		return SUCCESS;
	}
	return FAILURE;
}

Status my_string_pop_back(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string; //This function is a lie. It doesnt actually touch any memory, it just says that spot doesnt exist
	if (pMy_string->size != 0) {
		pMy_string->size--;
		return SUCCESS;
	}
	return FAILURE;
}
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
	My_string* string_structure1 = (My_string*)hResult;
	My_string* string_structure2 = (My_string*)hAppend;
	char* string1 = string_structure1->data;
	char* string2 = string_structure2->data;
	char* tempArray;
	int i, j;
	tempArray = (char*)malloc(sizeof(char) * (string_structure1->capacity - 1) + (string_structure2->capacity - 1) + 1);
	if (tempArray == NULL) {
		free(tempArray);
		return FAILURE;
	}
	for (i = 0; i < string_structure1->size; i++) {
		tempArray[i] = string1[i];
	}
	for (j = 0; i < (string_structure1->size) + (string_structure2->size); j++, i++) {
		tempArray[i] = string2[j];
	}
	free(string_structure1->data); string_structure1->data = tempArray;
	string_structure1->capacity = (string_structure1->capacity - 1) + (string_structure2->capacity - 1) + 1;
	string_structure1->size = i;
	return SUCCESS;
}
void my_string_assignment(Item_ptr* pLeft, Item_ptr Right)
{
	My_string* pMy_string_left = (My_string*)*pLeft;
	My_string* pMy_string_right = (My_string*)Right;
	int i;
	const char* temp;

	temp = my_string_c_str((MY_STRING)Right);
	if (pMy_string_left == NULL) {
		pMy_string_left = my_string_init_c_string(temp);
	}
	else {
		pMy_string_left->size = 0;
		for (i = 0; i < pMy_string_right->size + 1; i++) {
			my_string_push_back(pMy_string_left, pMy_string_right->data[i]);
		}
	}
	*pLeft = pMy_string_left;
}


Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	My_string* pNew_key = (My_string*)new_key;
	My_string* pWord = (My_string*)word;
	guess = tolower(guess);
	int i;

	my_string_assignment((Item_ptr*)&new_key, (Item_ptr)current_word_family);

	for (i = 0; i < pWord->size; i++) {
		if (tolower(pWord->data[i]) == guess) {
			pNew_key->data[i] = guess;
		}
	}

	return SUCCESS;
}
