#include <stdio.h>
#include <stdint.h>
#include "list.h"

typedef struct grade_{
	int math;
	int phy;
	int Eng;
}Grade_t;

typedef struct Student_{
	char name[20];
	int  ID;
	Grade_t grade;
}Student_t;

int main(void)
{
	int rv;
	List_t list;
	Student_t student[3]={"li lei",1,{90,88,75},"han meimei",2,{80,68,77},"zhang san",3,{70,58,54}};
	printf("List Test !\n");
	List_Init(&list);
	rv = List_Insert_Next(&list,NULL,&student[1]);
	printf("insert: name: %s, ID: %d, Grade: math: %d, phy: %d, eng: %d\n",((Student_t *)(list.head->data))->name,\
	((Student_t *)(list.head->data))->ID,((Student_t *)(list.head->data))->grade.math,((Student_t *)(list.head->data))->grade.phy,\
	((Student_t *)(list.head->data))->grade.Eng);
}
