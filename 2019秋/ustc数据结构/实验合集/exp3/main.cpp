#include "head.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int line=0;//�к�
	int flag=0;
	char mark[10]="";
	char str[N]="";
	char file[n]="";
	char key[N]="";
	int next[50];
	FILE *fp;
	printf("�����ļ�����\n");
	cin>>file;
	if((fp=fopen(file,"r"))==NULL){
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	while(1){
		printf("����ؼ��֣�\n");
		cin>>key;
		get_next(key,next);
		while(fgets(str,N,fp)!=NULL){
			int re = Index(str,key,0,next);
			line++;
			if(re!=0){
				flag=1;
				cout<<"�������ݣ�"<<str<<"�кţ�"<<line<<endl;	
			}
		}
		if(flag==0)
			cout<<"�ı��ļ����޸ùؼ���"<<endl;
		cout<<"�������������������0����"<<endl;
		cin>>mark;
		if(mark[0]=='0')
			break;
		rewind(fp);
		flag=0;
		line=0;
	}
	cout<<"�������"<<endl;
	fclose(fp); 
	return 0;
}
