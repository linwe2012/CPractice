#include<stdio.h>

void exch(int *a,int m,int n){
	int swap = a[m];
	a[m] = a[n];
	a[n] = swap;
}


void shuffle(int *a,int left,int right){
	int i,r,len = right - left + 1;
	for(i=left;i<=right;i++){
		r = rand() % len;
		exch(a,i,r);
	}
	
	
}

int main(){
	
	
	return 0;
}
