/* 
   Code by: ido jhirad	
   Project: avl
   Date: 20/06/224
   Review by: yarden
   Review Date: 22/06/2024
   Approved by: yarden
   Approval Date: 27/06/2024
*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stddef.h>	/* typedef */

#include "avl.h"
 
 #define LEFT_CHILD 0
 #define RIGHT_CHILD 1
 #define NUMS_OF_CHILDREN 2

typedef struct node
{
	size_t height;
	void * data;
	struct node *child[NUMS_OF_CHILDREN];
	
}node_t;

struct avl
{
	node_t *root;
	avl_cmp_func_t compare;
};

/*******************************************/
static size_t CountHelper(node_t * node);
static void DestroyHelper(node_t *node);
static node_t *MoveLeft(node_t *node);
static node_t *MoveRight(node_t *node);
static node_t * HelperInsert(node_t *node_for_iter ,
						       	  void *data, avl_cmp_func_t compare
						       	  , int *status);
static node_t * CreateNode( void * data);
static void *GetData(node_t * node);
static void Updetheight(node_t *node);
static size_t Checkheight(node_t *node);
static void *FindIter(node_t *node 
					  ,avl_cmp_func_t compare 
					  ,const void * data);
static void *HelperAVLFind(node_t *node 
						   ,avl_cmp_func_t compare 
						   ,const void * data);

static node_t *DiveRight(node_t * node);
static void SetData(node_t *node , void *data);
static node_t *RemoveHelper(node_t * node_to_remove
						  , avl_cmp_func_t compare
						  , void *data);
static int ForEachHelper(node_t *node 
						 , avl_action_func_t action 
						 , void *params);
static void SetHeight(node_t *node, size_t new_height);


static node_t *BalanceNode(node_t * node);
static node_t *GetChild(node_t * node, int side);
static int GetBalanceFactor(node_t *node);
static node_t *DetermineRotationType(node_t * node);
static node_t *Rotate(node_t * node, int side);
static int IsBalance(node_t * node);

/****************api function**************************/

avl_t *AVLCreate(avl_cmp_func_t compare)
{
	avl_t *avl =NULL;
	
	assert(compare);
	
	avl = (avl_t *)malloc(sizeof(struct avl));
	if(!avl)
	{
		return NULL;
	}
	
	avl->compare = compare;
	avl->root = NULL;
	
	return avl;	
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(tree);
	
	return tree->root == NULL;
}

void AVLDestroy(avl_t *tree)
{
	assert(tree);
	
	DestroyHelper(tree->root);
	free(tree);
}

size_t AVLCount(const avl_t *tree)
{
	assert(tree);
	
	return CountHelper(tree->root);
}

size_t AVLHeight(const avl_t *tree)
{
	assert(tree);
	
	if(!tree->root)
	{
		return 0;
	}
	
	return tree->root->height;
}

int AVLInsert(avl_t *tree, void *data)
{
	int status = 0;

	assert(tree);
	
	tree->root = HelperInsert(tree->root, data , tree->compare, &status);
	Updetheight(tree->root);
	
	return status;	
}

void *AVLFind(const avl_t *tree, const void *data)
{
	assert(tree);
	
	return HelperAVLFind(tree -> root, tree -> compare , data);
}

void AVLRemove(avl_t *tree, void *data)
{
	assert(tree);
	
	tree->root = RemoveHelper(tree->root, tree->compare, data);
}	

int AVLForEach(avl_t *tree,
				 avl_action_func_t action,
				  void* params)
{
	int status = 0;
	
	assert(tree);
	/*assert(tree->root);*/
	assert(action);
	
	status = ForEachHelper(tree->root ,action , params);
	
	return status;
}

/*****************************helper function**********************************/
/******************************************************************************/

static node_t *MoveLeft(node_t *node)
{
	if(!node)
	{
		return NULL;
	}
	return node->child[LEFT_CHILD];
}

static node_t *MoveRight(node_t *node)
{
	if(!node)
	{
		return NULL;
	}
	return node->child[RIGHT_CHILD];
}

static void DestroyHelper(node_t *node)
{
	if(node)
	{
		DestroyHelper(MoveLeft(node));
		DestroyHelper(MoveRight(node));
		free(node);
	}
}

static size_t CountHelper(node_t * node)
{

	if(!node)
	{
		return 0;
	}	
	
	return 1 + 	CountHelper(MoveLeft(node)) + CountHelper(MoveRight(node));
}

static node_t *HelperInsert(node_t *node_for_iter ,
						          void *data, avl_cmp_func_t compare
						          , int *status)
{
	struct node  *new = NULL;
	int compare_res = 0;
	int side = 0;
	
	if(!node_for_iter)
	{
		 new = CreateNode(data);
		 if(!new)
		 {
		 	*status = -1;
		 	return NULL;
		 }
		 return new;
	}
	compare_res = compare(GetData(node_for_iter), data); 
	side = ((compare_res > 0) ? LEFT_CHILD : RIGHT_CHILD );
	
	/*find the right place to insert*/
	node_for_iter->child[side] = 
			   HelperInsert(GetChild(node_for_iter,side),data,compare, status);				
			   
	 Updetheight(node_for_iter); 
	
	return BalanceNode(node_for_iter);
}

