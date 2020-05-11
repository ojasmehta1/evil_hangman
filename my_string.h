#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include "generic.h"
#define MY_STRING void*

struct my_string {
  int capacity;
  int size;
  char* data;
};
typedef struct my_string My_string;
struct nextpass {
  My_string* key;
  int size;
};
typedef struct nextpass NextPass;

enum status { FAILURE, SUCCESS };
enum boolean { FALSE, TRUE };
typedef enum status Status;
typedef enum boolean Boolean;

typedef void* GENERIC_VECTOR;


// init
GENERIC_VECTOR generic_vector_init_default(
  void(*assignment)(Item_ptr* pLeft, Item_ptr Right),
  void(*destroy)(Item_ptr* ppItem));



// size
// capacity

int generic_vector_size(GENERIC_VECTOR hVector);
int generic_vector_capacity(GENERIC_VECTOR hVector);

// push_back
Status generic_vector_push_back(GENERIC_VECTOR hVector, Item_ptr item);

// pop_back
Status generic_vector_pop_back(GENERIC_VECTOR hVector);

// empty
Boolean generic_vector_is_empty(GENERIC_VECTOR);

// at
Item_ptr generic_vector_at(GENERIC_VECTOR hVector, int index);


// destroy
void generic_vector_destroy(GENERIC_VECTOR* phVector);

// Precondition: None
// Postcondition: Allocate space for a string object that represents the empty
// string. The string will have capacity 7 and size 0 by default. A copy of
// the address of the opaque object will be returned on success and NULL on failure
MY_STRING my_string_init_default(void);

// Precondition: phMy_string holds the address of a valid handle to a MY_STRING object
// Postcondition: The memory used for the MY_STRING object has been reclamined by//the system and the handle referred to by the pointer phMy_string has been set to NULL
void my_string_destroy(Item_ptr* pItem_ptr);

// Precondition: c_string is a valid null termianted c-string
// Postconiditon: Allocate space for a string object will be set to be one greater than is required to hold the string. As an example, the string"the" would set capacity at 4 instead of 3. A copy of the address of thje opaque object will be returned on success and NULL on failure.
MY_STRING my_string_init_c_string(const char* c_string);

// Precondition: hMy_string is the handle of a valid My_string object.
// Postcondition: Returns a copy of the integer value of the object's capacity
int my_string_get_capacity(MY_STRING hMy_string);

// Precondition: hMy_string is the handle of a valid My_String object.
// Postcondition: Returns a copy of the integer value of an object's size
int my_string_get_size(MY_STRING hMy_string);

// Precondition:// hLeft_string and hRight_string are valid My_string objects
// Postcondiiton: returns an integer less than zero if the string respresented by hLeft_string is lexicographically smaller than rRight_string. If
// one strign is a prefix of the other string then the shorter string is considered to by the smaller one. (app is less than apple).
// Returns 0 if the strings are the same and returns a number greater than zero if the string represented by hLeft_string is bigger than hRight_string
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: hMy_string will be the handle of a string object that contains
// the next string from the file stream fp according to the following rules.
// 1) Leading whitespace will be ignored.
// 2) All characters (after the first non-whitespace character is obtained
// and included) will be added to the string until a stopping condition
// is met. The capacity of the string will continue to grow as needed
// until all characters are stored.
// 3) A stopping condition is met if we read a whitespace character after
// we have read at least one non-whitespace character or if we reach
// the end of the file.
// Function will return SUCCESS if a non-empty string is read successfully.
// and failure otherwise. Remember that the incoming string may aleady
// contain some data and this function should replace the data but not
// necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp);

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Writes the characters contained in the string object indicated
// by the handle hMy_string to the file stream fp.
// Function will return SUCCESS if it successfully writes the string and
// FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);


// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: If successful, places the character item at the end of the
// string and returns SUCCESS. If the string does not have enough room and
// cannot resize to accomodate the new character then the operation fails
// and FAILURE is returned. The resize operation will attempt to amortize
// the cost of a resize
// by making the string capacity somewhat larger than
// it was before (up to 2 times bigger).
Status my_string_push_back(MY_STRING hMy_string, char item);

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Removes the
// last character of a string in constant time.
// Guaranteed to not cause a resize operation of the internal data. Returns
// SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string);

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Returns the address of the character located at the given
// index if the index is in bounds but otherwise returns NULL. This address
// is not usable as a c-string since the data is not NULL terminated and is
// intended to just provide access to the element at that index.
char* my_string_at(MY_STRING hMy_string, int index);

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Returns the address of the first element of the string object
// for use as a c-string. The resulting c-string is guaranteed to be NULL
// terminated and the memory is still maintained by the string object though
// the NULL is not actually counted as part of the string (insize).
char* my_string_c_str(MY_STRING hMy_string);

// Precondition: hResult and hAppend are handles to valid My_string objects.
// Postcondition: hResult is the handle of a string that contains the original
// hResult object followed by the hAppend object concatenated together. This
// function should guarantee no change to the hAppend object and return
// SUCCESS if they operation is successful and FAILURE if the hResult object
// is unable to accomodate the characters in the hAppend string perhaps
// because of a failed resize operation. On FAILURE, no change to either
// string should be made.
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend);

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Returns an enumerated type with value TRUE if the string
// is empty and FALSE otherwise.
Boolean my_string_empty(MY_STRING hMy_string);

// Precondition: pLeft is the address of a MY_STRING handle
// containing a valid MY_STRING object address OR NULL.
// The value of Right must be the handle of a valid MY_STRING object
// Postcondition: On Success pLeft will contain the address of a handle
// to a valid MY_STRING object that is a deep copy of the object indicated
// by Right. If the value of the handle at the address indicated by
// pLeft is originally NULL then the function will attempt to initialize
// a new object that is a deep copy of the object indicated by Right,
// otherwise the object indicated by the handle at the address pLeft will
// attempt to resize to hold the data in Right. On failure pLeft will be
// left as NULL and any memory that may have been used by a potential
// object indicated by pLeft will be returned to the freestore.
void my_string_assignment(Item_ptr* pLeft, Item_ptr Right);

// Precondition:current_word_family, new_key and word are all handles to valid
// MY_STRING opaque objects. guess is an alphabetical character that can be either
// upper or lower case.
// Postcondition: Returns SUCCESS after replacing the string in new_key with the key
// value formed by considering the current word family, the word and the guess.
// Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);

#endif  // MY_STRING_H_
