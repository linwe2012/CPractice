#include<stdlib.h>
#include<graphics.h>

#define MAX 100
#define MAXH 10

#define ENEMY 1000
#define ALLY 1000
#define PLAYER 0
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
/* Resources, tech, and population will determines wealth generated in a round.
* Tech will effect how powerful of a troop. 
* So if a lord have force of 40, possesing 100 tech, he attacks another lord whose force is 40 while having 0 Tech.
* Assuming that attack = force * (tech * 0.01 + 1)
* The Attacker will have overwhelmed the defender, with 20 force remaining.
*/
/*
* Lords won't attack allies.
* Chances are that they will declaring war against a neutral lord, or contract peace with a lord at war with him. Chance shouldn't be too high nor remote.
* Any Attack will be ragarded as declaring war
*/
struct Map{
	int res;        // resources
	int pop;        // population
	unsigned char status;    // the land' status : to whom it belongs
	int force;      //army on the land;
} map[MAXH][MAXH];

int r[2][MAX];              //first row: power; second row: corresponding lords
char survivor = MAX;

/* record player's ally, enimies.1 for ally. -1 for enemy. 2 for player*/
/*When all of the lands are either allies' or player's. Player wins*/
int playerally[MAXH][MAXH];

/*reveal superpower in the map. When a lord command over 7 lands, his number should be recorded in the second row of array.
* He will be revealed to the player with color of his column.
* When a lord who previously have his name listed in the array and if he continues to do so, his positiona (column) should not be changed;
*/
int color[2][16] ={{0xF44336,0xE91E63,0x9C27B0,0x673AB7,0x3F51B5,0x0097A7,0x009688,0x43A047,0x689F38,0x827717, 0xF57F17,0xCDDC39,0xFFEB3B,0x795548,0x607D88,0x263238},{0}};

void datashuffle(struct Map a[MAXH][MAXH]);
void init(struct Lords *pl, struct Map m[MAXH][MAXH]);
void lanass(struct Map a[MAXH][MAXH],struct Lords b[MAX]);


/*random distribution of lords' and Map's sources*/
void init(struct Lords *pl, struct Map m[MAXH][MAXH]){         
	int i,j,num = 0,k;
	int temp;
	int lor;
	int lor1,lor2;
	
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
			m[i][j].force = (pl + lor)->force = random(100) + 50;
			(pl + lor)->own[0] = i + j*100+1;
			(pl + lor)->wealth = random(100) +50;
			(pl + lor)->tech = random(10) + 5;
		}
	}
	k = pl->own[0];
	k--;
	playerally[k%MAX][k/MAX] = 2;
	//wage war
	for(i = 1;i < ENEMY;i++) {  
		lor1 = random(MAX);
		lor2 = random(MAX);
		if(lor1 != lor2){
			if(lor1==PLAYER || lor2 == PLAYER){
				k = (lor1 == PLAYER) ? ((pl + lor2)->own[0]) : ((pl + lor1)->own[0]);
				k--;
				playerally[k%MAX][k/MAX] = -1;
			}
			(pl + lor1)->ally[lor2] = -1;
			(pl + lor2)->ally[lor1] = -1;
		}
		
	}
	//contract peace
	for(i = 1;i < ALLY;i++) {
		lor1 = random(MAX);
		lor2 = random(MAX);
		if(lor1 != lor2){
			if(lor1==PLAYER || lor2 == PLAYER){
				k = (lor1 == PLAYER) ? ((pl + lor2)->own[0]) : ((pl + lor1)->own[0]);
				k--;
				playerally[k%MAX][k/MAX] = 1;
			}
			(pl + lor1)->ally[lor2] = 1;
			(pl + lor2)->ally[lor1] = 1;
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

//only for test purpose
void player_reinforce(int wealth,int force){
	int a;
	lords[0].wealth += wealth;
	lords[0].force += force;
	a = lords[0].own[0];
	a--;
	map[a%100][a/100].force += force;
}

/*might come to be useful...or not*////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////



