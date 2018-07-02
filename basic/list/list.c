#include "list.h"

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
		
	}
}