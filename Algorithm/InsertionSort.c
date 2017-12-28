#include<stdio.h>
/* 
void InsertionSort(int *a,int left,int right){
	int i,swap;
	if(left<= right) return;
	if(a[left-1] < a[left]){
		swap = a[left-1];
		a[left-1]=a[left];
		a[left] = swap;
		InsertionSort(a,left-1,right);
	}
	else
	InsertionSort(a,left+1,right);
}
*/ 

void InsertionSort(int *a,int left,int right){
	int i,swap;
	left ++;
	for(;left<=right;left++){
		i = left;
		while(a[i-1] > a[i] && i>0){
			swap = a[i];
			a[i] = a[i-1];
			a[i-1] = swap;
			i --;
		}
	}
	return; 
}


int main()
{
	int a[100],i=0,j;
	while(a[i-1] != 0){
		scanf("%d",&a[i]);
		i++;
	}
	InsertionSort(a,0,i-1);
	for(j=0;j<i;j++){
		printf("%d  ",a[j]);
	}
	
	return 0;
}
