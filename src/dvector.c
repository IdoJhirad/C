/***********************************************
Name: Ido
Reviewer: first cr yan , secound cr amit
Exercise: dynamic vector 
Status: approved
***********************************************/ 

#include <stdlib.h> /* malloc, realloc, free */
#include <assert.h> /* assert*/
#include <string.h> /*memcpy*/ 

#include "dvector.h" 

#define GROWTH_FACTOR 2

struct dvector
{
    size_t capacity;
    size_t current_size;
    size_t element_size;
   	char *buffer;
};

static int IsDvectorFull(dvector_t *vector);

dvector_t *DvectorCreate(size_t capacity, size_t element_size)
{
	dvector_t *dvector = NULL;
	
	assert(capacity > 0);
	assert(element_size > 0);
	
	dvector = (dvector_t *) malloc (sizeof(dvector_t));
	if( NULL == dvector)
	{
		return NULL;
	}
	dvector -> element_size = element_size;
	dvector -> current_size = 0;
	dvector -> capacity = capacity;
	
	dvector -> buffer = malloc( capacity * element_size );
	if( NULL == dvector -> buffer)
	{
		free(dvector);
		
		return NULL;
	}
	return dvector;
}


void DvectorDestroy(dvector_t *vector)
{
	assert(NULL != vector);
	
	free(vector -> buffer);
	free(vector);
}


int DvectorPushBack(dvector_t *vector, const void *new_element)
{	
    size_t new_capacity = 0;


	assert(NULL != vector);
		
	if(IsDvectorFull(vector))
	{
		new_capacity = GROWTH_FACTOR * vector -> capacity;

		if( 0 != DvectorReserve(vector, new_capacity))
		{
			return -1;
		}
	}
	
	memcpy(vector -> buffer + (vector -> current_size * vector ->
	                       element_size ), new_element, vector -> element_size);
	++(vector -> current_size);	
		
	return 0;
	
}

void DvectorPopBack(dvector_t *vector)
{
	assert(NULL != vector);
	assert(0 < vector-> current_size);
	
	--(vector -> current_size);	
}
     
int DvectorShrink(dvector_t *vector)
{
	assert(NULL != vector);
	
	return DvectorReserve(vector , vector -> current_size);
}

int DvectorReserve(dvector_t *vector, size_t new_size)
{
	char *new_buffer = NULL;
	size_t size = 0; 

	assert(0 < new_size);
	assert(NULL != vector);
	
	size = new_size * vector -> element_size;
	new_buffer = (char*)realloc(vector -> buffer,size);
	if( NULL ==  new_buffer) 
	{
		return -1;
	}
	if(new_size < vector->current_size)
	{
		vector->current_size = new_size;
	}

	vector -> buffer = new_buffer;
	vector -> capacity =  new_size;
	
	
	return 0;
}

size_t DvectorSize(const dvector_t *vector)
{
	assert(NULL != vector);
	return vector -> current_size;
}

size_t DvectorCapacity(const dvector_t *vector)
{
	assert(NULL != vector);
	
	return vector -> capacity;
}


void *DvectorGetElement(const dvector_t *vector, size_t index)
{	void *data = NULL;

	assert(NULL != vector);
	assert(index < vector->current_size);
	
	assert(vector ->current_size  > index);
	data = ((vector->buffer) + (index * vector->element_size));

	return data;
}


static int IsDvectorFull(dvector_t *vector)
{
	return(( vector -> current_size )==(vector -> capacity));
}
