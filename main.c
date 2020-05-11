#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "my_string.h"
#include "generic.h"
#include "evil_tree.h"

Status get_int_from_user(int* number, FILE* fp1, FILE* fp2);
Status get_guessesLeft_from_user(int* number, FILE* fp1, FILE* fp2);
void clear_keyboard_buffer(FILE* fp2);
int getWordLength(int* a, FILE* fp1, FILE* fp2);
int getGuessNumber(FILE* fp1, FILE* fp2);
Boolean printWordTotal(FILE* fp1, FILE* fp2 );
char getCharacter(FILE* fp1, FILE* fp2);
Boolean notReused(char current_guess, MY_STRING guesses, FILE* fp1);
void playtheGame(FILE* fp1, FILE* fp2);
int userwishestoContinue(FILE* fp1, FILE* fp2);


int main(int argc, char** argv) {
  FILE* fp1 = stdout; // fopen("outfile.txt", "w");
  FILE* fp2 = stdin;
  do {
    playtheGame(fp1, fp2);
  } while(userwishestoContinue(fp1, fp2));
  return 0;
}



Status get_int_from_user(int* number, FILE* fp1, FILE* fp2) {
	int number_of_conversions;

	number_of_conversions = fscanf(fp2,"%d", number);
	while (number_of_conversions <= 0 || *number < 2 || *number > 29) {
		fprintf(fp1,"The game must be played with word lengths from 2 to 29: ");
		clear_keyboard_buffer(fp2);
		number_of_conversions = fscanf(fp2,"%d", number);
	}

	return SUCCESS;
}

Status get_guessesLeft_from_user(int* number, FILE* fp1, FILE* fp2) {
	int number_of_conversions;

	number_of_conversions = fscanf(fp2,"%d", number);
	while (number_of_conversions <= 0 || *number < 1) {
		fprintf(fp1,"You have to have at least one guess: ");
		clear_keyboard_buffer(fp2);
		number_of_conversions = fscanf(fp2,"%d", number);
	}

	return SUCCESS;
}

void clear_keyboard_buffer(FILE* fp2) {
	char c;
	do {
		fscanf(fp2,"%c", &c);
	} while (c != '\n');
	return;
}

int getWordLength(int* a, FILE* fp1, FILE* fp2) {
		int number_of_conversions;
		int length_of_word;
		fprintf(fp1, "How long would you like the word you are playing with to be: ");
		number_of_conversions = fscanf(fp2, "%d", &length_of_word);
		//fprintf(fp1,"  number_of_conversions == %d\n", number_of_conversions);
		//fprintf(fp1,"  length_of_word == %d\n", length_of_word);
		clear_keyboard_buffer(fp2);
		if (number_of_conversions == 1) {
			if (!(length_of_word > 0 && length_of_word < 30)) {
				fprintf(fp1,"I'm sorry, but you need to choose a number between [2-29].\n");
				length_of_word = getWordLength(a, fp1, fp2);
			}
			if (a[length_of_word - 1] == 0) {
				//fprintf(fp1,"a[i] = %d\n",a[length_of_word]);
				fprintf(fp1,"I'm sorry, but there are no words in the English language that are that long.\n");
				length_of_word = getWordLength(a, fp1, fp2);
			}
		} else {
			fprintf(fp1,"I'm sorry, but you need to choose a number between [2-29].\n");
			length_of_word = getWordLength(a, fp1, fp2);
		}
		return length_of_word;
	}

	int getGuessNumber(FILE* fp1, FILE* fp2) {
		int guessesLeft;
		int number_of_conversions;
		fprintf(fp1,"How many guesses would you like to have: ");
		number_of_conversions = fscanf(fp2, "%d", &guessesLeft);
		clear_keyboard_buffer(fp2);;
		if (number_of_conversions == 1) {
			if (!(guessesLeft > 0)) {
				fprintf(fp1,"I'm sorry, but you need to choose a positive integer!\n");
				guessesLeft = getGuessNumber(fp1, fp2);
			}
		} else {
			fprintf(fp1,"I'm sorry, but you need to choose a positive integer!\n");
			guessesLeft = getGuessNumber(fp1, fp2);
		}
		return guessesLeft;
	}


	Boolean printWordTotal(FILE* fp1, FILE* fp2) {
		char c;
		fprintf(fp1,"Would you like the program to display the remaining words? (y/n): ");
		fscanf(fp2,"%c", &c);
		clear_keyboard_buffer(fp2);;
		if (isalpha(c)) {
			if (isupper(c)) {
				c = tolower(c);
			}
			switch (c) {
			case 'y':
				return TRUE;
				break;
			case 'n':
				return FALSE;
				break;
			default:
				return FALSE;
			}
		}
		return FALSE;
	}

	char getCharacter(FILE* fp1, FILE* fp2) {
		char c;
		fprintf(fp1,"Please enter a character: ");
		fscanf(fp2,"%c", &c);
		clear_keyboard_buffer(fp2);;
		if (isalpha(c)) {
			if (isupper(c)) {
				c = tolower(c);
			}
		} else {
			c = getCharacter(fp1, fp2);
		}

		return c;
	}

