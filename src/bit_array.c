
/***********************************************
Name: Ido
Reviewer: sahar
Exercise: bit_array
Status: done
***********************************************/ 
#include "bit_array.h"
#include <assert.h> /* assert() */
#include <limits.h> /* CHAR_BIT */

#define NUMBER_OF_BITS_IN_SIZE_T (sizeof(size_t) * CHAR_BIT)
#define EIGHT_BITS_ON 0xff

static int lut[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 
    2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 
    2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 
    3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 
    2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 
    3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 
    3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 
    4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 
    2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 
    3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 
    3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 
    4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 
    3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 
    4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 
    4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 
    5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};
static char mirror_look_up[16] = {0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 
								 0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF};
				  

bit_array_t SetAll(bit_array_t bit_arr)
{
	/*bit_arr |= 0xFFFFFFFFFFFFFFFF; */
	(void)bit_arr;
	return -(1);
}

bit_array_t ResetAll(bit_array_t bit_arr)
{
  /*  bit_arr &= 0;*/ /*all 0*/
	(void)bit_arr;
	return 0;
}

bit_array_t SetOn(bit_array_t bit_arr, size_t index)
{
	assert(index< NUMBER_OF_BITS_IN_SIZE_T);
	   bit_arr |= 1 << index; 
	   return bit_arr;
}

bit_array_t SetOff(bit_array_t bit_arr, size_t index)
{
	assert(index< NUMBER_OF_BITS_IN_SIZE_T);
		bit_arr &= ~(1 << index);
		
		return bit_arr; 
}


bit_array_t SetBit(bit_array_t bit_arr, size_t index, int bool_value)
{
	assert(index < NUMBER_OF_BITS_IN_SIZE_T);
	assert(bool_value >= 0);
	assert(bool_value <= 1);

	if (bool_value) 
	{
        return bit_arr | ((size_t)1 << index); 
    } 
    else 
    {
        return bit_arr & ~((size_t)1 << index);
    }
	/*if(bool_value)
	{
		return SetOn(bit_arr, index);
	}
	return SetOff(bit_arr, index);
*/
}

int GetVal(bit_array_t bit_arr, size_t index)
{
	assert(index < NUMBER_OF_BITS_IN_SIZE_T);
	return (bit_arr >> index) & (size_t)1;
}

bit_array_t FlipBit(bit_array_t bit_arr, size_t index)
{
	assert(index < NUMBER_OF_BITS_IN_SIZE_T);
	return bit_arr ^ (1 << index);
}



bit_array_t FlipAll(bit_array_t bit_arr)
{
	return ~bit_arr;
}

	
bit_array_t Mirror(bit_array_t bit_arr)
{
	
	bit_arr = ((bit_arr & 0xFFFFFFFF00000000) >> 32) | ((bit_arr & 0x00000000FFFFFFFF) << 32);
	
    bit_arr = ((bit_arr & 0xFFFF0000FFFF0000) >> 16) | ((bit_arr & 0x0000FFFF0000FFFF) << 16);

    bit_arr = ((bit_arr & 0xFF00FF00FF00FF00) >> 8) | ((bit_arr & 0x00FF00FF00FF00FF) << 8);

    bit_arr = ((bit_arr & 0xF0F0F0F0F0F0F0F0) >> 4) | ((bit_arr & 0x0F0F0F0F0F0F0F0F) << 4);

    bit_arr = ((bit_arr & 0xCCCCCCCCCCCCCCCC) >> 2) | ((bit_arr & 0x3333333333333333) << 2);

    bit_arr = ((bit_arr & 0xAAAAAAAAAAAAAAAA) >> 1) | ((bit_arr & 0x5555555555555555) << 1);
	
	return bit_arr;
}

bit_array_t RotateRight(bit_array_t bit_arr, size_t n)
{
	size_t temp = bit_arr << (NUMBER_OF_BITS_IN_SIZE_T - (n % NUMBER_OF_BITS_IN_SIZE_T));
	bit_arr >>= (n % NUMBER_OF_BITS_IN_SIZE_T);
	
	return (bit_arr | temp);

    
}

bit_array_t RotateLeft(bit_array_t bit_arr,size_t n)
{
    size_t temp = bit_arr >> (NUMBER_OF_BITS_IN_SIZE_T - (n % NUMBER_OF_BITS_IN_SIZE_T));
	bit_arr <<= (n % NUMBER_OF_BITS_IN_SIZE_T);
	return (bit_arr | temp);

}

size_t CountOn(bit_array_t bit_arr)
{
	bit_arr =bit_arr - ((bit_arr>> 1) & 0x5555555555555555);
    bit_arr = (bit_arr & 0x3333333333333333) + ((bit_arr >> 2) & 0x3333333333333333);
    return (((bit_arr + (bit_arr >> 4)) & 0xF0F0F0F0F0F0F0F) * 0x101010101010101) >> 56;
}


size_t CountOff(bit_array_t bit_arr)
{
	size_t count =NUMBER_OF_BITS_IN_SIZE_T - CountOn( bit_arr);
	
	
	return count;
}


char *ToString(bit_array_t bit_arr, char *dest)
{
    int i = NUMBER_OF_BITS_IN_SIZE_T - 1;
    int j = 0;
    
    while (0 <= i) 
    {
        dest[j] = ((bit_arr >> i) & 1) + '0';
        --i;
        ++j;
    }
    dest[j] = '\0';
    return dest;
}


bit_array_t MirrorLut(bit_array_t data)
{
	bit_array_t result = 0;
	size_t i = 0;
	
	for(; i < 16; ++i)
	{
		result <<= 4;
		result |= mirror_look_up[data & 0xF];
		data >>= 4;
	}
	
	return result;
}

size_t CountBitsOnLut(bit_array_t bit_arr)
{
	size_t count = 0;
	
	count += lut[(bit_arr & EIGHT_BITS_ON)];
	count += lut[((bit_arr >> 8) & EIGHT_BITS_ON)];
	count += lut[((bit_arr >> 16) & EIGHT_BITS_ON)];
	count += lut[((bit_arr >> 24) & EIGHT_BITS_ON)];
	count += lut[((bit_arr >> 32) & EIGHT_BITS_ON)];
	count += lut[((bit_arr >> 40) & EIGHT_BITS_ON)];
	count += lut[((bit_arr >> 48) & EIGHT_BITS_ON)];
	count += lut[((bit_arr >> 56) & EIGHT_BITS_ON)];

	return count;
}

