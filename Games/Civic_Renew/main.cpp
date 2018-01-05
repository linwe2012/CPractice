#include<stdio.h>
#include"func.h"
#include<graphics.h>
#define WIDTH 480
#define HIGH 640
#define GAPI1 46   //(WIDTH - 30) / MAXH +1
#define GAPJ1 60      //gapj = (HIGH - 50) / MAXH +1;
#define GAPI 45  
#define GAPJ 59


/*color here*/
#define BGCOLOR 0xE0E0E0
#define LIGHTGREY 0x9E9E9E


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void inidraw(struct Lords *pl, int player);
void update(struct Lords *pl,int player);
void status_check(int *x,int *y,struct Lords *pl,int player);
MOUSEMSG msgshare;            //shared mouse msg

int main(int argc, char** argv) {
	int player;
	int attackin_x,attacking_y;
	initgraph(WIDTH,HIGH);
	setbkcolor(BGCOLOR);
	
	init(lords,map);
	rank(lords);
	inidraw(lords,0);
	update(lords,0);
	
	status_check(&attackin_x,&attacking_y,lords,0);
	
	getch();
	closegraph();
	return 0;
}

void update_title(struct Lords *pl,int player);
void update_force_one(int x,int y,struct Lords *pl,int player);

void inidraw(struct Lords *pl, int player){
	int i,j,a,b;
	int pos = (pl + player)->own[0];
	pos --;
	setfillstyle(SOLID_FILL,0x9E9E9E);
	outtextrect(WIDTH-100,25,90,25,"Diplomacy");
	for(i=10,a=0;i<WIDTH - GAPI;i+= GAPI + 1,a++){
		for(j=50,b=0;j<HIGH - GAPJ;j+=GAPJ + 1,b++){
			if(a+b*100 == pos){
				setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
				bar(i,j,i+GAPI,j+GAPJ);
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
			}
			else
				bar(i,j,i+GAPI,j+GAPJ);
		}
	}
	outtextrect(WIDTH/3+35,HIGH-20,WIDTH,HIGH-5,"Jakiro & Leon. All rights reserved.");
	settextjustify(CENTER_TEXT, TOP_TEXT);
	outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul");
	i = pos % 100;
	j = pos / 100;
	update_force_one(i,j,pl,player);
}

void update_title(struct Lords *pl,int player){
	char s[50];
	setcolor(EGERGB(0x42, 0x42, 0x42));
	setfontbkcolor(BGCOLOR);
	settextjustify(CENTER_TEXT, TOP_TEXT);
	sprintf(s, "Force: %d      Currency: %d      Tech: %d      rank:%d",(pl + player)->force,(pl + player)->wealth,(pl + player)->tech,(pl + player)->rank);
	outtextxy(WIDTH/2,4,s);
}
void update_force_one(int x,int y,struct Lords *pl,int player){
	int force;
	force = map[x][y].force;
	char s[50];
	setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
	x = 10 + x * GAPI1;
	y = 50 + y * GAPJ1;
	bar(x,y,x+GAPI,y+GAPJ);
	sprintf(s, "%d",force);
	outtextxy((x+GAPI)/2,(y + GAPJ)/2,s);
}

void update(struct Lords *pl,int player){
	char s[50];
	setcolor(EGERGB(0x42, 0x42, 0x42));
	setfontbkcolor(BGCOLOR);
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
	int realpos;
	for(i=0;i<MAX;i++){
		realpos = (pl + player)->own[i];
		if(realpos == pos)
			return 1;
		else if(realpos == pos + 100 || realpos == pos - 100 || realpos == pos + 1||realpos == pos -1){
			return 0;
		}
		else if(realpos == pos + 101 || realpos == pos + 99 || realpos == pos - 101||realpos == pos -99){
			return 0;
		}
		else if(realpos == 0){
			return -1;
		}
		else if(0);
	}
}

int more_mouse_translate(int x,int y,struct Lords *pl,int player){
	int i;
	int pos;
	int realpos;
	if((x>=WIDTH-100 && x<=WIDTH) && (y>=10 && y<= 50))
		return 2;
	x = (x - 10)/GAPI;
	y = (y - 50)/GAPJ;
	pos = x + y*100 + 1;
	for(i=0;i<MAX;i++){
		realpos = (pl + player)->own[i];
		if(realpos == pos)
			return 1;
		else if(realpos == pos + 100 || realpos == pos - 100 || realpos == pos + 1||realpos == pos -1){
			return 0;
		}
		else if(realpos == pos + 101 || realpos == pos + 99 || realpos == pos - 101||realpos == pos -99){
			return 0;
		}
		else if(realpos == 0){
			return -1;
		}
	}
}


