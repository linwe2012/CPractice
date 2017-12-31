#include "stdio.h"
#include "func.cpp"
#include<graphics.h>
#define HIGH 640
#define WIDTH 480
#define TER 10

main(){
	initgraph(HIGH, WIDTH);
	setbkcolor(EGERGB(0xE0, 0xE0, 0xE0));
	getch();
	closegraph();
	return 0;
}


