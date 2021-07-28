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
		cout<<"         停车场管理"<<endl;
		cout<<"请选择操作："<<endl;
		cout<<"A+车牌号+时间：车辆到达（例如：A ANHUI001 5）"<<endl;
		cout<<"D+车牌号+时间：车辆离去（例如：D ANHUI001 10)"<<endl;
		cout<<"P 0 0：停车场状态"<<endl;
		cout<<"W 0 0：候车场状态"<<endl;
		cout<<"E 0 0：退出程序"<<endl;
		gets(exp);
		status = exp[0];
		if(exp[1]!=' '){
            cout<<"输入有误，请重新输入！"<<endl;
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
			cout<<"结束退出"<<endl;
			return 0;
		}
		cout<<"________________________________________"<<endl;
		switch(status){
			case 'A':
				if(StackLocate(S,no,'A')){
                    cout<<"该车已进入停车场！"<<endl;
                    break;
				}
				if(!StackFull(S)){//栈不满
					Push(S,no,ntime);
					cout<<"停车场内位置(从北到南第n辆)："<<S.top+1<<endl;
				}
				else{//停车场满
					if(QueueFull(Q)&&Q.length<4){//队列不满
						EnQueue(Q,no,ntime);
						cout<<"便道位置(从左到右第n辆)： "<<Q.length<<endl;
					}
					else{//队满
						cout<<"停车场已满！便道已满！无法到达！"<<endl;
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
					}//将目标车出栈,目标车后的车进W栈
					Pop(S,no,n2time);
					while(!StackEmpty(W)){
						Pop(W,no,n3time);//W栈中车进S栈
						Push(S,no,n3time);
					}
					if(!QueueEmpty(Q)){
						DeQueue(Q,no);
						QueueNum(Q);
						Push(S,no,ntime);
					}
					if(ntime<n2time){
                        cout<<"出停车场时间有误，请重新输入！"<<endl;
                        break;
					}
					int time = ntime - n2time;//此时ntime为出栈时间,n2time为进栈时间,n3time为W栈中元素的
					money = time * P;
					cout<<"停留时间："<<time<<" 应缴费用："<<money<<endl;
				}
				else
					cout<<"停车场中无此车！\n"<<endl;
				break;
			case 'P':
				if(strcmp(no,"0")!=0||ntime!=0){
					printf("输入非法,重新输入！\n");
					break;
				}
				StackTravels(S);
				break;
			case 'W':
				if(strcmp(no,"0")!=0||ntime!=0){
					printf("输入非法,重新输入！\n");
					break;
				}
				QueueTravels(Q);
				break;
		}
		cout<<"________________________________________"<<endl;
	}
	return 0;
}
