#include<stdlib.h>
#include"data.c"
#define RATE 0.1

/*Major Functions*/

void rank(struct Lords *pl){
	
	int i,j;
	for(i=0;i<MAX;i++){
		r[i] = (int) ((int)pl->force*RATE + (int)pl->tech*RATE + (int)pl->wealth*RATE + (int)pl++->cond*RATE);
	}
}

void sort(int *a,int *b,int left,int right);
void judge();
