#ifndef  _LIST_H
#define  _LIST_H

typedef struct node_t{
	void *data;
	struct node_t *next;
	struct node_t *prev;
}Node, *pNode;

typedef struct List_t{
	int count;
	struct node_t *head;
	struct node_t *tail;
	
	//void (* free) (void *ptr);
	//void (* match) (void *ptr,void *key);
	
}List, *pList;

#define List_Elemnts_Number(list)   list->count;
#define List_Head(list)   		    list->head;
#define List_Tail(list)   		    list->head;

void List_Init(List *list);
int List_Add(List *list,Node *node,void *data);

void List_Remove_Next(List *list,Node *node,void *data);
void List_destroy(List *list);
int  List_Match(List *list, void *data);



#endif
