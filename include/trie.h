#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /* size_t */


typedef struct node node_trie_t; 
typedef struct trie trie_t;

typedef enum trie_status
{
  TRIE_SUCCESS,	
  TRIE_MEMORY_FALIURE,
  TRIE_IS_FULL,
  NOT_FOUND
} trie_status_e;


/*
TrieCreate
description: create the trie
input: void
return: pointer to the trie
time complexity: o(1)
space complexity: o(1)
*/

trie_t *TrieCreate(size_t depth);


/*
TrieDestroy
description:Destroy the trie
input: pointer to the Trie
return: void
time complexity: o(n)
space complexity: o(1)
*/
void TrieDestroy(trie_t *trie);


/*
TrieDestroy
description:insert a host 
input: pointer to the Trie, host id and its lenght 
return: pointerto the node that inserted if faild NULL
time complexity: o(log n)
space complexity: o(1)
*/
trie_status_e TrieInsert(trie_t *trie, unsigned int host_id, unsigned int *output_param);


/*
TrieDestroy
description:remove the host id from the trie
input: pointer to the Trie , host lenght and host id
return: void??
time complexity: o(log n)
space complexity: o(1)
*/
trie_status_e TrieRemove(trie_t *trie , unsigned int host_id);

size_t TrieCount(trie_t *trie);


#endif /*__TRIE_H__*/
