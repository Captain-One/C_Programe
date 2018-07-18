#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void List_Init(List *list)
{
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;
}


int List_Add(List *list,Node *node,void *data)  //node == NULL, insert head 
{
	Node *newnode;
	newnode = (Node *)malloc(sizeof(Node));
	if(newnode == NULL)
	{
		printf("malloc list node error !\n");
		return -1;
	}
	newnode->data = data;
	if(list->head == NULL)
	{
		list->head = newnode;
		list->tail = newnode;
		newnode->prev = newnode;
		newnode->next = NULL;
		list->count ++;
	}else{
		if(node == NULL)
		{
			newnode->next = list->head;
			newnode->prev = newnode;
			list->head = newnode;
		}else{
			node->next = newnode;
			newnode->prev = node;	
            newnode->next = node->next;			
			if(list->tail == node)
			{				
				list->tail = newnode;
			}else{
				node->next->prev = newnode;
			}			
		}
		list->count ++;
	}
	return 0;
}

void List_Remove_Next(List *list,Node *node,void *data)
{
	
}

void List_destroy(List *list)
{
	
}

int  List_Match(List *list, void *data)
{
	return 0;
}
