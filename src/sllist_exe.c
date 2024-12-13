#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/


typedef struct node
{
	void *data;
	struct node *next;
}node_t;

static size_t Count(node_t *head);
static void PrintLlist(node_t *head);

node_t *flip(node_t *head)
{	
	node_t *curr = head;
	node_t *prev = NULL;
	node_t *next = head -> next;
	for(;NULL != next;)
	{
		next = curr ->next;
		curr -> next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
} 

int HasLoop( node_t *head)
{
	node_t *slow_p = head;
	node_t *fast_p = head;
	while(slow_p != NULL && fast_p != NULL&& fast_p -> next !=NULL )
	{
		slow_p = slow_p-> next;
		fast_p = fast_p -> next-> next;
		if(slow_p == fast_p)
		{
			return 1;
		}
	}
	return 0;
}

node_t *FindIntersection(node_t *head1, node_t *head2)
{
	size_t size1 = Count(head1);
	size_t size2 = Count(head2);
	int diff = 0;
	if(size1 > size2)
	{
		diff= size1 -size2;
		while(diff>0)
		{
			--diff;
			head1 = head1 -> next;	
		}
	}
	else if(size1 < size2)
	{
		diff= size2 -size1;
		while(diff>0)
		{
			--diff;
			head2 = head2 -> next;	
		}
	}
	while(NULL !=head1&& NULL != head2)
	{
		if(head1==head2)
		{
			return head1;
		}
	
		else
		{
			head1 = head1 -> next;
			head2 = head2 -> next;
		}
	}
	return NULL;
}

int main()
{
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;
	
	int data15 = 25;
	int data16 = 30;

	int loop_i = 0;	

	node_t *node1=(node_t *) malloc(sizeof(node_t)); 
	node_t *node2=(node_t *) malloc(sizeof(node_t)); 
	node_t *node3=(node_t *) malloc(sizeof(node_t)); 
	node_t *node4=(node_t *) malloc(sizeof(node_t)); 
	
	
	node_t *node15=(node_t *) malloc(sizeof(node_t)); 
	node_t *node16=(node_t *) malloc(sizeof(node_t)); 
	
	node_t *head1 = node1;
	node_t *head2 = NULL;
	node_t *head3 = NULL;
	
	node1 -> data = &data1;
	node2 -> data = &data2;
	node3 -> data = &data3;
	node4 -> data = &data4;
	
	node15-> data = &data15;
	node16-> data = &data16;
	
	node1 -> next = node2;
	node2 -> next = node3;
	node3 -> next = node4;
	node4 -> next = /*node1 for hasloop */ NULL;
	
	node15-> next = node16;
	node16-> next = NULL;		
	
	PrintLlist(head1);
	head1 = flip(head1);
	PrintLlist(head1);
	
	loop_i = HasLoop(head1);
	if(loop_i)
	{
		printf("has loop\n");
	}
	else
	{
		printf("has no loop\n");
	}
	
	head1 = node1;
	head2 = node15;
	head3 = FindIntersection(head1,head2);
	if(head3)
	{
		printf("has Intersection\n");
	}
	else
	{
		printf("has no Intersection\n");
	}
	return 0;	
}

static  void PrintLlist(node_t *head)
{
	while(NULL != head)
	{
		printf("%d", *(int *) (head-> data));
		head = head-> next;	
	}
	printf("\n");
}

static size_t Count(node_t *head)
{
	size_t count = 0;
	while(NULL != head)
	{
		head = head-> next;	
		++count;
	}
	printf("\n");
	return count;
}




