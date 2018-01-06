#include<stdlib.h>
#include"data.h"
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
		r[0][i] = (int) ((int)pl->force*RATE + (int)pl->tech + (int)pl->wealth*RATE + ((int)(pl++->cond))*RATE);
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


/*x1 for attacker, and x2 for defender*/
void judge(struct Lords *pl, struct Map m[MAXH][MAXH],int x1,int y1,int x2,int y2){
	int lor1 = m[x1][y1].status;
	int lor2 = m[x2][y2].status;
	
	;
}

// same as above
void getrid(struct Lords *pl, struct Map m[MAXH][MAXH],int x1,int y1,int x2,int y2,int lor1,int lor2){
	char swap;
	int i,j;
	swap = m[x1][y1].status;
	m[x1][y1].status = m[x2][y2].status;
	m[x2][y2].status = swap;
	i = 0;
	while((pl + lor2)->own[i++] != x2+y2*100+1);
	j = i;
	for(;(pl + lor2)->own[i];i++){
		(pl + lor2)->own[i-1] = (pl + lor2)->own[i];
	}
}























