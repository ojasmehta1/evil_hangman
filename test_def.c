#include "unit_test.h"
#include <string.h>

Status test_dconnoll_init_default_returns_nonNULL(char* buffer, int length) {
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString == NULL) {
		my_string_destroy((Item_ptr*)&hString);
		strncpy(buffer, "test_init_default_returns_nonNULL\nmy_string_init_default returns NULL", length);
		return FAILURE;
	}
	else {
		my_string_destroy((Item_ptr*)&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}
Status test_dconnoll_init_c_string_returns_nonNULL(char* buffer, int length) {
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("HI!");
	if (hString == NULL) {
		my_string_destroy((Item_ptr*)&hString);
		strncpy(buffer, "test_dconnoll_init_c_string_returns_nonNULL\test_dconnoll_init_c_string_returns_nonNULL returns NULL", length);
		return FAILURE;
	}
	else {
		my_string_destroy((Item_ptr*)&hString);
		strncpy(buffer, "\ntest_dconnoll_init_c_string_returns_nonNULL\n", length);
		return SUCCESS;
	}
}
Status test_dconnoll_get_size_on_init_default_returns_0(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if (my_string_get_size(hString) != 0) {
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			"Did not receive 0 from get_size after init_default\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
	}
		my_string_destroy((Item_ptr*)&hString);
	return status;
}
Status test_dconnoll_init_c_string_correctly_assigns_size(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Hello");
	if (my_string_get_size(hString) != 5) {
		status = FAILURE;
		printf("Expected a size of 5 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_init_c_string_correctly_assigns_size\n"
			"Did not get a size of 5 after the init_c_string_function\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_init_c_string_correctly_assigns_size\n", length);
	}
		my_string_destroy((Item_ptr*)&hString);
	return status;
}
Status test_dconnoll_my_string_compare(char* buffer, int length) {
	MY_STRING hLeft = NULL;
	MY_STRING hRight = NULL;

	Status status;
	hLeft = my_string_init_c_string("Hello");
	hRight = my_string_init_c_string("Hello");

	if (my_string_compare(hLeft, hRight) != 0) {
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_compare(hLeft, hRight));
		strncpy(buffer, "tests_my_string_compare\n"
			"Did not receive 0 from my_string_compare, even though the strings are lexicographically the same.\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_compare\n", length);
	}
	my_string_destroy((Item_ptr*)&hLeft);
my_string_destroy((Item_ptr*)&hRight);
	return status;
}
Status test_dconnoll_my_string_at(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Hello");
	if (*my_string_at(hString, 1) != 'e') {
		status = FAILURE;
		printf("Expected a character 'e' but got %c\n", my_string_at(hString, 2));
		strncpy(buffer, "tests_my_string_at\n"
			"Did not get a character 'e' after the my_string_at\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_at\n", length);
	}
		my_string_destroy((Item_ptr*)&hString);
	return status;
}
Status test_dconnoll_my_string_push_back(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Hello");
	if (my_string_push_back(hString, 'c') != SUCCESS) {
		status = FAILURE;
		printf("Expected to get SUCCESS (meaning that we successfully pushedback a character. Instead got: \n", my_string_push_back(hString, 'c'));
		strncpy(buffer, "my_string_push_back\nDid not get a character 'SUCCESS' after the my_string_push_back\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "my_string_push_back\n", length);
	}
		my_string_destroy((Item_ptr*)&hString);
	return status;
}
Status test_dconnoll_my_string_get_capacity_on_init_c_string(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Hello");
	if (my_string_get_capacity(hString) != 6) {
		status = FAILURE;
		printf("Expected a capacity of 6 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_init_c_string_correctly_assigns_size\n"
			"Did not get a capacity of 6 after the tests_my_string_get_capacity_on_init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_get_capacity_on_init_c_string\n", length);
	}
		my_string_destroy((Item_ptr*)&hString);
	return status;
}
Status test_dconnoll_my_string_concat(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hAppend = NULL;
	Status status;
	hRight = my_string_init_c_string("My");
	hAppend = my_string_init_c_string("Name");
	if (my_string_concat(hRight, hAppend) != SUCCESS) {
		status = FAILURE;
		printf("Expected a returned value of SUCCESS (1) but got %d\n", my_string_concat(hRight, hAppend));
		strncpy(buffer, "my_string_concat\n"
			"Did not receive 1 from my_string_concat\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_concat\n", length);
	}
		my_string_destroy((Item_ptr*)&hRight);
		my_string_destroy((Item_ptr*)&hAppend);
	return status;
}
Status test_dconnoll_my_string_empty_after_init_c_string(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	hMyString = my_string_init_c_string("My");
	if (my_string_empty(hMyString) == 1) {
		status = FAILURE;
		printf("Expected a returned value of 0 meaning not empty, but got %d\n", my_string_empty(hMyString));
		strncpy(buffer, "my_string_empty\n"
			"Did not receive 0 from my_string_empty\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_empty_after_init_c_string\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_my_string_popback_and_my_string_get_size(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	hMyString = my_string_init_c_string("Hello");
	my_string_pop_back(hMyString);
	if (my_string_get_size(hMyString) != 4) {
		status = FAILURE;
		printf("Expected a returned value of 4 meaning we popped back a character and decreased size, but got %d\n", my_string_get_size(hMyString));
		strncpy(buffer, "my_string_empty\n"
			"Did not receive 4 from my_string_get_size\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_popback_and_my_string_get_size\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_my_string_push_back_and_my_string_get_capacity(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	hMyString = my_string_init_c_string("Hello");
	my_string_push_back(hMyString, 'y');
	if (my_string_get_capacity(hMyString) != 12) {
		status = FAILURE;
		printf("Expected a returned value of 12 meaning we successfully resized our string but got %d\n", my_string_get_capacity(hMyString));
		strncpy(buffer, "my_string_empty\n"
			"Did not receive 12 from my_string_get_capacity\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_popback_and_my_string_get_capacity\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_my_string_get_capacity_on_init_default_returns_7(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if (my_string_get_capacity(hString) != 7) {
		status = FAILURE;
		printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
			"Did not receive 7 from my_string_get_capacity after init_default\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n", length);
	}
		my_string_destroy((Item_ptr*)&hString);
	return status;
}
Status test_dconnoll_my_string_empty_after_init_default(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	hMyString = my_string_init_default();
	if (my_string_empty(hMyString) == 0) {
		status = FAILURE;
		printf("Expected a returned value of 1 meaning empty, but got %d\n", my_string_empty(hMyString));
		strncpy(buffer, "tests_my_string_empty_after_init_default\n"
			"Did not receive 1 from my_string_empty\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_empty_after_init_default\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_pop_back_on_empty_my_string_object(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;

	hMyString = my_string_init_default();
	if (my_string_pop_back(hMyString) == 1) {
		status = FAILURE;
		printf("Expected a returned value of 1 meaning we couldn't popback because its empty, but we got %d\n", my_string_empty(hMyString));
		strncpy(buffer, "tests_pop_back_on_empty_my_string_object\n"
			"Did not receive 1 from my_string_pop_back\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_pop_back_on_empty_my_string_object\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_resize_feature_within_my_string_pushback(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	int i;
	hMyString = my_string_init_c_string("Hello");
	for (i = 0; i<5000; i++) {
		my_string_push_back(hMyString, 'y'); //just randomly push back
	}
	if (my_string_get_capacity(hMyString) != 6144) {
		status = FAILURE;
		printf("Expected to get a capacity of 6144 meaning we successfully resized our string but got %d\n", my_string_get_capacity(hMyString));
		strncpy(buffer, "tests_resize_feature_within_my_string_pushback\n"
			"Did not receive 12 from my_string_get_capacity\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_resize_feature_within_my_string_pushback\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_loop_of_pop_back_on_my_string_object(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	int i;
	hMyString = my_string_init_c_string("Hello");
	for (i = 0; i<5; i++) {
		my_string_pop_back(hMyString);
	}
	if (my_string_pop_back(hMyString) != 0) {
		status = FAILURE;
		printf("Expected a returned value of 0 meaning we couldn't popback because its empty, but we got %d\n", my_string_pop_back(hMyString));
		strncpy(buffer, "tests_loop_of_pop_back_on_my_string_object\n"
			"Did not receive 0 from my_string_pop_back\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_loop_of_pop_back_on_my_string_object\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_my_string_compare_with_larger_left_string(char* buffer, int length) {
	MY_STRING hLeft = NULL;
	MY_STRING hRight = NULL;

	Status status;
	hLeft = my_string_init_c_string("Helloyyyyyyyyyy");
	hRight = my_string_init_c_string("Hello");

	if (my_string_compare(hLeft, hRight) > 0) {
		status = FAILURE;
		printf("Expected a size of 1 but got %d\n", my_string_compare(hLeft, hRight));
		strncpy(buffer, "tests_my_string_compare\n"
			"Did not receive 1 from my_string_compare, even though the left string is larger.\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_compare\n", length);
	}
	my_string_destroy((Item_ptr*)&hLeft);
		my_string_destroy((Item_ptr*)&hRight);
	return status;
}
Status test_dconnoll_my_string_compare_with_larger_right_string(char* buffer, int length) {
	MY_STRING hLeft = NULL;
	MY_STRING hRight = NULL;

	Status status;
	hLeft = my_string_init_c_string("Hello");
	hRight = my_string_init_c_string("Helloyyyyyyyyyyy");

	if (my_string_compare(hLeft, hRight) < 0) {
		status = FAILURE;
		printf("Expected a size of -1 but got %d\n", my_string_compare(hLeft, hRight));
		strncpy(buffer, "tests_my_string_compare\n"
			"Did not receive -1 from my_string_compare, even though the right string is larger.\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_compare\n", length);
	}
	my_string_destroy((Item_ptr*)&hLeft);
		my_string_destroy((Item_ptr*)&hRight);
	return status;
}
Status test_dconnoll_popback_and_pushback_on_init_default(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	hMyString = my_string_init_default();
	my_string_pop_back(hMyString);
	my_string_pop_back(hMyString);
	if (my_string_empty(hMyString) == 0) {
		status = FAILURE;
		printf("Expected a returned value of 0 meaning not empty, but got %d\n", my_string_empty(hMyString));
		strncpy(buffer, "my_string_empty\n"
			"Did not receive 0 from my_string_empty\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "tests_my_string_empty_after_init_c_string\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_my_string_extraction_on_dictionary_dot_txt(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	hMyString = my_string_init_default();
	FILE* fp1 = fopen("dictionary.txt", "r");
	if (my_string_extraction(hMyString, fp1) != 1) {
		status = FAILURE;
		printf("Expected a returned value of 1 meaning it successfully extracted a string, but got %d\n", my_string_extraction(hMyString, fp1));
		strncpy(buffer, "test_dconnoll_my_string_extraction_on_dictionary_dot_txt\n"
			"Did not receive 0 from my_string_extraction\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_dconnoll_my_string_extraction_on_dictionary_dot_txt\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
fclose(fp1);
	return status;

}
Status test_dconnoll_my_string_extraction_loop_till_false(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	int i;
	hMyString = my_string_init_default();
	FILE* fp1 = fopen("dictionary.txt", "r");
	for (i = 0; my_string_extraction == SUCCESS; i++) {
		my_string_extraction(hMyString, fp1);
	}
	if (my_string_extraction(hMyString, fp1) != 1) {
		status = FAILURE;
		printf("Expected a returned value of 1 meaning it successfully extracted a string, but got %d\n", my_string_extraction(hMyString, fp1));
		strncpy(buffer, "test_dconnoll_my_string_extraction_loop_till_false\n"
			"Did not receive 0 from my_string_extraction\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_dconnoll_my_string_extraction_loop_till_false\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	fclose(fp1);
	return status;
}
Status test_dconnoll_my_string_pushback_and_my_string_at(char* buffer, int length) {
	MY_STRING hMyString = NULL;
	Status status;
	hMyString = my_string_init_c_string("Hello");
	my_string_push_back(hMyString, 'U');
	if (*my_string_at(hMyString, 5) != 'U') {
		status = FAILURE;
		printf("Expected a returned value of 'U' meaning we popped back a character and decreased size, but got %c\n", my_string_at(hMyString, 5));
		strncpy(buffer, "my_string_at\n"
			"Did not receive 4 test_dconnoll_my_string_pushback_and_my_string_at\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_dconnoll_my_string_pushback_and_my_string_at\n", length);
	}
		my_string_destroy((Item_ptr*)&hMyString);
	return status;
}
Status test_dconnoll_my_c_str(char* buffer, int length) {
	MY_STRING hString = NULL;
	char* myString;
	hString = my_string_init_c_string("hello");
	myString = my_string_c_str(hString);
	if (myString[2] != 'l') {
		my_string_destroy((Item_ptr*)&hString);
		printf("Expected a returned value of 'l' meaning we popped back a character and decreased size, but got %c\n", myString[1]);

		strncpy(buffer, "test_dconnoll_my_c_str\ntest_dconnoll_my_c_str returns a char* to the string", length);
		return FAILURE;
	}
	else {
		my_string_destroy(&hString);
		strncpy(buffer, "\ntest_dconnoll_init_c_string_returns_nonNULL\n", length);
		return SUCCESS;
	}
}
Status test_dconnoll_string_at_returns_NULL_if_index_is_greater_than_capacity(char* buffer, int length) {
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("Testers");
	if (my_string_at(hString, 15) != NULL) {
		my_string_destroy(&hString);
		printf("Expected NULL but got %c\n", my_string_at(hString, 15));
		strncpy(buffer, "test_dconnoll_my_c_str\ntest_dconnoll_my_c_str returns a char* to the string", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy(&hString);
		strncpy(buffer, "\ntest_dconnoll_init_c_string_returns_nonNULL\n", length);
		return SUCCESS;
	}
}
