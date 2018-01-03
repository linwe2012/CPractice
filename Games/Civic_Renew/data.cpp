#include<stdlib.h>
#include<graphics.h>

#define MAX 100
#define MAXH 10

/*Database for the game*/

/*assumming player is lords[0]*/
struct Lords{
	int force;
	int wealth;
	int tech;               //techpoints
	int own[MAX];          //land owned = x + y*100
	char ally[MAX];         // allies: ally 1; Enemy -1; Neutral 0;
	char cond;              //condition = ally + enemy + nutral;
	char rank;              //rank
} lords[MAX];

struct Map{
	int res;        // resources
	int pop;        // population
	char status;    // the land' status : to whom it belongs
	int force;      //army on the land;
} map[MAXH][MAXH];

int r[2][MAX]; //first row: power; second row: corresponding lords
char survivor = MAX;

void datashuffle(struct Map a[MAXH][MAXH]);
void init(struct Lords *pl, struct Map m[MAXH][MAXH]);
void lanass(struct Map a[MAXH][MAXH],struct Lords b[MAX]);


/*random distribution of lords' and Map's sources*/
void init(struct Lords *pl, struct Map m[MAXH][MAXH]){         
	int i,j,num = 0,k;
	int temp;
	int lor;
	
	randomize();
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			m[i][j].res = random(10000) + 10000;
			m[i][j].pop = random(10000) + 10000;
			for(k = 0;k<MAX;k++)
				(pl + i + j)->own[k] = 0; 
			r[1][num] = m[i][j].status = num++;

		}
	}
	datashuffle(m);
	num = 0;
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			lor = m[i][j].status;
			m[i][j].force = (pl + lor)->force = rand() % 100 + 50;
			(pl + lor)->own[0] = i + j*100+1;
			(pl + lor)->wealth = random(100) +50;
			(pl + lor)->tech = random(10) + 5;
		}
	}

}

/*shuffle lands lords own*/ 
void datashuffle(struct  Map a[MAXH][MAXH]){
	randomize();
	int i,r1,r2,j;
	char swap;
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			r1 = random(MAXH);
			r2 = random(MAXH);
			swap = a[i][j].status;
			a[i][j].status = a[r1][r2].status;
			a[r1][r2].status = swap;
		}
	}
}
/*might come to be useful...or not*/

/*assign lands to lords*/
void lanass(struct Map a[MAXH][MAXH],struct Lords b[MAX]){
	int i,j,lor=0;
	char t;
	for(i=0;i<MAXH;i++){
		for(j=0;j<MAXH;j++){
			b[lor++].own[0] = i + j*MAX;
		}
	}
}



