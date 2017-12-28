#include<stdio.h>

void swap(int *a,int *b){
	int swap = *a;
	*a = *b;
	*b = swap;
}

void InsertionSort(int *a,int left,int right){
	int i,j;
	for(i=left+1;i<=right;i++){
		j = i;
		while(j-1 >= left && a[j-1] > a[j] ){
			swap(&a[j-1] , &a[j]);
			j--;
		}
	}
}

void merge(int *a,int *aux,int left,int mid,int right){ // merge from a[] to aux[]
	int i=left,j=mid+1,k;
	for(k=left;k<=right;k++){
		if(i > mid)            aux[k] = a[j++];
		if(j > right)          aux[k] = a[i++];
		else if(a[i] > a[j])    aux[k] = a[j++];
		else                    aux[k] = a[i++];
	}
}


void MergeSort(int *a, int *aux, int left, int right){
	int mid = left + (left + right) / 2;
	if(right <= left) return;
	/*if(right - left + 1 <= 5){
		InsertionSort(a,left,right);
		return;
	} */
	MergeSort(a,aux,left,mid);
	MergeSort(a,aux,mid+1,right);
	//if(a[mid] <= a[mid+1]) return; 
	merge(a,aux,left,mid,right);
}





int main()
{
	int a[100],i=0,j,aux[100];
	while(a[i-1] != 0){
		scanf("%d",&a[i]);
		aux[i] = a[i];
		i++;
	}
	MergeSort(a,aux,0,i-1);
	for(j=0;j<i;j++){
		printf("%d  ",a[j]);
	}
	
	return 0;
}
