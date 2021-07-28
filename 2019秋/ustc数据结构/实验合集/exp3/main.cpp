#include "head.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int line=0;//行号
	int flag=0;
	char mark[10]="";
	char str[N]="";
	char file[n]="";
	char key[N]="";
	int next[50];
	FILE *fp;
	printf("输入文件名：\n");
	cin>>file;
	if((fp=fopen(file,"r"))==NULL){
		printf("文件打开失败！");
		return 0;
	}
	while(1){
		printf("输入关键字：\n");
		cin>>key;
		get_next(key,next);
		while(fgets(str,N,fp)!=NULL){
			int re = Index(str,key,0,next);
			line++;
			if(re!=0){
				flag=1;
				cout<<"该行内容："<<str<<"行号："<<line<<endl;	
			}
		}
		if(flag==0)
			cout<<"文本文件中无该关键词"<<endl;
		cout<<"输入任意键继续，输入0结束"<<endl;
		cin>>mark;
		if(mark[0]=='0')
			break;
		rewind(fp);
		flag=0;
		line=0;
	}
	cout<<"程序结束"<<endl;
	fclose(fp); 
	return 0;
}
