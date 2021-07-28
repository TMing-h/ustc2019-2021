#include<stdio.h>
int length=0;
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	int no;
	struct LNode *next;
}LinkList;
LinkList* CreateList(LinkList *&L,int a[],int n){
	LinkList *s,*r;
	L = new LinkList;
	L->next = NULL;
	r = L;
	int i=0;
	while(i<n){
		s = new LinkList;
		s->data = a[i];
		s->no = i+1;
		s->next = r->next;
		r->next = s;
		r = s;
		i++;
	}
	r->next = L->next;
	return r;
}
void ListLength(LinkList *L){
	LinkList *p=L->next;
	while(p->next!=L->next){
		p = p->next;
		length++;
	}
	length++;
}
void Joseph(LinkList *&L,LinkList *r,int m){
	LinkList *p=L->next,*q=L;
	int num=1;
	if(length==1){
		printf("%d",p->no);
		delete p;
		delete q;
		return;
	}
	while(length!=1){
		while(num<m){
			q = p;
			p = p->next;
			num++;
		}
		if(p->no==1)
			r->next = q;
		m = p->data;
		q->next = p->next;
		printf("%d ",p->no);
		delete p;
		length--;
		p = q->next;
		num=1;
	}
	printf("%d\n",q->no);
	delete q;
	delete L;
}