int simple_mouse_translate(int x,int y){
	if((x>=WIDTH-100 && x<=WIDTH) && (y>=10 && y<= 50))
		return 2;
	else return 0;
}

void show_diplomacy(){
	int i,j;
	int a,b;
	MOUSEMSG msg;
	for(i=10,a=0;i<WIDTH - GAPI;i+= GAPI + 1,a++){
		for(j=50,b=0;j<HIGH - GAPJ;j+=GAPJ + 1,b++){
			if(playerally[a][b] == -1){
				setfillstyle(SOLID_FILL,0xC62828);
				bar(i,j,i+GAPI,j+GAPJ);
			}
			else if(playerally[a][b] == 1){
				setfillstyle(SOLID_FILL,0x2E7D32);
				bar(i,j,i+GAPI,j+GAPJ);
			}	
		}
	}
	for(; is_run(); delay_fps(120)){
		if(mousemsg() && (msg = GetMouseMsg()).uMsg == WM_LBUTTONDOWN){
			if(simple_mouse_translate(msg.x,msg.y)){
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
				for(i=10,a=0;i<WIDTH - GAPI;i+= GAPI + 1,a++){
					for(j=50,b=0;j<HIGH - GAPJ;j+=GAPJ + 1,b++){
						if(playerally[a][b] == 2){
							setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
							bar(i,j,i+GAPI,j+GAPJ);
							setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
						}
						else
							bar(i,j,i+GAPI,j+GAPJ);
					}
				}
				return;
			}
		}
	}
}
void mousecheck_inpos(int ox,int oy,struct Lords *pl,int player){
	int keyboardmsg;
	MOUSEMSG msg;
	int x,y;
	register int msg_x,msg_y;
	register int omsg_x,omsg_y;
	int pos_status;
	int pos;
	int adder;
	int pos1 = ox + oy*100 +1;
	int pos2;
	int flag = 0;
	
	setfillstyle(SOLID_FILL,BGCOLOR);
	bar(0,HIGH - 45,WIDTH,HIGH - 25);
	outtextxy(WIDTH/2,HIGH - 45,"Press Enter to Cancel Selection. Careful! You can't undo.'");
	while(1){
	for(; is_run(); delay_jfps(100))
		{
			if(kbhit() && ((keyboardmsg = getch()) == 'm' || keyboardmsg == 'M')){
				setcolor(LIGHTGREY);
				outtextxy(WIDTH/2,HIGH - 45,"Too lazy to write it. Figure it out yourself! Auf Wiedersehen!");
				while((msg = GetMouseMsg()).uMsg != WM_LBUTTONDOWN )
					;
				setfillstyle(SOLID_FILL,BGCOLOR);
				bar(0,HIGH - 45,WIDTH,HIGH - 25);
				outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul.");
				continue;
			}
			else if(keyboardmsg == '\n'){
				bar(0,HIGH - 45,WIDTH,HIGH - 25);
				outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul.");
				return;
			}
			else if(keyboardmsg == ' '){
				adder = 1;
				if((pl+player)->wealth > 0){
						(pl+player)->force += adder;
						map[ox][oy].force += adder;
						(pl+player)->wealth -= adder;
						update_title(pl,player);
						 update_force_one(ox,oy,pl,player);
					}
				else
					continue;
				for(; is_run() && keystate(' '); delay_fps(30))
				{
					if((pl+player)->wealth > 0){
						(pl+player)->force += adder;
						map[ox][oy].force += adder;
						(pl+player)->wealth -= adder;
						update_title(pl,player);
					}
					else
						break;
					
				}
			}
			if(mousemsg() && (msg = GetMouseMsg()).uMsg == WM_LBUTTONDOWN)
				break;
			if(msg.x == ox && msg.y ==oy)
				continue;
			msg_x = (msg.x - 10)/GAPI;
			msg_y = (msg.y - 50)/GAPJ;
			
			pos_status = mouse_translate(msg_x,msg_y,pl,player);
			
			msg_x = 10 + msg_x * GAPI1;
			msg_y = 50 + msg_y * GAPJ1; // translate into real position
			
			if( (pos_status == 0 || pos_status == 1)&& (!flag || (omsg_x != msg_x || omsg_y != msg_y)  )){
				flag = 1;
				setfillstyle(SOLID_FILL,0x90CAF9);
				bar(msg_x,msg_y,msg_x+GAPI,msg_y+GAPJ);
				
				if(pos_status){
					setfillstyle(SOLID_FILL,0x1976D2);	
				}
				else
					setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
				bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
				
				omsg_x = msg_x;
				omsg_y = msg_y;
			}
			else if(flag && pos_status == -1){
				flag = 0;
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
				bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
				omsg_x = msg_x;
				omsg_y = msg_y;
			}
		}
		x = msg.x;
		y = msg.y;
		pos = more_mouse_translate(x,y,pl,player);
		if(pos == 2){
			show_diplomacy();
			continue;
		}
		else if(pos == 1){
			adder = 1;
			msg_x = (msg.x - 10)/GAPI;
			msg_y = (msg.y - 50)/GAPJ;
			if(map[ox][oy].force >= adder){
				map[ox][oy].force -= adder;
				map[msg_x][msg_y].force += adder;
				adder ++;
				 update_force_one(ox,oy,pl,player);
				 update_force_one(msg_x,msg_y,pl,player);
			}
			else{
				map[ox][oy].force = 0;
				map[msg_x][msg_y].force +=1;
				update_force_one(ox,oy,pl,player);
				 update_force_one(msg_x,msg_y,pl,player);
				continue;
				}
			for(; is_run() && mousemsg() && (msg = GetMouseMsg()).uMsg != WM_LBUTTONUP ; delay_jfps(30)){
					if(map[ox][oy].force >= adder){
						map[ox][oy].force -= adder;
						map[msg_x][msg_y].force += adder;
						adder ++;
						update_force_one(ox,oy,pl,player);
				 		update_force_one(msg_x,msg_y,pl,player);
					}
					else{
						adder = map[ox][oy].force;
						map[ox][oy].force = 0;
						map[msg_x][msg_y].force += adder;
						update_force_one(ox,oy,pl,player);
				 		update_force_one(msg_x,msg_y,pl,player);
						break;
					}
				
			}
		}
		else if(pos == 0){
			;
		}
		
	}
}
///////////////////////////////////////////////////////////



