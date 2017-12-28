#include<stdlib.h>

#define MAX 100
#define MAXH 10

/*Database for the game*/

struct Lords{
	int force;
	int wealth;
	int tech;           //techpoints
	char own[MAXH][MAXH];
	char ally[MAX];   // allies: ally 0; Enemy 1; Neutral 2;
	
} lords[MAX];

struct Map{
	int res;        // resources
	int pop;        // population
	char status;    // the land' status : to whom it belongs
} map[MAXH][MAXH];

void datashuffle(struct Map a[MAXH][MAXH]);
void init(struct Lords *pl, struct Map m[MAXH][MAXH]);



/*randum distribution of lords' and Map's sources*/
void init(struct Lords *pl, struct Map m[MAXH][MAXH]){         
	int i,j,num = 0;
	int temp;
	
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			m[i][j].res = rand() % 10000 + 10000;
			m[i][j].pop = rand() % 10000 + 10000;
			m[i][j].status = num++;
		}
	}
	datashuffle(m);
	num = 0;
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			pl->own[i][j] = 0; 
			pl->force = rand() % 100 + 50;
			pl->wealth = rand() % 100 +50 ;
			pl++->tech = rand() % 10 + 5;
		}
	}
	
}

/*shuffle lands lords own*/
void datashuffle(struct  Map a[MAXH][MAXH]){
	int i,r1,r2,j;
	char swap;
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			r1 = rand() % MAX;
			r2 = rand() % MAX;
			swap = a[i][j].status;
			a[i][j].status = a[r1][r2].status;
			a[r1][r2].status = swap;
		}
	}
}

/*assign lands to lords*/
void lanass(struct Map a[MAXH][MAXH],struct Lords b[MAX]){
	int i,j,lor=0;
	char t;
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			b[lor++].own[i][j] = 1;
		}
	}
}












