/************ 
   Code by:Ido Jhirad
   Project: Circular buffer data structure
   Date: 20/05/24
   Review by: oded
   Review Date: 21/05/24
   Approved by: Shahar Hadad
   Approval Date: 23/05/24
************/

#include <stddef.h>/*size_t offset*/
#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include <string.h>/*memcpy*/
#include <pthread.h>    /*thread*/
#include <fcntl.h> /* O_ */

#include "cbuffer.h"


struct cbuffer
{
	ssize_t write_index;
	ssize_t read_index;
	size_t capacity;
	
	pthread_mutex_t read_lock;
	pthread_mutex_t write_lock;

	char buff_data[1];
};

cbuffer_t *CBuffCreate(size_t capacity)
{
	cbuffer_t *c_buffer = (cbuffer_t *)malloc(offsetof(cbuffer_t,buff_data )+ capacity );
	
	if(NULL==c_buffer)
	{
		return NULL;
	}
	
	c_buffer -> capacity = capacity;
	c_buffer -> write_index = -1;
	c_buffer -> read_index = -1;
	
   	pthread_mutex_init(&(c_buffer->read_lock) , NULL);
	pthread_mutex_init(&(c_buffer->write_lock) , NULL);

	return c_buffer;
}

void CBuffDestroy(cbuffer_t *buffer)
{
	assert(buffer);
	
	pthread_mutex_destroy(&buffer->read_lock);
	pthread_mutex_destroy(&buffer->write_lock);
	
	free(buffer);

    
}

size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	assert(buffer);
	
	if(CBuffIsEmpty(buffer))
	{
		return buffer -> capacity;
	}
	else if(buffer -> read_index >= buffer -> write_index )
	{
		return buffer -> read_index - buffer -> write_index;
	}
	else
	{
		return buffer -> capacity -( buffer -> write_index -  buffer -> read_index);
	}
}

size_t CBuffSize(const cbuffer_t *buffer)
{
	assert(buffer);
	
	return buffer -> capacity;
}


ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{
	ssize_t read_count = -1;

	
	char *dest_ptr = NULL; 
	size_t first_read =  buffer->capacity - CBuffFreeSpace(buffer);
	
	assert(buffer);
	assert(dest);
	
	pthread_mutex_lock(&buffer->read_lock);
	dest_ptr = (char *)dest;

	
	if(CBuffIsEmpty(buffer))
	{
		return read_count;
	}
	if(count > buffer -> capacity - CBuffFreeSpace(buffer))
	{
		count = buffer -> capacity - CBuffFreeSpace(buffer);
	}
	
	if(first_read >= count)
	{
		memcpy(dest_ptr, buffer->buff_data + buffer->read_index, count);
		buffer -> read_index =(buffer -> read_index + count) % buffer->capacity;
	}
	else
    {
        memcpy(dest_ptr,  buffer->buff_data + buffer->read_index, first_read);
        memcpy(dest_ptr + first_read,  buffer->buff_data, count - first_read);
        buffer->read_index = count - first_read;
     
    }

	if(buffer -> read_index == buffer -> write_index)
	{
		buffer -> read_index = -1;
		buffer -> write_index = -1;
	}
	
	pthread_mutex_unlock(&buffer->read_lock);
	
	return count;
}



ssize_t CBuffWrite(cbuffer_t *buffer, const void *src, size_t count)
{	
	ssize_t write_count =  -1;

	char *src_ptr = NULL; 
	int over_write_flag = 0;
	size_t count_mod_capacity = 0;
	size_t right_write =0;
	size_t left_write =0;

	
	assert(buffer);
	assert(src);
	
	pthread_mutex_lock(&buffer->write_lock);
    
    src_ptr = (char *)src;

	if(0 == count)
	{
		return write_count;
	}
	
	if(count > CBuffFreeSpace(buffer))
	{
		over_write_flag = 1;
	}
	if(-1 == buffer -> write_index)
	{
		buffer -> write_index = 0;
		buffer -> read_index = 0;
	}
	if(count > buffer->capacity)
	{
		count_mod_capacity = count % buffer ->capacity;
		right_write = buffer -> capacity - buffer -> write_index;
		left_write =  buffer -> capacity -  right_write;
		memcpy(buffer->buff_data + buffer -> write_index , src_ptr + count_mod_capacity, right_write);
		memcpy(buffer->buff_data  ,src_ptr +  count_mod_capacity + right_write ,left_write );
	}

	else if(buffer->write_index + count > buffer->capacity)
	{
		right_write = buffer -> capacity - buffer -> write_index;
		left_write =  buffer-> write_index +count - buffer -> capacity;
		
		memcpy(buffer->buff_data + buffer -> write_index , src_ptr, right_write);
		memcpy(buffer->buff_data  ,src_ptr +  right_write ,left_write );
		buffer-> write_index += count;
		buffer-> write_index %= buffer->capacity;
	}
	else 
	{
		memcpy(buffer->buff_data + buffer -> write_index ,src_ptr, count);
        buffer-> write_index += count;
		buffer-> write_index %= buffer->capacity;
	}

	if(1 == over_write_flag )
	{
		buffer-> read_index =buffer -> write_index; 
	}

	pthread_mutex_unlock(&buffer->write_lock);
	
	return count;
}


int CBuffIsEmpty(const cbuffer_t *buffer)
{
	assert(buffer);
	
	return ( -1 == buffer -> write_index ) ;	
 
}











	
