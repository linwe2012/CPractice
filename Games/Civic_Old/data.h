#ifndef DATA_DEFINE
#define DATA_DEFINE

#define MAX 100
#define MAXH 10
extern struct Lords{
	int force;
	int wealth;
	int tech;               //techpoints
	int own[MAX];          //land owned = x + y*100 + 1
	char ally[MAX];         // allies: ally 1; Enemy -1; Neutral 0;
	char cond;              //condition = ally + enemy + nutral;
	char rank;              //rank
} lords[MAX];

extern struct Map{
	int res;        // resources
	int pop;        // population
	unsigned char status;    // the land' status : to whom it belongs
	int force;      //army on the land;
} map[MAXH][MAXH];

extern int playerally[MAXH][MAXH];
extern int color[2][16];
extern int r[2][MAX]; 
extern char survivor;
void datashuffle(struct Map a[MAXH][MAXH]);
void init(struct Lords *pl, struct Map m[MAXH][MAXH]);

#endif
