#include <stdio.h>
#include <stdlib.h>

struct Lnode {
	int val;
	Lnode *next;
};

int insertLink(Lnode *head, int val)
{
	Lnode *node = (Lnode*)malloc(sizeof(Lnode));
	node->val = val;
	node->next = head->next;
	head->next = node;
	return 0;
}

void printLink(Lnode *head)
{
	Lnode *p = head->next;
	while(p) {
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}

int reserveLink(Lnode *head)
{
	Lnode *curr, *pnext, *pafter;
	curr = head->next;
	pnext = curr->next;
	curr->next = NULL;
	while(pnext) {
		pafter = pnext->next;
		pnext->next = curr;
		curr = pnext;
		pnext = pafter;
	}
	head->next = curr;
}
int main()
{
	int a[] = {1,4,7,9,8};
	Lnode *head = (Lnode*)malloc(sizeof(Lnode));
	head->next = NULL;

	for(int i=0; i<5; i++) {
		insertLink(head, a[i]);
	}

	printLink(head);
	reserveLink(head);
	printLink(head);
}
