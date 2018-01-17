#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
	void *data;
	ListNode *next;
};

struct sList
{
	ListNode *head;
	int len;
};

void printList(sList *list)
{
	ListNode *p = list->head->next;
	int *data = NULL;
	while(p != NULL){
		data = (int*)(p->data);
		printf("%d ", *data);
		p = p->next;
	}
	printf("\n");
}


sList *createList()
{
	sList *list = (sList*)malloc(sizeof(sList));
	list->head = (ListNode*)malloc(sizeof(ListNode));
	list->head->data = NULL;
	list->len = 0;

	return list;
}

int listInsert(sList *list, void *data)
{
	ListNode *item = (ListNode*)malloc(sizeof(ListNode));
	item->data = data;

	item->next = list->head->next;
	list->head->next = item;

	return 0;
}

int ListReverse(sList* L)
{
    ListNode *current, *pnext, *prev;

    current = L->head->next;
    pnext = current->next;
    current->next = NULL;
    while(pnext)
    {
    	prev = pnext->next;
    	pnext->next = current;
    	current = pnext;
    	pnext = prev;
        printf("after change：current = %d,next = %d \n",*(int *)(current->data),*(int*)(current->next->data) );
    }
    L->head->next = current;
    return 0;
}

sList *ListReverse1(sList *L)
{
	sList *list = (sList*)malloc(sizeof(sList));
	list->head = (ListNode*)malloc(sizeof(ListNode));
	list->head->data = NULL;
	list->len = 0;

	ListNode *p = L->head->next;
	ListNode *next;
	while(p)
	{
		next = p->next;
		p->next = list->head->next ;
		list->head->next = p;
		p = next;
	}
	free(L);
	return list;

}


int main()
{
	int a[]={1,2,3,8,7,6,5,6,7,8,5};

	sList *list = createList();
	for(int i=0; i<11; i++) {
		int *data = (int*)malloc(sizeof(int));
		*data = a[i];
		listInsert(list, (void*)(data));
	}
	printList(list);

	sList *newList = ListReverse1(list);
	printList(newList);
}
