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

void mergeLink(Lnode *heada, Lnode *headb)
{
	Lnode *pa, *pb, *panext, *pbnext;
	pa = heada->next;
	pb = headb->next;

	while(pb) {
		panext = pa->next;
		pbnext = pb->next;
		pa->next = pb;
		pb->next = panext;

		pb = pbnext;
		pa = panext;
	}
}

int main()
{
	int a[] = {1,4,7,9,8};
	int b[] = {3,5,7,9,10};
	Lnode *heada = (Lnode*)malloc(sizeof(Lnode));
	heada->next = NULL;

	Lnode *headb = (Lnode*)malloc(sizeof(Lnode));
	headb->next = NULL;

	for(int i=0; i<sizeof(a)/sizeof(int); i++) {
		insertLink(heada, a[i]);
	}

	for(int i=0; i<sizeof(b)/sizeof(int); i++) {
		insertLink(headb, b[i]);
	}

	printLink(heada);
	printLink(headb);
	mergeLink(heada, headb);
	printLink(heada);
}
