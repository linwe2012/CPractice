#include<stdio.h>

void ShellSort(int *a,int left,int right){
	int length = right - left + 1, h=1,i,j,temp,swap;
	while (h < length / 3) h = h*3+1;
	while(h > 0){
		for(i=left;i<=right;i++){
			for(j=i;j<=right;j+=h){
				temp = j;
				while(a[temp] < a[temp-h] && temp-h>=0){
					swap = a[temp];
					a[temp] = a[temp-h];
					a[temp-h] = swap;
				}
			}
		}
		h /= 3;
	}
}


int main()
{
	int a[100],i=0,j;
	while(a[i-1] != 0){
		scanf("%d",&a[i]);
		i++;
	}
	ShellSort(a,0,i-1);
	for(j=0;j<i;j++){
		printf("%d  ",a[j]);
	}
	
	return 0;
}
