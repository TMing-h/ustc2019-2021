#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#define N 3
#define M 4
#define P 2
using namespace std;
typedef struct{//���ṹ�嶨��
	char no[20];//����
	int ntime;//����ʱ��
}car;
typedef struct LNode{//�����нڵ㶨��
	car c;
	int num;
	LNode *next;
}LNode;
typedef struct{//�����ж���
	LNode *front;
	LNode *rear;
	int length;
}LinkQueue;
typedef struct{//ջ����
	car *c;//car���͵�����N���ռ�N����
	int top;
}SqStack;
void InitStack(SqStack &S){
	S.c = new car[N];
	S.top=-1;
}
void DestroyStack(SqStack &S){
	delete[] S.c;
	S.top = -1;
}
bool StackFull(SqStack S){
	return (S.top==N-1);
}
bool StackEmpty(SqStack S){
	return (S.top==-1);
}
void Push(SqStack &S,char no[],int ntime){//��ͣ����
	if(S.top==N-1){
		printf("ͣ����������\n");
		return;
	}
	S.top++;
	strcpy(S.c[S.top].no,no);
	S.c[S.top].ntime = ntime;
}
void Pop(SqStack &S,char no[],int &ntime){//��ͣ����
	if(S.top==-1){
		printf("ͣ�����ѿգ�\n");
		return;
	}
	strcpy(no,S.c[S.top].no);
	ntime = S.c[S.top].ntime;
	S.top--;
}
void GetTop(SqStack &S,char no[],int &ntime){
	if(S.top==-1){
		printf("ͣ����Ϊ�գ�\n");
		return;
	}
	strcpy(no,S.c[S.top].no);
	ntime = S.c[S.top].ntime;
}
void InitQueue(LinkQueue &Q){
	Q.front=Q.rear=new LNode;
	Q.front->next=NULL;
	Q.length=0;
}
void DestroyQueue(LinkQueue &Q){
	while(Q.front){
		Q.rear = Q.front->next;
		delete Q.front;
		Q.front = Q.rear;
	}
}
void GetHead(LinkQueue Q,char no[],int &ntime){
	if(Q.front==Q.rear){
		printf("����޳���\n");
		return;
	}
	strcpy(no,Q.front->next->c.no);
	ntime = Q.front->next->c.ntime;
}
void EnQueue(LinkQueue &Q,char no[],int ntime){
	LNode *p = new LNode;
	strcpy(p->c.no,no);
	p->c.ntime = ntime;
	p->next = Q.rear->next;
	Q.rear->next = p;
	Q.rear = p;
	Q.rear->next = Q.front->next;
	Q.length++;
	Q.rear->num = Q.length;
}
void DeQueue(LinkQueue &Q,char no[]){
	if(Q.front==Q.rear){
		printf("���Ϊ�գ�\n");
		return;
	}
	LNode *p = Q.front->next;
	Q.front->next = p->next;
	strcpy(no,p->c.no);
	if(Q.rear==p)
		Q.rear==Q.front;
	delete p;
	Q.length--;
}
bool QueueFull(LinkQueue Q){
	if(Q.length<=M)
		return 1;
	return 0;
}
bool QueueEmpty(LinkQueue Q){
	return (Q.front==Q.rear);
}
void StackTravels(SqStack S){
	if(!StackEmpty(S)){
			while(S.top!=-1){
			cout<<"���ƣ�"<<S.c[S.top].no<<" ͣ������λ�ã�"<<S.top+1<<endl;
			S.top--;
		}
	}
	else
		cout<<"ͣ����Ϊ�գ�"<<endl;
}
void QueueTravels(LinkQueue Q){
	if(!QueueEmpty(Q)){
		LNode *p;
		p = Q.front->next;
		while(p!=Q.rear){
			cout<<"���ƣ�"<<p->c.no<<" �����λ�ã�"<<p->num<<endl;
			p = p->next;
		}
		cout<<"���ƣ�"<<p->c.no<<" �����λ�ã�"<<p->num<<endl;
	}
	else
		cout<<"���Ϊ�գ�"<<endl;
}
void QueueNum(LinkQueue Q){
	if(!QueueEmpty(Q)){
		LNode *p;
		p = Q.front->next;
		while(p!=Q.rear){
			p->num--;
			p = p->next;
		}
		p->num--;
	}
}
bool StackLocate(SqStack S,char no[],char status){
	if(!StackEmpty(S)){
		while(S.top!=-1){
			if(strcmp(S.c[S.top].no,no)==0)
				return 1;
			S.top--;
		}
	}
	return 0;
}