void status_check(int *x,int *y,struct Lords *pl,int player){
	MOUSEMSG msg;
	int keyboardmsg;
	int pos_status;
	int last_pos_status = 0;
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
			if(kbhit() && ((keyboardmsg = getch()) == 'm' || keyboardmsg == 'M')){
				setcolor(LIGHTGREY);
				outtextxy(WIDTH/2,HIGH - 45,"Too lazy to write it. Figure it out yourself! Auf Wiedersehen!");
				while((msg = GetMouseMsg()).uMsg != WM_LBUTTONDOWN )
					;
				setfillstyle(SOLID_FILL,BGCOLOR);
				bar(0,HIGH - 45,WIDTH,HIGH - 25);
				outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul.");
				continue;
			}
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
				bar(msg_x,msg_y,msg_x+GAPI,msg_y+GAPJ);
				
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
				bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
				
				omsg_x = msg_x;
				omsg_y = msg_y;
			}
			else if(flag && pos_status == -1){
				flag = 0;
				setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
				bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
				omsg_x = msg_x;
				omsg_y = msg_y;
			}
		}
		
		
		real_x=relative_x = msg.x;
		real_y=relative_y = msg.y;
		pos_status = more_mouse_translate(real_x,real_y,pl,player);
		if(pos_status == 2){
			show_diplomacy();
			continue;
		}
		translate_to_relative_position(&real_x,&real_y);
		translate_to_real_position(&real_x,&real_y);
		translate_to_real_position(&old_x,&old_y);
		
		
		if(pos_status == 1){
			setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
			bar(old_x,old_y,old_x+GAPI,old_y+GAPI);
			setfillstyle(SOLID_FILL,0x1976D2);
			bar(real_x,real_y,real_x+GAPI,real_y+GAPI);
		}
		
	}	
	
}