static node_t *BalanceNode(node_t * node)
{
	if(IsBalance(node))
	{
		return node;
	}
	
	return DetermineRotationType(node);
}

static int IsBalance(node_t * node)
{
	int balance_factor  = GetBalanceFactor(node);
	
	return ((balance_factor >= -1 && balance_factor <= 1) ? 1 : 0);
}

static int GetBalanceFactor(node_t *node)
{
	return  (Checkheight(MoveLeft(node)) - Checkheight(MoveRight(node)));
}

static node_t *DetermineRotationType(node_t * node)
{
	node_t *child = NULL;
	int node_balace = 0;
	int child_balace = 0;
	int side = GetBalanceFactor(node); 
	
	node_balace	= side;
	
	side = ((side > 0) ? LEFT_CHILD : RIGHT_CHILD );
	child = GetChild(node , side);
	
	child_balace = GetBalanceFactor(child);
	
	if(child_balace * (-2) == node_balace)
	{
		child = Rotate( child, !side);
		node->child[side] = child;
	}
	
	
	return Rotate(node, side);
	
}

node_t *Rotate(node_t * node, int side)
{
	node_t * child = GetChild(node , side);
	
	/*the node get the chile i swap with*/	
	node->child[side]= child->child[!side];
	child->child[!side] = node;
	
	Updetheight(node);
	Updetheight(child);
	
	return child;
}
node_t *GetChild(node_t * node, int side)
{
	return node->child[side];
}

static void Updetheight(node_t *node)
{
	size_t height_left = Checkheight(MoveLeft(node));
 	size_t height_right = Checkheight(MoveRight(node));
 	
 	if(height_right > height_left)
 	{
 		SetHeight(node, (height_right + 1));
 	}
 	else
 	{
 		SetHeight(node, (height_left + 1));
	}
}	

static void SetHeight(node_t *node, size_t new_height)
{
	node->height = new_height;
}

static size_t Checkheight(node_t *node)
{
	if (!node)
	{
		return 0;
	}
	
	return node->height;
}

static void *HelperAVLFind(node_t *node ,avl_cmp_func_t compare ,
															const void * data)
{	if(!FindIter(node, compare , data))
	{
		return NULL;
	}
	return (void*)data;
}
static void *FindIter(node_t *node ,avl_cmp_func_t compare ,const void * data)
{
	int status = 0;
	
	if(!node)
	{
		return NULL;
	}
	
	status = compare(GetData(node), data);
	
	if(0 == status)
	{
		return node;
	}
	if(status < 0 )
	{
		node = MoveRight(node);
	}
	else	
	{
		node = MoveLeft(node);
	}
	
	return 	FindIter(node, compare , data);
	
}
static void *GetData(node_t * node)
{
	assert(node);
	
	return node -> data;
}

static node_t * CreateNode( void * data)
{
	node_t * iter = (node_t *)malloc(sizeof( struct node));
	if(!iter)
	{

		return NULL;
	}
	
	iter->data = data;
	iter->child[RIGHT_CHILD] = NULL;
	iter->child[LEFT_CHILD] =NULL;
	iter->height = 1;
	return iter;
}

static node_t *RemoveHelper(node_t * node_to_remove,
								 avl_cmp_func_t compare
								 , void *data)	
{
	node_t *child = NULL;
	int compare_res = 0;
	size_t side = 0;
	
	if(!node_to_remove)
	{
		return NULL;
	}

	compare_res = compare(GetData(node_to_remove), data);
	
	if(0 == compare_res)
	{
		/*case it a leaf or right child only */
		if(NULL == MoveLeft(node_to_remove))
		{
			child = node_to_remove->child[RIGHT_CHILD];
			
			free(node_to_remove);

			return child;
		}
		
		/*has left child only*/	
		if(NULL == MoveRight(node_to_remove))
		{
			child = node_to_remove->child[LEFT_CHILD];  
			
			free(node_to_remove);
			
			return child;
		}
		/*has two child*/
		else
		{	
			/* move to the left and then dive right to search node to copy
			then remove the found iter and connect the nodes*/
			
			child = DiveRight(MoveLeft(node_to_remove));
			SetData(node_to_remove, GetData(child));
			child = RemoveHelper(MoveLeft(node_to_remove), compare 
										  , GetData(node_to_remove));
			node_to_remove->child[LEFT_CHILD]= child;
			Updetheight(node_to_remove);	
		}
	}	
	/*in case it not the node for traversal*/
	else
	{
		side = ((compare_res < 0) ? RIGHT_CHILD : LEFT_CHILD);
		
		child = RemoveHelper(node_to_remove->child[side], compare , data);
		
		node_to_remove->child[side]= child;
		Updetheight(node_to_remove);	
			
	}
	return  BalanceNode(node_to_remove); ;
}

static node_t *DiveRight(node_t * node)
{
	if(node->child[RIGHT_CHILD])
	{
		node = DiveRight(MoveRight(node));
	}
	
	return node;
}

static void SetData(node_t *node , void *data)
{
	node->data = data;
}

static int ForEachHelper(node_t *node ,
									 avl_action_func_t action , 
									 void *params)
{
	int status = 0;
	if(!node)
	{
		return status;
	}
	ForEachHelper(MoveLeft(node), action, params);
	status = action(node->data , params);
	ForEachHelper(MoveRight(node), action, params);
	
	return status;
}

