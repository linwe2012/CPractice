#include<stdio.h>
#include"func.h"
#include<graphics.h>
#define WIDTH 480
#define HIGH 640
#define GAPI1 46   //(WIDTH - 30) / MAXH +1
#define GAPJ1 60      //gapj = (HIGH - 50) / MAXH +1;
#define GAPI 45  
#define GAPJ 59


#define DELAY 200

/*color here*/
#define BGCOLOR 0xE0E0E0
#define LIGHTGREY 0x9E9E9E
#define SELECTED 0x1976D2
#define UNSELECTED 0x2196F3


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void inidraw(struct Lords *pl, int player);
void update(struct Lords *pl,int player);
int status_check(int *x,int *y,struct Lords *pl,int player);
MOUSEMSG msgshare;            //shared mouse msg
char s[50];
int sel;

int main(int argc, char** argv) {
	int player;
	int attackin_x,attacking_y;
	initgraph(WIDTH,HIGH);
	setbkcolor(BGCOLOR);
	
	init(lords,map);
	player_reinforce(200,1000);
	rank(lords);
	inidraw(lords,0);
	
	status_check(&attackin_x,&attacking_y,lords,0);
	
	getch();
	closegraph();
	return 0;
}

void update_title(struct Lords *pl,int player);
void update_force_one(int x,int y,struct Lords *pl,int player,int ifselect);

void inidraw (struct Lords *pl, int player){
	int i,j,a,b;
	int pos = (pl + player)->own[0];
	/*
	LOGFONTA f;
	/*preset front*/
	/*
	getfont(&f);                      
	strcpy(f.lfFaceName, "Arial");         
	f.lfQuality = ANTIALIASED_QUALITY;  
	setfont(&f);                          
	*/
	
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
	outtextrect(WIDTH/3+35,HIGH-20,WIDTH,HIGH-5,"All rights reserved.");
	settextjustify(CENTER_TEXT, TOP_TEXT);
	outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul");
	i = pos % 100;
	j = pos / 100;
	update_force_one(i,j,pl,player,0);
	update_title(lords,PLAYER);
}

void update_title(struct Lords *pl,int player){
	setcolor(EGERGB(0x42, 0x42, 0x42));
	setfillstyle(SOLID_FILL,BGCOLOR);
	bar(0,0,WIDTH,25);
	setfontbkcolor(BGCOLOR);
	settextjustify(CENTER_TEXT, TOP_TEXT);
	sprintf(s, "Force: %d      Currency: %d      Tech: %d      rank:%d",(pl + player)->force,(pl + player)->wealth,(pl + player)->tech,(pl + player)->rank);
	
	outtextxy(WIDTH/2,4,s);
}
void update_force_one(int x,int y,struct Lords *pl,int player,int ifselect){
	int f;
	f = map[x][y].force;
	x = 10 + x * GAPI1;
	y = 50 + y * GAPJ1;
	if(ifselect){
		setfillstyle(SOLID_FILL,SELECTED);
		setcolor(WHITE);
		setfontbkcolor(SELECTED);
	}
	else{
		setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
		setcolor(0xBBDEFB);
		setfontbkcolor(UNSELECTED);
	}
	bar(x,y,x+GAPI,y+GAPJ);

	
	sprintf(s, "%d",f);
	outtextxy((2 * x+GAPI)/2,(2 * y + GAPJ)/2,s);
}

void update(struct Lords *pl,int player){
	int i,j,a,b,k;
	int pos = (pl + player)->own[0];
	/*
	LOGFONTA f;
	/*preset front*/
	/*
	getfont(&f);                      
	strcpy(f.lfFaceName, "Arial");         
	f.lfQuality = ANTIALIASED_QUALITY;  
	setfont(&f);                          
	*/
	cleardevice();
	setfillstyle(SOLID_FILL,0x9E9E9E);
	outtextrect(WIDTH-100,25,90,25,"Diplomacy");
	for(i=10,a=0;i<WIDTH - GAPI;i+= GAPI + 1,a++){
		for(j=50,b=0;j<HIGH - GAPJ;j+=GAPJ + 1,b++){
			pos = a+b*100+1;
			k = 0;
			while((pl + player)->own[k]){
				if(pos == (pl + player)->own[k]){
					setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
					bar(i,j,i+GAPI,j+GAPJ);
					setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
					continue;
				}
			}
			bar(i,j,i+GAPI,j+GAPJ);
		}
	}
	outtextrect(WIDTH/3+35,HIGH-20,WIDTH,HIGH-5,"All rights reserved.");
	settextjustify(CENTER_TEXT, TOP_TEXT);
	outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul");
	i = pos % 100;
	j = pos / 100;
	update_force_one(i,j,pl,player,0);
}

