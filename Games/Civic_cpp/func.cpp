#include<stdlib.h>
#include"data.cpp"
#define RATE 0.1

/*Major Functions*/

void sort(int *a,int *b,int left,int right);
void swap(int *a,int b,int c);

/*rank lords and return player's rank*/
int rank(struct Lords *pl){
	int i,j;
	struct Lords *pll = pl;
	int lor, ret;
	char count = 1;
	for(i=0;i<MAX;i++){
		r[0][i] = (int) ((int)pl->force*RATE + (int)pl->tech*RATE + (int)pl->wealth*RATE + ((int)(pl++->cond))*RATE);
	}
	sort(r[0],r[1],0,MAX-1);
	for(i=0;i<MAX;i++){
		lor = r[1][i];
		if(!lor) ret = count;
		(pll + lor)->rank = count++;
	}
	return ret;
}

/*quick sort*/
void sort(int *a,int *b,int left,int right){
	int i,j;
	int temp1 = a[left];
	int temp2 = b[left];
	if(left >= right) return;
	i = left; j = right;
	
	while(i<j){
		while(a[j--] <= temp1 && i < j)
			;
		while(a[i++] >= temp1 && i < j)
			;
		if(i<j){
			swap(a,i,j);
			swap(b,i,j);
		}
	}
	a[left] = a[i];
	a[i] = temp1;
	b[left] = b[i];
	b[i] = temp2;
	sort(a,b,left,i);
	sort(a,b,i+1,right);
	
}
void swap(int *a,int b,int c){
	int temp;
	temp = a[b];
	a[b] = a[c];
	a[c] = temp;
}


void judge(struct Lords *pl, struct Map m[MAXH][MAXH],int x1,int y1,int x2,int y2){
	
	;
}

