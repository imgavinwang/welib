#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

struct Lnode {
	int data;
	Lnode *next;
};

struct Link {
	Lnode *head;
};

Link *createLink()
{
	Link *link = (Link*)malloc(sizeof(Link));
	link->head = (Lnode*)malloc(sizeof(Lnode));
	return link;
}

int insertNode(Link *l, int data)
{
	Lnode *node = (Lnode *)malloc(sizeof(Lnode));
	node->data = data;
	node->next = l->head->next;
	l->head->next = node;
	return 0;
}

void printLink(Link *l) {
	Lnode *p = l->head->next;
	while(p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

int reserveLink(Link *l)
{
	Lnode *curr, *pnext, *prv;
	curr = l->head->next;
	pnext = curr->next;
	curr->next = NULL;
	while(pnext) {
		prv = pnext->next;
		pnext->next = curr;
		curr = pnext;
		pnext = prv;
	}
	l->head->next = curr;
	return 0;
}

int main()
{
	int a[] = {1,2,3,4,6,7,9,8,5};
	vector<int> v(a, a+9);
	Link *link = createLink();
	vector<int>::iterator it;
	for(it = v.begin(); it != v.end(); it++) {
		insertNode(link, *it);
	}

	printLink(link);
	reserveLink(link);
	printLink(link);
}
