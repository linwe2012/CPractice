#include<stdlib.h>
#include<stdio.h>

#define MAX 100
#define MAXH 10
#define RATE 0.2

void swap(int *a,int b,int c);
/*quick sort*/
void sort(int *a,int *b,int left,int right){
	int i,j;
	int temp1 = a[left];
	int temp2 = b[left];
	if(left >= right) return;
	i = left; j = right;
	
	while(i<j){
		while(a[j] <= temp1 && i < j)
			j--;
		while(a[i] >= temp1 && i < j)
			i++;
		if(i<j){
			swap(a,i,j);
			swap(b,i,j);
		}
	}
	a[left] = a[i];
	a[i] = temp1;
	b[left] = b[i];
	b[i] = temp2;
	sort(a,b,left,i-1);
	sort(a,b,i+1,right);
	
}
void swap(int *a,int b,int c){
	int temp;
	temp = a[b];
	a[b] = a[c];
	a[c] = temp;
}




main(){
	
	int a[2][10] ={{1,2,3,7,8,1,2,3,5,7},{0}},b[10]={1,2,3,7,8,1,2,3,5,7};
	int i,j;
	for(i=0;i<MAXH;i++)
		printf("%d ",&a[0][i]);
	printf("\n");
	sort(a[0],b,0,9);
	for(i=0;i<MAXH;i++){
		//for(j=0;j<MAXH;j++){
			printf("%d ",&a[0][i]);
		//}
	}
	return 0;
}
