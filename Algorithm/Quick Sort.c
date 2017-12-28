/*Callback = refernece to executive code
	Client passes array of objects to sort() function
	The sort() function calls ack objects's compareTo() as needed.
	
	Java = interfaces(接口） 
	C = function pointers
	C++ = class-type functors
	C# = delegates
*/

#include<stdio.h>

void QuickSort(int *a,int left,int right){
	int i,j,swap,temp;
	if(left > right) return;
	temp = a[left];
	i = left; j = right;
	
	while(i != j){
		while(a[j] >= temp && i<j)
			j--;    //从右边开始找
		while(a[i] <= temp && i<j)
			i++; 
			
		if(i<j){
			swap = a[i];
			a[i] = a[j];
			a[j] = swap;
		}
	}
	a[left] = a[i];
	a[i] = temp;
	QuickSort(a,left,i-1);
	QuickSort(a,i+1,right);
} 


int main()
{
	int a[100],i=0,j;
	while(a[i-1] != 0){
		scanf("%d",&a[i]);
		i++;
	}
	QuickSort(a,0,i-1);
	for(j=0;j<i;j++){
		printf("%d  ",a[j]);
	}
	return 0;
}
