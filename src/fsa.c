
/* 
   Code by: ido jhirad	
   Project: fsa
   Date: 05/06/24
   Review by: oria
   Review Date: 06/05/24
   Approved by: oria
   Approval Date: 09/06/2024
*/
#include <assert.h> /*assert*/

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)
#define INVALID (size_t) -1


static size_t AlingSize(size_t block_size);
static void* AlingPointerForward(void* memory);

struct fsa 
{
	size_t block_size;
	size_t free_next;
	void *base;
};

/*nums block */
size_t FSASuggestSize(size_t block_size, size_t block_num)
{
	assert(0 < block_num);
	assert(0 < block_size);
	

	return (sizeof(struct fsa ) + ((AlingSize(block_size) * block_num) + WORD_SIZE)) ;
}



fsa_t *FSAInit(void *memory, size_t total_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	char * init_ptr = NULL;
	char * end_ptr = NULL;
	char * memory_runner = memory;
	
	assert(memory);
	assert(0 < total_size);
	assert(0 < block_size);
	
	while((size_t)memory % WORD_SIZE != 0 )
	{
		++memory_runner;
		--total_size;
		memory = memory_runner;
	}
	fsa = (fsa_t *)memory;
	fsa -> block_size = AlingSize(block_size);
	fsa -> base = (char*)memory + sizeof(fsa_t);
	
	init_ptr = fsa -> base;
	end_ptr = (char*)memory + total_size;
	while((size_t)end_ptr % WORD_SIZE != 0 )
	{
		--end_ptr;
		--total_size;
	}
	while((size_t)(end_ptr -init_ptr) >= block_size+WORD_SIZE )
	{
		*(size_t*) init_ptr = (size_t)init_ptr + fsa -> block_size;
		 init_ptr += fsa -> block_size;
	}
	
	*(size_t*)init_ptr = INVALID;
	
	fsa -> free_next = 0;
	
	return fsa;
	
}


void *FSAAlloc(fsa_t *fsa)
{
	size_t *ptr = NULL;	
	
	assert(fsa);
	
	ptr = (size_t*)fsa->base + (fsa -> free_next / WORD_SIZE);

	if((*ptr) == INVALID )
	{	
		return NULL;
		
	}
	fsa -> free_next = fsa -> block_size + (size_t)ptr - (size_t)fsa->base;
	
	return (void *)ptr;
}


void FSAFree(fsa_t *memory_pool, void *block_ptr)
{
	assert(memory_pool)	;
	assert(block_ptr);
	
	*(size_t*)block_ptr = memory_pool -> free_next +(size_t) memory_pool->base ;
	
	memory_pool -> free_next =  (size_t)block_ptr - (size_t)memory_pool -> base;
}


size_t FSACountFree(const fsa_t *fsa)
{
	size_t *ptr = NULL;  
	size_t counter = 0;
	
	assert(fsa);
	
	ptr = (size_t*)fsa->base + (fsa -> free_next / WORD_SIZE);
	
	while(INVALID != *(size_t*)ptr)
	{	
		++counter;
		ptr = (size_t *)*ptr; 
 	}
 	
 	return counter;
}
	
static size_t AlingSize(size_t block_size)
{
	if(block_size % WORD_SIZE != 0)
	{
		return  (((block_size + 8 ) /8) *8) ;
	}

	return block_size;
}

static void* AlingPointerForward(void* memory)
{
	
	char *runner = NULL;
	
	assert(memory);
	
	runner = (char *)memory;
	while ((size_t)runner & (WORD_SIZE-1))
	{
		++runner;
	}
	
	return (void *)runner;

}
