#include <iostream>
#include<stdio.h>
#include<string.h>
#define N 100
#define n 50
using namespace std;
int Index(char *S,char *P,int start,int next[]){
	if(start<0||start>strlen(S)-strlen(P)){
		cout<<"startÖµ·Ç·¨£¡"<<endl;
		return -1;
	}
	int i=start;
	int j=0;
	while(i<strlen(S)&&j<(int)strlen(P)){
		if(j==-1||S[i]==P[j]){
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if(j==strlen(P))
		return 1;
	return 0;
}
void get_next(char *P,int next[]){
	int j = 0;
	int k = -1;
	next[0] = -1;
	while(j<=strlen(P)-1){
		if(k==-1||P[j]==P[k]){
			j++;
			k++;
			if(P[j]!=P[k])
				next[j] = k;
			else
				next[j] = next[k];
		}
		else 
			k = next[k];
	}
}
