
#include <iostream>
using namespace std;

//定义结点类型
struct Node 
{
	int m_value;//结点值
	Node* m_next;//指向下一个结点的指针
};

//创建一个长度为n的链表，返回头结点的指针
Node* creat(int n)
{
	Node* head;
	Node* p1;
	Node* p2;
	for (int i=0; i<n; i++)
	{
		if (i == 0)
		{
			head = new Node();//创建头结点
			cout << "请输入第1个元素：";
			cin >> head->m_value;
			head->m_next = NULL;
			p1 = head;
		}
		else
		{
			p2 = new Node();
			cout << "请输入第" <<i+1 << "个元素：";
			cin >> p2->m_value;
			p2->m_next = NULL;
			p1->m_next = p2;
			p1 = p2;
		}
	}
	return head;
}

//递归的实现A、B两个链表的交叉归并
void mergeRecursively(Node* headA, Node* headB) //注意：链表A的长度要大于等于链表B
{
	if (headA == NULL || headB == NULL)
	{
		return;
	} 
	
	mergeRecursively(headA->m_next, headB->m_next);
	headB->m_next = headA->m_next;
	headA->m_next = headB;
}

//非递归的实现A、B两个链表的交叉归并
void mergeNoRecursively(Node* headA, Node* headB)
{
	Node *pBCurrent = headB;
	Node *pBm_next = NULL;
	Node *pACurrent = headA;
    Node *pAm_next = NULL;

    while (pBCurrent != NULL)
    {
	   pBm_next = pBCurrent->m_next;//记录下一个待插元素
	   pAm_next = pACurrent->m_next;//记录插入位置

	   //插入元素
       pBCurrent->m_next = pACurrent->m_next;
	   pACurrent->m_next = pBCurrent;

	   pBCurrent = pBm_next; 
	   pACurrent = pAm_next;
    }
}

int main()
{
	Node* headA;
	Node* headB;
	Node* p;

	cout << "链表A: \n";
	headA = creat(4);
	cout << "链表B: \n";
	headB = creat(3);

	p = headA;
	//mergeRecursively(headA, headB);
	mergeNoRecursively(headA, headB);

	cout << "递归合并后的链表为：\n";	
	while (p != NULL)
	{
		cout << p->m_value << " ";
		p = p->m_next;
	} 
    cout << endl;
	return 0;
}
