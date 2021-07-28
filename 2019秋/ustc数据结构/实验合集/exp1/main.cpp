#include "joseph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	LinkList *L;
	int n,m;
	scanf("%d",&n);
	int a[n];
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	scanf("%d",&m);
	LinkList *r = CreateList(L,a,n);
	ListLength(L);
	Joseph(L,r,m);
	return 0;
}
