#ifndef __LIST_H
#define __LIST_H

#include <stdint.h>

typedef struct list_Node_{
	struct node_t_tag *next;
	struct node_t_tag *prev;
	void *data;
}List_Node_t, pList_Node_t *;


typedef struct list_{
	int node_num;
	List_Node_t *head;
	List_Node_t *tail;
}List_t, pList_t *;

#define List_Head(list)					((list)->head)
#define List_Tail(list)					((list)->tail)
#define List_Node_Num(list)				({list}->node_num)
#define Is_List_Tail(list_node)  		((list_node)->next==NULL?1:0)
#define IS_List_Head(list_node,list)	((list_node)==(list)->head?1:0)
#define Get_List_Node_Data(lsit_node)	((list_node)->data)
#define Get_List_Node_Next(lsit_node)	((lsit_node)->next)

void List_Init(List_t *list);
void List_Destroy(List_t *list);
int List_Insert_Next(List_t *list, List_Node_t *list_node,void *data);


#endif