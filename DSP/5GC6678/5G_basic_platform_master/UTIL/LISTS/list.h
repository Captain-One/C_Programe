#ifndef __LIST_H__
#    define __LIST_H__

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//#include<linux/types.h>
#include<stdlib.h>
//#include<sys/queue.h>
#include <string.h>


#include "../MEM/mem_block.h"

//-----------------------------------------------------------------------------
void         list_init (list_t* , char *);
void         list_free (list_t* listP);
mem_block_t* list_get_head (list_t*);
mem_block_t* list_remove_head (list_t* );
mem_block_t* list_remove_element (mem_block_t*, list_t*);
void         list_add_head (mem_block_t* , list_t* );
void         list_add_tail_eurecom (mem_block_t* , list_t* );
void         list_add_list (list_t* , list_t* );
void         list_display (list_t* );
//-----------------------------------------------------------------------------
void         list2_init           (list2_t*, char*);
void         list2_free           (list2_t* );
mem_block_t* list2_get_head       (list2_t*);
mem_block_t* list2_get_tail       (list2_t*);
mem_block_t* list2_remove_element (mem_block_t* , list2_t* );
mem_block_t* list2_remove_head    (list2_t* );
mem_block_t* list2_remove_tail    (list2_t* );
void         list2_add_head       (mem_block_t* , list2_t* );
void         list2_add_tail       (mem_block_t* , list2_t* );
void         list2_add_list       (list2_t* , list2_t* );
void         list2_display        (list2_t* );
//-----------------------------------------------------------------------------
/* The following lists are used for sorting numbers */
#ifndef LINUX_LIST
/*! \brief the node structure */
struct node {
  struct node* next; /*!< \brief is a node pointer */
  double val; /*!< \brief is a the value of a node pointer*/
};
//-----------------------------------------------------------------------------
/*! \brief the list structure */
struct list {
  struct node* head; /*!< \brief is a node pointer */
  ssize_t size; /*!< \brief is the list size*/
};
#else
//-----------------------------------------------------------------------------
struct entry {
  double val;
  LIST_ENTRY(entry) entries;
};
//-----------------------------------------------------------------------------
struct list {
  LIST_HEAD(listhead, entry) head;
  ssize_t size;
};
#endif
//-----------------------------------------------------------------------------
void   push_front  (struct list*, double); 
void   initialize  (struct list*);         
void   del         (struct list*);         
void   totable     (double*, struct list*);
int compare (const void * a, const void * b);
int32_t calculate_median(struct list *loc_list);


typedef struct {
  size_t size;
  size_t mallocedSize;
  size_t atomSize;
  size_t increment;
} varArray_t;
 
static inline varArray_t * initVarArray(size_t increment, size_t atomSize) {
    varArray_t * tmp=malloc(sizeof(varArray_t)+increment*atomSize);
    tmp->size=0;
    tmp->atomSize=atomSize;
    tmp->mallocedSize=increment;
    tmp->increment=increment;
    return(tmp);
}

static inline void * dataArray(varArray_t * input) {
  return input+1;
}

static inline void appendVarArray(varArray_t * input, void* data) {
  if (input->size>=input->mallocedSize) {
     input->mallocedSize+=input->increment;
     input=realloc(input,sizeof(varArray_t)+input->mallocedSize*input->atomSize);
  }
  memcpy((uint8_t*)(input+1)+input->atomSize*input->size++, data, input->atomSize);
}

static inline void freeVarArray(varArray_t * input) {
   free(input);
}

#endif
