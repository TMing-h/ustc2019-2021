#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#define N 3
#define M 4
#define P 2
using namespace std;
typedef struct{//车结构体定义
	char no[20];//车牌
	int ntime;//到达时间
}car;
typedef struct LNode{//链队列节点定义
	car c;
	int num;
	LNode *next;
}LNode;
typedef struct{//链队列定义
	LNode *front;
	LNode *rear;
	int length;
}LinkQueue;
typedef struct{//栈定义
	car *c;//car类型的数组N个空间N辆车
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
void Push(SqStack &S,char no[],int ntime){//进停车场
	if(S.top==N-1){
		printf("停车场已满！\n");
		return;
	}
	S.top++;
	strcpy(S.c[S.top].no,no);
	S.c[S.top].ntime = ntime;
}
void Pop(SqStack &S,char no[],int &ntime){//出停车场
	if(S.top==-1){
		printf("停车场已空！\n");
		return;
	}
	strcpy(no,S.c[S.top].no);
	ntime = S.c[S.top].ntime;
	S.top--;
}
void GetTop(SqStack &S,char no[],int &ntime){
	if(S.top==-1){
		printf("停车场为空！\n");
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
		printf("便道无车！\n");
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
		printf("便道为空！\n");
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
			cout<<"车牌："<<S.c[S.top].no<<" 停车场中位置："<<S.top+1<<endl;
			S.top--;
		}
	}
	else
		cout<<"停车场为空！"<<endl;
}
void QueueTravels(LinkQueue Q){
	if(!QueueEmpty(Q)){
		LNode *p;
		p = Q.front->next;
		while(p!=Q.rear){
			cout<<"车牌："<<p->c.no<<" 便道上位置："<<p->num<<endl;
			p = p->next;
		}
		cout<<"车牌："<<p->c.no<<" 便道上位置："<<p->num<<endl;
	}
	else
		cout<<"便道为空！"<<endl;
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
