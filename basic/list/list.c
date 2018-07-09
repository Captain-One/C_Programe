#include "list.h"
#include <stdlib.h>

void List_Init(List_t *list)
{
	list->node_num = 0;
	list->head = NULL;
	list->tail = NULL;
	list->match = NULL;
	list->destroy = NULL;
}

int List_Insert_Next(List_t *list, List_Node_t *list_node,void *data)
{
	List_Node_t *new_node;
	new_node = (List_Node_t *)malloc(sizeof(List_Node_t));
	if(new_node == NULL)
	{
		return -1;
	}
	new_node->data = data;
	if(list_node == NULL)
	{
		new_node->next = list->head;
		list->head = new_node;	
		new_node->prev = NULL;
        if(list->tail == NULL)
		{
			list->tail = list->head;
		}			
	}else{
		new_node->next = list_node->next;
		new_node->prev = list_node;
		list_node->next->prev = new_node;
		list_node->next = new_node;
        if(list_node == list->tail)		
		{
			list->tail = new_node;
		}
	}
	list->node_num ++;
	return 0;
}

int List_Remove_Next(List_t *list, List_Node_t *list_node,void *data)
{
	List_Node_t *old_node;
	if(list->node_num)
	{
		if(list_node == NULL)
		{
			old_node = list->head;			
			if(list->head->next == NULL)
			{
				list->tail = NULL;
			}else{				
				list->head->next->prev = NULL;
			}
			list->head = list->head->next;
		}else{
			old_node = list_node->next;
			if(list_node->next == NULL)
			{
				return -1;
			}else{
				if(list_node->next == list->tail)
				{
					list->tail = list_node;
					list_node->next = NULL;
				}
			}
			list_node->next = list_node->next->next;
		}
		data = old_node->data;
		free(old_node);
	}else{
		return -1;
	}
	list->node_num --;
    return 0;
}

void List_Destroy(List_t *list)
{
	char *data;
	if(list == NULL)
	{
		return -2;
	}
	while(list->node_num)
	{
		if(List_Remove_Next(list,NULL,data) && (list->destroy != NULL))
		{
			list->destroy(data);
		}
	}
}































