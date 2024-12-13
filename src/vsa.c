
/* 
   Code by: ido jhirad	
   Project: vsa
   Date: 06/06/24
   Review by: yan
   Review Date: 08/06/24
   Approved by: yan 
   Approval Date: 17.6
*/

#include <assert.h> /*assert*/
#include <stddef.h> /* size_t */

#include "vsa.h"

#define WORD_SIZE sizeof(size_t)

#ifndef NDEBUG 
	#define MAGIC 0xABA
#endif /*NDEBUG */
#define ALOCATED (int) -1



struct vsa
{
	long block_size;
	#ifndef NDEBUG
		size_t magic;
	#endif
};
static int IsFree(long block_size);
static void DeFrag(vsa_t *runner);
static int IsSizeJustEnough(long current_size, size_t block_size);
static vsa_t* SkipBlock(vsa_t * block);
static int MoreSpace(long current_size, size_t block_size);
static long AbsolutValue(long num);
static size_t AlingSize(size_t block_size);
static char* AlingPointerForward(char* ptr , size_t *total_size);
static char* AlingPointerBack(char* ptr , size_t *total_size);

vsa_t *VSAInit(void *memory, size_t total_size)
{
	char *end_ptr = NULL;
	vsa_t *start = NULL;
	vsa_t *end =NULL;
	
	assert(memory);
	assert(total_size > sizeof(vsa_t));
	
	memory = AlingPointerForward((char*)memory, &total_size);
	
	end_ptr = (char*)memory + total_size;
	end_ptr = AlingPointerBack(end_ptr , &total_size);
	
	start = (vsa_t *)memory;
	start -> block_size = total_size - (2 * sizeof(vsa_t));
	
	end_ptr = (char*)end_ptr - sizeof(vsa_t);
	end = (vsa_t *)end_ptr;
	end -> block_size = 0;	
	#ifndef NDEBUG
		end -> magic = MAGIC;
		start -> magic = MAGIC;
	#endif
	
	return start;
}


void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	vsa_t *runner = NULL;
	vsa_t *current_free_block = NULL;
	vsa_t *new_free_block = NULL;
	size_t new_block_size = 0;
	block_size = AlingSize(block_size);
	assert(vsa);
	assert(block_size > sizeof(vsa_t));


	runner =  vsa;
	
	while(runner ->block_size != 0)
	{	
		if(!IsFree(runner -> block_size))
		{
		if (current_free_block)
			{
				current_free_block = NULL;
			}
			
			runner = SkipBlock(runner);

		}
		else
		{
			if( NULL == current_free_block )
			{
				current_free_block = runner;
			}
			else
			{
				current_free_block -> block_size += runner->block_size + sizeof(vsa_t); 
			}
			
			if(IsSizeJustEnough(current_free_block -> block_size,  block_size) )
			{
				current_free_block->block_size *= ALOCATED;
				
				++current_free_block;
				return (current_free_block);

			}
			else if(MoreSpace(current_free_block -> block_size,  block_size))
			{
				
				new_block_size = current_free_block-> block_size - block_size - sizeof(vsa_t) ;
				current_free_block -> block_size = block_size * ALOCATED;
				new_free_block = SkipBlock(current_free_block);
				new_free_block->block_size = new_block_size;
				
				#ifndef NDEBUG
					new_free_block->magic = MAGIC;
				#endif /*NDEBUG*/
				++current_free_block;
				
				return (current_free_block);
			}
			else
			{
				runner = SkipBlock(runner);
			}
		}
	}
	
	return NULL;
}

void VSAFree(void *block_ptr)
{
	vsa_t* block = NULL;
	
	assert(block_ptr);

	block = (vsa_t*)block_ptr;
	
	--block;
	
	assert( MAGIC  ==  block -> magic);
	
	block->block_size *= ALOCATED;

}

size_t LargestChunkAvailable(const vsa_t *vsa)
{
	 vsa_t *runner = NULL;

	long current_size = 0;
	long max_free_block_size = 0;
	
	assert(vsa);
	
	runner = (vsa_t*)vsa;

	while(0 != *(long*)runner )
	{
		DeFrag(runner);
		current_size = *(long*)runner;
		if(IsFree(*(long*)runner) && current_size > max_free_block_size)
		{
			max_free_block_size = current_size;

		}
		
		runner = SkipBlock(runner);
	}
	return  max_free_block_size;
}



static void DeFrag(vsa_t *runner)
{
	vsa_t * next_block = SkipBlock(runner);
	
	assert(runner);
	
	while(IsFree(runner-> block_size) && IsFree(next_block->block_size))
	{
		runner->block_size+= next_block->block_size+sizeof(vsa_t);
		next_block = SkipBlock(runner);
	} 
} 


static int IsSizeJustEnough(long current_size, size_t block_size)
{
	return ((size_t)current_size >= block_size && (size_t)current_size <= block_size + sizeof(vsa_t));
}

static int MoreSpace(long current_size, size_t block_size)
{
	return (size_t)current_size >= block_size + sizeof(vsa_t);
}

static vsa_t* SkipBlock(vsa_t * block)
{
	block = (vsa_t*)((size_t)block + sizeof(vsa_t) +AbsolutValue(block-> block_size));
	
	return block;
}

static long AbsolutValue(long num)
{
	if(num < 0)
	{
		num *=-1;
	}
	
	return num ;
}

static char* AlingPointerBack(char* ptr , size_t *total_size)
{
	while((size_t)ptr % WORD_SIZE != 0)
	{
		--ptr;
		*total_size -=1;
	}
	return ptr;
}

static char* AlingPointerForward(char* ptr , size_t *total_size)
{
	while((size_t)ptr % WORD_SIZE != 0)
	{
		++ptr;
		*total_size -=1;
	}
	
	return ptr;
}
	
static size_t AlingSize(size_t block_size)
{
	if(block_size % WORD_SIZE != 0)
	{
		return  (((block_size + WORD_SIZE ) /WORD_SIZE) *WORD_SIZE) ;
	}

	return block_size;
}

static int IsFree(long block_size)
{
    return block_size > 0;

}
