#include "head.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	SqStack S,W;
	LinkQueue Q;
	InitStack(S);
	InitStack(W);
	InitQueue(Q);
	char status;
	char no[20]="";
	int ntime,n2time,n3time,money;
	char ntc[5]="";
	char exp[100]="";
	while(true){
		cout<<"________________________________________"<<endl;
		cout<<"         ͣ��������"<<endl;
		cout<<"��ѡ�������"<<endl;
		cout<<"A+���ƺ�+ʱ�䣺����������磺A ANHUI001 5��"<<endl;
		cout<<"D+���ƺ�+ʱ�䣺������ȥ�����磺D ANHUI001 10)"<<endl;
		cout<<"P 0 0��ͣ����״̬"<<endl;
		cout<<"W 0 0���򳵳�״̬"<<endl;
		cout<<"E 0 0���˳�����"<<endl;
		gets(exp);
		status = exp[0];
		if(exp[1]!=' '){
            cout<<"�����������������룡"<<endl;
            continue;
		}
		int i,k=0;
		for(i=2; exp[i]!=' '; i++){
            no[k] = exp[i];
            k++;
		}
		no[k] = '\0';
		for(i=i+1,k=0; exp[i]!='\0'; i++){
            ntc[k] = exp[i];
            k++;
		}
		ntc[k] = '\0';
		ntime = atoi(ntc);
		if(status=='E'&&strcmp(no,"0")==0&&ntime==0){
			cout<<"�����˳�"<<endl;
			return 0;
		}
		cout<<"________________________________________"<<endl;
		switch(status){
			case 'A':
				if(StackLocate(S,no,'A')){
                    cout<<"�ó��ѽ���ͣ������"<<endl;
                    break;
				}
				if(!StackFull(S)){//ջ����
					Push(S,no,ntime);
					cout<<"ͣ������λ��(�ӱ����ϵ�n��)��"<<S.top+1<<endl;
				}
				else{//ͣ������
					if(QueueFull(Q)&&Q.length<4){//���в���
						EnQueue(Q,no,ntime);
						cout<<"���λ��(�����ҵ�n��)�� "<<Q.length<<endl;
					}
					else{//����
						cout<<"ͣ��������������������޷����"<<endl;
					}
				}
				break;
			case 'D':
				if(StackLocate(S,no,'D')){
					char no2[10]="";
					strcpy(no2,no);
					while(strcmp(S.c[S.top].no,no)!=0){
						Pop(S,no2,n3time);
						Push(W,no2,n3time);
					}//��Ŀ�공��ջ,Ŀ�공��ĳ���Wջ
					Pop(S,no,n2time);
					while(!StackEmpty(W)){
						Pop(W,no,n3time);//Wջ�г���Sջ
						Push(S,no,n3time);
					}
					if(!QueueEmpty(Q)){
						DeQueue(Q,no);
						QueueNum(Q);
						Push(S,no,ntime);
					}
					if(ntime<n2time){
                        cout<<"��ͣ����ʱ���������������룡"<<endl;
                        break;
					}
					int time = ntime - n2time;//��ʱntimeΪ��ջʱ��,n2timeΪ��ջʱ��,n3timeΪWջ��Ԫ�ص�
					money = time * P;
					cout<<"ͣ��ʱ�䣺"<<time<<" Ӧ�ɷ��ã�"<<money<<endl;
				}
				else
					cout<<"ͣ�������޴˳���\n"<<endl;
				break;
			case 'P':
				if(strcmp(no,"0")!=0||ntime!=0){
					printf("����Ƿ�,�������룡\n");
					break;
				}
				StackTravels(S);
				break;
			case 'W':
				if(strcmp(no,"0")!=0||ntime!=0){
					printf("����Ƿ�,�������룡\n");
					break;
				}
				QueueTravels(Q);
				break;
		}
		cout<<"________________________________________"<<endl;
	}
	return 0;
}
