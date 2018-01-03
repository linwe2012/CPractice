#include<stdio.h>
#include"func.h"
#include<graphics.h>
#define WIDTH 480
#define HIGH 640
#define GAPI1 46   //(WIDTH - 30) / MAXH +1
#define GAPJ1 60      //gapj = (HIGH - 50) / MAXH +1;
#define GAPI 45  
#define GAPJ 59

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void inidraw(struct Lords *pl, int player);
void update(struct Lords *pl,int player);
void status_check(int *x,int *y,struct Lords *pl,int player);


int main(int argc, char** argv) {
	int player;
	int attackin_x,attacking_y;
	initgraph(WIDTH,HIGH);
	setbkcolor(EGERGB(0xE0, 0xE0, 0xE0));
	
	init(lords,map);
	rank(lords);
	inidraw(lords,0);
	update(lords,0);
	
	status_check(&attackin_x,&attacking_y,lords,0);
	
	getch();
	closegraph();
	return 0;
}


void inidraw(struct Lords *pl, int player){
	int i,j,a,b;
	player = 0;
	int gapi = (WIDTH - 30) / MAXH;
	int gapj = (HIGH - 50) / MAXH;
	setfillstyle(SOLID_FILL,0x9E9E9E);
	for(i=10,a=0;i<WIDTH - gapi;i+= gapi + 1,a++){
		for(j=50,b=0;j<HIGH - gapj;j+=gapj + 1,b++){
			if(a+b*100 + 1== (pl + player)->own[0]){
				setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
				bar(i,j,i+gapi,j+gapj);
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
			}
			else
				bar(i,j,i+gapi,j+gapj);
		}
	}
	outtextrect(WIDTH/3+35,HIGH-20,WIDTH,HIGH-5,"All rights reserved by Jakiro & Leon");
}

void update(struct Lords *pl,int player){
	char s[50];
	setcolor(EGERGB(0x42, 0x42, 0x42));
	setfontbkcolor(EGERGB(0xE0, 0xE0, 0xE0));
	settextjustify(CENTER_TEXT, TOP_TEXT);
	sprintf(s, "Force: %d      Currency: %d      Tech: %d      rank:%d",(pl + player)->force,(pl + player)->wealth,(pl + player)->tech,(pl + player)->rank);
	outtextxy(WIDTH/2,4,s);
}

//processing mouse message////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void translate_to_real_position(int *x,int *y){
	int gapi = (WIDTH - 30) / MAXH;
	int gapj = (HIGH - 50) / MAXH;
	int xx = *x,yy = *y;
	*x = 10 + xx * gapi + xx;
	*y = 50 + yy * gapj + yy;
}
void translate_to_relative_position(int *x,int *y){
	*x -= 10;
	*y -= 50;
	*x = *x / GAPI;
	*y = *x / GAPJ;
}

//  need relative cordination   ////////////////////////////
int mouse_translate(int x,int y,struct Lords *pl,int player){
	int i;
	int pos = x + y*100 + 1;
	for(i=0;i<MAX;i++){
		if((pl+player)->own[i] == pos)
			return 1;
		else if((pl + player)->own[i] == pos + 100 || (pl + player)->own[i] == pos - 100 || (pl + player)->own[i] == pos + 1||(pl + player)->own[i] == pos -1){
			return 0;
		}
		else if((pl + player)->own[i] == pos + 101 || (pl + player)->own[i] == pos + 99 || (pl + player)->own[i] == pos - 101||(pl + player)->own[i] == pos -99){
			return 0;
		}
		else if((pl + player)->own[i] == 0){
			return -1;
		}
	}
}
//
int integreted_mouse_translate(int x,int y,struct Lords *pl,int player){
	int i;
	int pos = x + y*100 + 1;
	for(i=0;i<MAX;i++){
		if((pl+player)->own[i] == pos)
			return 1;
		else if((pl + player)->own[i] == pos + 100 || (pl + player)->own[i] == pos - 100 || (pl + player)->own[i] == pos + 1||(pl + player)->own[i] == pos -1){
			return 0;
		}
		else if((pl + player)->own[i] == pos + 101 || (pl + player)->own[i] == pos + 99 || (pl + player)->own[i] == pos - 101||(pl + player)->own[i] == pos -99){
			return 0;
		}
		else if((pl + player)->own[i] == 0){
			return -1;
		}
	}
}
///////////////////////////////////////////////////////////

void status_check(int *x,int *y,struct Lords *pl,int player){
	MOUSEMSG msg;
	int pos_status;
	int relative_x,relative_y,real_x,real_y;
	int old_x = (pl+player)->own[0] % 100;   //position for owned lands
	int old_y = (pl+player)->own[0] / 100;
	int gapi = (WIDTH - 30) / MAXH;
	int gapj = (HIGH - 50) / MAXH;
	register int msg_x,msg_y;
	register int omsg_x,omsg_y;
	int flag = 0;
	while(1){
		
		for(; is_run(); delay_fps(120))
		{
			if(mousemsg() && (msg = GetMouseMsg()).uMsg == WM_LBUTTONDOWN)
				break;
			msg_x = (msg.x - 10)/GAPI;
			msg_y = (msg.y - 50)/GAPJ;
			
			pos_status = mouse_translate(msg_x,msg_y,pl,player);
			
			msg_x = 10 + msg_x * GAPI1;
			msg_y = 50 + msg_y * GAPJ1; // translate into real position
			
			if( pos_status == 0 && (!flag || (omsg_x != msg_x || omsg_y != msg_y)  )){
				flag = 1;
				setfillstyle(SOLID_FILL,0x90CAF9);
				bar(msg_x,msg_y,msg_x+gapi,msg_y+gapj);
				
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
				bar(omsg_x,omsg_y,omsg_x+gapi,omsg_y+gapj);
				
				omsg_x = msg_x;
				omsg_y = msg_y;
			}
			else if(flag && pos_status == -1){
				flag = 0;
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
				bar(omsg_x,omsg_y,omsg_x+gapi,omsg_y+gapj);
				omsg_x = msg_x;
				omsg_y = msg_y;
			}
		}
		
		
		real_x=relative_x = msg.x;
		real_y=relative_y = msg.y;
		translate_to_relative_position(&relative_x,&relative_y);
		pos_status = mouse_translate(relative_x,relative_y,pl,player);
		translate_to_relative_position(&real_x,&real_y);
		translate_to_real_position(&real_x,&real_y);
		translate_to_real_position(&old_x,&old_y);
		
		
		if(pos_status == 1){
			setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
			bar(old_x,old_y,old_x+gapi,old_y+gapj);
			setfillstyle(SOLID_FILL,0x1976D2);
			bar(real_x,real_y,real_x+gapi,real_y+gapj);
		}
		
	}	
	
}
