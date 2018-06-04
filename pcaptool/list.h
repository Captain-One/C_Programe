#ifndef  _LIST_H
#define  _LIST_H

typedef struct node_t{
	void *data;
	struct node_t *next;
}Node, *pNode;

typedef struct List_t{
	int count;
	struct List_t *head;
	struct List_t *tail;
}List, *pList;

#define List_Elemnts_Number(list)   list->count
#define List_Head(list)   		    list->head;
#define List_Tail(list)   		    list->head;

void List_Insert_Node()
void List_Remove_Node()
void List_

#endif