Boolean notReused(char current_guess, MY_STRING guesses, FILE* fp1) {
	My_string* temp = (My_string*)guesses;
	int i;
	Boolean is_reused_letter = FALSE;
	for (i = 0; i < temp->size; i++) {
		if (temp->data[i] == current_guess) {
			fprintf(fp1,"You already guessed that letter, try again!\n");
			is_reused_letter = TRUE;
		}
	}
		return is_reused_letter;
}


void playtheGame(FILE* fp1, FILE* fp2){
  int i, wordLength = 0, guessesLeft;
	Boolean printTotal;
	char current_guess;
	FILE* fp = fopen("dictionary.txt", "r");
	MY_STRING hMy_string = my_string_init_default();
	EVIL_TREE treeBins = my_tree_init_default();
	MY_STRING wordKey = my_string_init_default();
	MY_STRING wordFamily = my_string_init_default();
	MY_STRING guesses = NULL;
	GENERIC_VECTOR array1[30];
	int a[30] = { 0 };
	GENERIC_VECTOR temp = NULL;
	for (i = 0; i < 30; i++) {
		array1[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
	}
	while (my_string_extraction(hMy_string, fp)) {
		generic_vector_push_back(array1[my_string_get_size(hMy_string) - 1], hMy_string);
		a[my_string_get_size(hMy_string) - 1]++;
	}
	fclose(fp);
	guesses = my_string_init_c_string(" ");
	wordLength = getWordLength(a, fp1, fp2);
	guessesLeft =  getGuessNumber(fp1, fp2);
	printTotal =  printWordTotal(fp1, fp2);
	for (i = 0; i < wordLength; i++) {
		my_string_push_back(wordKey, '-');
	}
	fprintf(fp1,"\n");
	do {
		fprintf(fp1,"There are %d guesses remaining\n", guessesLeft);
		fprintf(fp1,"Used Letters: ");
		my_string_insertion(guesses, fp1);
		fprintf(fp1,"\nWord: ");
		my_string_insertion(wordKey, fp1);
		fprintf(fp1,"\n");
		do {
			current_guess = getCharacter(fp1, fp2);
		} while (notReused(current_guess, guesses, fp1));
		fprintf(fp1,"\n");
		my_string_push_back(guesses, current_guess);
		my_string_push_back(guesses, ', ');

		for (i = 0; i < generic_vector_size(array1[wordLength - 1]); i++) {
			get_word_key_value(wordKey, wordFamily, generic_vector_at(array1[wordLength - 1], i), current_guess);
			my_tree_add_item(treeBins, wordFamily, generic_vector_at(array1[wordLength - 1], i));
		}

		temp = my_tree_get_largest_bin(treeBins, fp1, printTotal);

		generic_vector_destroy(&(array1[wordLength - 1]));
		array1[wordLength - 1] = generic_vector_init_default(my_string_assignment, my_string_destroy);
		for (i = 0; i < generic_vector_size(temp); i++) {
			generic_vector_push_back(array1[wordLength - 1], generic_vector_at(temp, i));
			//my_string_insertion(generic_vector_at(array1[wordLength -1], i), fp1);
			//fprintf(fp1,"\n");
		}
    //printf("--------------\n");
    //fprintf(fp1,"Word Family: ");
    //my_string_insertion(wordFamily, fp1);
    //fprintf(fp1,"\ngeneric_vector_at(array1[wordLength - 1], 0) : ");
    //my_string_insertion(generic_vector_at(array1[wordLength - 1], 0), fp1);
    //fprintf(fp1,"\n");
		get_word_key_value(wordKey, wordFamily, generic_vector_at(array1[wordLength - 1], 0), current_guess);
		//fprintf(fp1,"Word Family: ");
		//my_string_insertion(wordFamily, fp1);
		//fprintf(fp1,"\ngeneric_vector_at(array1[wordLength - 1], 0) : ");
		//my_string_insertion(generic_vector_at(array1[wordLength - 1], 0), fp1);
		fprintf(fp1,"\n");
		if (my_string_compare(wordKey, wordFamily) == 0) {
    	fprintf(fp1,"I'm sorry, but the word does not contain any %c's.\n\n", current_guess);
      guessesLeft--;
  	}
		/*	fprintf(fp1,"-----------------------PRE-------------------");
			fprintf(fp1,"\nwordKey = ");
			my_string_insertion(wordKey, fp1);
			fprintf(fp1,"\nwordFamily = ");
			my_string_insertion(wordFamily, fp1);*/
		my_string_assignment(&wordKey, wordFamily);
		/*	fprintf(fp1,"\n-----------------------POST-------------------");
			fprintf(fp1,"\nwordKey = ");
			my_string_insertion(wordKey, fp1);
			fprintf(fp1,"\nwordFamily = ");
			my_string_insertion(wordFamily, fp1);
			fprintf(fp1,"\n"); */
		generic_vector_destroy(&temp);
		my_tree_destroy(&treeBins);
		my_string_destroy(&wordFamily);
		wordFamily = my_string_init_default();
		treeBins = my_tree_init_default(my_string_assignment, my_string_destroy);

		if (guessesLeft == 0) {
			fprintf(fp1,"\nYou Lost!\nThe word was: ");
			my_string_insertion(generic_vector_at(array1[wordLength - 1], 0), fp1);
			fprintf(fp1,"\n\n");
			break;
		}
		if (my_string_compare(generic_vector_at(array1[wordLength - 1], 0), wordKey) == 0) {
			if (generic_vector_size(array1[wordLength - 1]) == 1) {
				fprintf(fp1,"CONGRATULATIONS!\nThe word was: ");
				my_string_insertion(generic_vector_at(array1[wordLength - 1], 0), fp1);
				fprintf(fp1,"\n\n");
				break;
			}
		}
	} while (guessesLeft > 0);

	for (i = 0; i < 30; i++) {
		generic_vector_destroy(&array1[i]);
	}
	my_tree_destroy(&treeBins);
	my_string_destroy(&hMy_string);
	my_string_destroy(&wordFamily);
	my_string_destroy(&wordKey);
	my_string_destroy(&guesses);
  //fclose(fp1);
  //fclose(fp2);
	return;
}


int userwishestoContinue(FILE* fp1, FILE* fp2){
  char c;
//  fprintf(stdout, "Would you like to play again? (y/n): ");
  fprintf(fp1, "Would you like to play again? (y/n): ");
  fscanf(fp2,"%c", &c);
  clear_keyboard_buffer(fp2);;
  if (isalpha(c)) {
    if (isupper(c)) {
      c = tolower(c);
    }
    switch (c) {
    case 'y':
      return TRUE;
      break;
    case 'n':
      return FALSE;
      break;
    default:
      return FALSE;
    }
  }
  return FALSE;
}
