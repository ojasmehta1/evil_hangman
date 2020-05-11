#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"



GENERIC_VECTOR generic_vector_init_default(void(*assignment)(Item_ptr* pLeft, Item_ptr Right), void(*destroy)(Item_ptr* ppItem)) {
	Generic_vector* pVector;
	int i;
	//printf("HERRLOOOO\n");
	pVector = (Generic_vector*)malloc(sizeof(Generic_vector)); //footprint
	if (pVector != NULL)
	{
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (Item_ptr*)malloc(sizeof(Item_ptr)*pVector->capacity);
		if (pVector->data == NULL)
		{
			free(pVector);
			pVector = NULL;
		}
		else
		{
			for (i = 0; i < pVector->capacity; i++)
			{
				pVector->data[i] = NULL;
			}
			pVector->assignment = assignment;
			pVector->destroy = destroy;
		}
	}
	return pVector;
}

int generic_vector_size(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->size;
}
int generic_vector_capacity(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->capacity;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, Item_ptr item)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	Item_ptr* pTemp;
	int i;
	//if there is not enough room, fix it.
	if (pVector->size >= pVector->capacity)
	{
		pTemp = (Item_ptr*)malloc(sizeof(Item_ptr) * pVector->capacity * 2);
		if (pTemp == NULL)
		{
			return FAILURE;
		}
		else
		{
			for (i = 0; i < pVector->size; i++)
			{
				pTemp[i] = pVector->data[i];
			}
			pVector->capacity *= 2;
			//fill the rest with NULL
			for (; i < pVector->capacity; i++)
			{
				pTemp[i] = NULL;
			}
			free(pVector->data);
			pVector->data = pTemp;
		}
	}
	//printf("\nSTRING INSTERTION FROM WITHIN GENERIC_VECTOR_PUSH_BACK:");
	//my_string_insertion(item, stdout); //PUSHBACK TEST
	//printf("\n");
	pVector->assignment(&(pVector->data[pVector->size]), item);
	if (pVector->data[pVector->size] == NULL)
	{
		return FAILURE;
	}
	pVector->size++;
	return SUCCESS;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;

	if (pVector->size <= 0)
	{
		return FAILURE;
	}
	pVector->size--;
	if (pVector->data[pVector->size] != NULL)
	{
		pVector->destroy(&(pVector->data[pVector->size]));
	}

	return SUCCESS;
}

Item_ptr generic_vector_at(GENERIC_VECTOR hVector, int index)
{
	Generic_vector* pVector = (Generic_vector*)hVector;

	if (index < 0 || index >= pVector->size)
	{
		return NULL;
	}

	return (pVector->data[index]);
}

Boolean generic_vector_is_empty(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;
	return pVector->size == 0;
}

void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
	Generic_vector* pVector = (Generic_vector*)*phVector;
	int i;

	for (i = 0; i < pVector->size; i++)
	{
		if (pVector->data[i] != NULL)
		{
			pVector->destroy(&(pVector->data[i]));
		}
	}
	free(pVector->data);
	free(pVector);

	*phVector = NULL;

	return;
}