/*x1 & y1 is our defeater's coordinate
*/
void launch_convertion(int x1,int y1,struct Lords *pl,int player){
	
	int i,lor;
	int temp,temppower;
	i = 0;
	lor = map[x1][y1].status;
	while(i<MAX && (pl+player)->own[++i])
		;
	(pl+player)->own[i] = x1 + y1 * 100 +1;
	playerally[x1][y1] = 2;
	i = 0; 
	while((pl+lor)->own[++i])
		;
	(pl + lor)->own[--i] = 0;
	if((pl + lor)->own[i] == 0){
		survivor--;
	}
	temp = 0;
	while(r[1][temp++] != lor)
		;
	temppower = r[0][--temp];
	i = 1;
	while(temp + i<MAX && temppower<r[1][temp + i]){
		r[1][temp + i -1] = r[1][temp + i];
		r[0][temp + i -1] = r[1][temp + i];
		i++;
	}
	i--;
	r[1][temp + i] = temppower;
	r[0][temp + i] = lor;
	
	update_force_one(x1,y1,pl,player,0);
	update_title(pl,player);
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
	int pos;
	int realpos;
	i = 0;
	pos = x + y*100 + 1;
	while((pl + player)->own[i] != 0){
		if(  ((pl + player)->own[i])  == pos)
			return 1;
		i++;
	}
	
	for(i=0;i<MAX;i++){
		realpos = (pl + player)->own[i];
		if(realpos == pos + 100 || realpos == pos - 100 || realpos == pos + 1||realpos == pos -1){
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

int more_mouse_translate(int x,int y,struct Lords *pl,int player){
	int i;
	int pos;
	int realpos;
	if((x>=WIDTH-100 && x<=WIDTH) && (y>=10 && y<= 50))
		return 2;
	x = (x - 10)/GAPI;
	y = (y - 50)/GAPJ;
	pos = x + y*100 + 1;
	i = 0;
	while((pl + player)->own[i] != 0){
		if(((pl + player)->own[i]) == pos)
			return 1;
		i++;
	}
	for(i=0;i<MAX;i++){
		realpos = (pl + player)->own[i];
		if(realpos == pos + 100 || realpos == pos - 100 || realpos == pos + 1||realpos == pos -1){
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
// x,y are real position,while sx,sy should be relative.
int selected_mouse_translate(int x,int y,int sx,int sy,struct Lords *pl,int player){
	int i;
	int pos;
	int realpos;
	int spos = sx + sy*100 + 1;
	if((x>=WIDTH-100 && x<=WIDTH) && (y>=10 && y<= 50))
		return 2;
	
	x = (x - 10)/GAPI;
	y = (y - 50)/GAPJ;
	
	pos = x + y*100 + 1;
	i = 0;
	
	while( (realpos = (pl + player)->own[i]) != 0){
		if(((pl + player)->own[i]) == pos){
			if( (realpos == spos + 100 || realpos == spos - 100 || realpos == spos + 1||realpos == spos -1)){
				return 3;
			}
			else if(realpos == spos + 101 || realpos == spos + 99 || realpos == spos - 101||realpos == spos -99){
				return 3;
			}
		
			return 1;
		}
		i++;
	}
	
	realpos = sx + sy*100 +1;
	if(realpos == pos + 100 || realpos == pos - 100 || realpos == pos + 1||realpos == pos -1){
		return 0;
	}
	else if(realpos == pos + 101 || realpos == pos + 99 || realpos == pos - 101||realpos == pos -99){
		return 0;
	}
		
	else if(1){
		return -1;
	}
	
}
// 3: abut selected and is owned
// 0: abut selected but not owned
// 1: not abut but is owned
// 2: diplomacy map


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
				i = 0;
				while(lords[PLAYER].own[i]){
					j = lords[PLAYER].own[i];
					j--;
					update_force_one(j%100,j/100,lords,PLAYER,(sel == j+1));
					
					i++;
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
	int relative_x=ox,relative_y=oy;
	int pos_status;
	int pos=0,old_pos=1;
	int adder;
	int pos1 = ox + oy*100 +1;
	int pos2;
	int flag = 0;
	int lor,emy_force;
	int ifinpos=1;
	
	setfillstyle(SOLID_FILL,BGCOLOR);
	bar(0,HIGH - 45,WIDTH,HIGH - 25);
	setcolor(LIGHTGREY);
	outtextxy(WIDTH/2,HIGH - 45,"Press Enter to Cancel Selection. Careful! You can't undo.");
	update_force_one(ox,oy,pl,player,1);
	delay_ms(1000);
	while(1){
	for(; is_run(); delay_jfps(120))
		{
			if(kbhit() && (keyboardmsg = getch()) ){
				if(keyboardmsg == '\n' || keyboardmsg == 'q' || keyboardmsg == 'Q'){
					bar(0,HIGH - 45,WIDTH,HIGH - 25);
					setcolor(LIGHTGREY);
					outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul.");
					update_force_one(ox,oy,pl,player,0);
					fflush(stdin);
					return;
				}
				else if(keyboardmsg == ' '){
					adder = 1;
					if((pl+player)->wealth > 0){
							(pl+player)->force += adder;
							map[ox][oy].force += adder;
							(pl+player)->wealth -= adder;
							update_title(pl,player);
							update_force_one(ox,oy,pl,player,1);
							fflush(stdin);
							delay_ms(DELAY);
							if(!keystate(' ')){
								continue;
							}
						}
					else{
						fflush(stdin);
						delay_ms(DELAY);
						continue;
					}
						
					for(;keystate(' '); delay_jfps(60))
					{
						if((pl+player)->wealth > 0){
							(pl+player)->force += adder;
							map[ox][oy].force += adder;
							(pl+player)->wealth -= adder;
							update_title(pl,player);
							update_force_one(ox,oy,pl,player,1);
							if(keystate(0x01)){
								fflush(stdin);
								delay_ms(DELAY);
								break;
							}
						}
						else{
							fflush(stdin);
							delay_ms(DELAY);
							break;
						}
						
					}
					fflush(stdin);
					continue;
				}
			}
			
			if(mousemsg() && (msg = GetMouseMsg()).uMsg == WM_LBUTTONDOWN)
				break;
			
			msg_x = (msg.x - 10)/GAPI;
			msg_y = (msg.y - 50)/GAPJ;
			
			if(msg_x == ox && msg_y ==oy){
				ifinpos = 1;
				continue;
				
			}
				
			
			
			pos_status = selected_mouse_translate(msg.x,msg.y,ox,oy,pl,player);
			
			msg_x = 10 + msg_x * GAPI1;
			msg_y = 50 + msg_y * GAPJ1; // translate into real position
			// 3: abut selected and is owned
			// 0: abut selected but not owned
			// 1: not abut but is owned
			//-1: not abut, not owned
			// 2: diplomacy map
			
			if( (pos_status == 0 || pos_status == 3)&& (!flag || (omsg_x != msg_x || omsg_y != msg_y)  )){
				flag = 1;
				setfillstyle(SOLID_FILL,0x90CAF9);
				bar(msg_x,msg_y,msg_x+GAPI,msg_y+GAPJ);
				
				if(ifinpos == 1){
					ifinpos = 0;
					update_force_one(ox,oy,pl,player,1);
				}
				
				//don't know if it is useful///////
				if(pos_status == 3){
					relative_x = (msg.x - 10)/GAPI;
					relative_y = (msg.y - 50)/GAPJ;
				}
				///////////////////////////////////
				if(old_pos == 3){
					setfillstyle(SOLID_FILL,UNSELECTED);
					bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
					update_force_one(relative_x,relative_y,pl,player,0);
						
				}
				else{
					setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
					bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
				}
				
				omsg_x = msg_x;
				omsg_y = msg_y;
				old_pos = pos_status;
			}
			else if(flag && pos_status == -1){
				ifinpos = flag = 0;
				if(old_pos == 3){
					setfillstyle(SOLID_FILL,UNSELECTED);
					bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
					update_force_one(relative_x,relative_y,pl,player,0);
				}
				else{
					setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
					bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
				}
				omsg_x = msg_x;
				omsg_y = msg_y;
				old_pos = pos_status;
			}
			old_pos = pos_status;
			update_force_one(ox,oy,pl,player,1);
		}
		x = msg.x;
		y = msg.y;
		pos = more_mouse_translate(x,y,pl,player);
		
		msg_x = (x - 10)/GAPI;
		msg_y = (y - 50)/GAPJ;
		
		
		if(pos == 2){
			show_diplomacy();
			continue;
		}
		//transfer army!
		else if(pos == 1){
			adder = 1;
			if(map[ox][oy].force >= adder){
				map[ox][oy].force -= adder;
				map[msg_x][msg_y].force += adder;
				adder ++;
				update_force_one(ox,oy,pl,player,1);
				update_force_one(msg_x,msg_y,pl,player,0);
				delay_ms(DELAY);
				if((msg = GetMouseMsg()).uMsg != WM_LBUTTONUP){
					continue;
				}
			}
			else{
				update_force_one(ox,oy,pl,player,1);
				update_force_one(msg_x,msg_y,pl,player,0);
				continue;
				}
			for(; is_run() && (msg = GetMouseMsg()).uMsg != WM_LBUTTONUP ; delay_jfps(120)){
					if(map[ox][oy].force >= adder){
						map[ox][oy].force -= adder;
						map[msg_x][msg_y].force += adder;
						adder ++;
						update_force_one(ox,oy,pl,player,1);
				 		update_force_one(msg_x,msg_y,pl,player,0);
					}
					else{
						adder = map[ox][oy].force;
						map[ox][oy].force = 0;
						map[msg_x][msg_y].force += adder;
						update_force_one(ox,oy,pl,player,1);
				 		update_force_one(msg_x,msg_y,pl,player,0);
						break;
					}
				
			}
		}
		//attack!
		else if(pos == 0){
			adder = 1;
			//map[msg_x][msg_y].force;
			
			if(map[ox][oy].force >= adder && map[msg_x][msg_y].status != player){
				map[ox][oy].force -= adder;
				map[msg_x][msg_y].force -= adder;
				((pl + player)->force)--;
				adder ++;
				update_title(pl,player);
				if(map[msg_x][msg_y].force < 0){
					map[msg_x][msg_y].force = -map[msg_x][msg_y].force;
					launch_convertion(msg_x,msg_y,pl,player);
					delay_ms(DELAY);
					continue;
				}
				update_force_one(ox,oy,pl,player,1);
				delay_ms(DELAY);
				if(!keystate(0x01)){
					delay_ms(DELAY);
					continue;
				}
			}
			else if(map[msg_x][msg_y].status == player){
				continue;
			}
			else{
				if(map[ox][oy].force == 0){
					delay_ms(DELAY);
					continue;
				}
				map[ox][oy].force = 0;
				map[msg_x][msg_y].force -=1;
				((pl + player)->force)--;
				update_title(pl,player);
				update_force_one(ox,oy,pl,player,1);
				delay_ms(DELAY);
				continue;
			}
			
			for(; is_run() && keystate(0x01); delay_jfps(120)){
					if(map[ox][oy].force >= adder ){
						map[ox][oy].force -= adder;
						map[msg_x][msg_y].force -= adder;
						((pl + player)->force)-=adder;
						adder ++;
						update_title(pl,player);
						
				 		if(map[msg_x][msg_y].force < 0){
				 			map[msg_x][msg_y].force = -map[msg_x][msg_y].force;
							launch_convertion(msg_x,msg_y,pl,player);
							adder = 0;
							delay_ms(DELAY);
							break;
						}
						update_force_one(ox,oy,pl,player,1);
						
					}
					else{
						adder = map[ox][oy].force;
						if(adder == 0){
							
							delay_ms(DELAY);
							break;
						}
						map[ox][oy].force = 0;
						map[msg_x][msg_y].force -= adder;
						((pl + player)->force)-=adder;
						update_title(pl,player);
				 		if(map[msg_x][msg_y].force < 0){
				 			map[msg_x][msg_y].force = -map[msg_x][msg_y].force;
							launch_convertion(msg_x,msg_y,pl,player);
							adder = 0;
							
							delay_ms(DELAY);
							break;
						}
						update_force_one(ox,oy,pl,player,1);
						
						delay_ms(DELAY);
						break;
					}
				
			}
			
		}
		
	}
}

int next_round(struct Lords *pl){
	int temp;
	fflush(stdin);
	setfillstyle(SOLID_FILL,BGCOLOR);
	bar(0,HIGH - 45,WIDTH,HIGH - 25);
	setcolor(LIGHTGREY);
	outtextxy(WIDTH/2,HIGH - 45,"WAIT PLEASE");
	if(judge(lords) == 1){
		cleardevice();
		setfillstyle(SOLID_FILL,BGCOLOR);
		bar(0,0,WIDTH,HIGH);
		outtextxy(WIDTH/2,HIGH/2,"You win!");
		return 1;
	}
	if(judge(lords) == -1){
		cleardevice();
		setfillstyle(SOLID_FILL,BGCOLOR);
		bar(0,0,WIDTH,HIGH);
		outtextxy(WIDTH/2,HIGH/2,"How unfortunate!");
		return -1;
	}
	rank(lords);
	update(lords,PLAYER);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int status_check(int *x,int *y,struct Lords *pl,int player){
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
	char s[50];
	
	while(1){
		
		for(; is_run(); delay_jfps(120))
		{
			if(kbhit() && ((keyboardmsg = getch()))  ){
				if(keyboardmsg == 'm' || keyboardmsg == 'M'){
					fflush(stdin);
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
					if(next_round(lords)){
						return 0;
					}
					continue;
				}
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
				
				setfillstyle(SOLID_FILL,0x90CAF9);
				bar(msg_x,msg_y,msg_x+GAPI,msg_y+GAPJ);
				
				if(flag){
					setfillstyle(SOLID_FILL,EGERGB(0x9E, 0x9E, 0x9E));
					bar(omsg_x,omsg_y,omsg_x+GAPI,omsg_y+GAPJ);
				}
				
				omsg_x = msg_x;
				omsg_y = msg_y;
				flag = 1;
			}
			else if(flag && (pos_status == -1 || pos_status == 1)){
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
		relative_x = (real_x - 10)/GAPI;
		relative_y = (real_y - 50)/GAPJ;
		translate_to_real_position(&real_x,&real_y);
		translate_to_real_position(&old_x,&old_y);
		
		
		if(pos_status == 1){
			setfillstyle(SOLID_FILL,EGERGB(0x21, 0x96, 0xF3));
			bar(old_x,old_y,old_x+GAPI,old_y+GAPI);
			setfillstyle(SOLID_FILL,SELECTED);
			bar(real_x,real_y,real_x+GAPI,real_y+GAPI);
			
			sel = relative_x + relative_y*100 + 1;
			sprintf(s, "%d",map[relative_x][relative_y].force);
			outtextxy((2 * relative_x+GAPI)/2,(2 * relative_y + GAPJ)/2,s);
			mousecheck_inpos(relative_x,relative_y,pl,player);
			
			//setfillstyle(SOLID_FILL,BGCOLOR);
			//bar(0,HIGH - 45,WIDTH,HIGH - 25);
			//outtextxy(WIDTH/2,HIGH - 45,"Press Enter to End this Round. Press M to read the manul.");
			sel =  0;
			continue;
		}
		
	}	
	
}
