#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <dos.h>

void draw_color_panel();
void draw_shape_panel();
int initmouse();
void showmouseptr();
void hidemouseptr();
void getmousepos(int*,int*,int*);
void ChangeColor(int,int);
char ChangeShape(int,int);

union REGS i,o;

void main()
{
	int gd=DETECT,gm;
	int maxx,maxy;
	int status;
	int button,x,y;
	int key,color;
	int temp1,temp2;
	char ch='f',arr[50];

	initgraph(&gd,&gm,"C:\\turboc3\\bgi");

	maxx=getmaxx();
	maxy=getmaxy();

	draw_color_panel();
	draw_shape_panel();

	outtextxy(530,13,"esc  : EXIT");

	setcolor(BLUE);
	rectangle(0,0,maxx,maxy);

	setcolor(WHITE);

	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);

	rectangle(3,2,521,425);

	setviewport(4,3,520,424,1);

	status=initmouse();

	while(1)
	{
	if(kbhit())
	{
		key=getch();
		if(key==27)
			exit(0);
	}
	if(status==0)
	{
		printf("Driver is not available");
		getch();
		exit(0);
	}
	else
	{
		showmouseptr();

		getmousepos(&button,&x,&y);

		if(button==1)
		{
			//printf("x: %d y: %d",x,y);
			if(x>100 && x<480 && y>435 && y<453)
			{
				ChangeColor(x,y);
			}
			else if(x>530 && x<628 && y>44 && y<280)
			{
				ch=ChangeShape(x,y);
			}

			temp1=x;
			temp2=y;

			if(ch=='f')
			{
				hidemouseptr();
				while(button==1)
				{
					line(temp1,temp2,x,y);
					temp1=x;
					temp2=y;
					getmousepos(&button,&x,&y);
				}
				showmouseptr();
			}

			while(button==1)
				getmousepos(&button,&x,&y);

			hidemouseptr();

			if(ch=='p')
			{
				putpixel(x,y,getcolor());
			}
			else if(ch=='l')
			{
				line(temp1,temp2,x,y);
			}
			else if(ch=='b')
			{
				bar3d(temp1,temp2,x,y,x+0.1,y+0.1);
			}
			else if(ch=='e')
			{
				ellipse(temp1,temp2,0,360,x-temp1,y-temp2);
			}
			else if(ch=='r')
			{
				rectangle(temp1,temp2,x,y);
			}
			else if(ch=='a')
			{
				while(button==1)
				{
					setcolor(RED);
					getmousepos(&button,&x,&y);
					circle(x,y,10);
					floodfill(x+1,y+1,RED);
				}
			}
			else if(ch=='c')
			{
				clearviewport();
				ch='f';
				getcolor();
			}
			showmouseptr();
		}
	}}

	getch();
}

int initmouse()
{
	i.x.ax=0;
	int86(0X33,&i,&o);
	return (o.x.ax);
}

void showmouseptr()
{
	i.x.ax=1;
	int86(0X33,&i,&o);
}

void hidemouseptr()
{
	i.x.ax=2;
	int86(0X33,&i,&o);
}

void getmousepos(int *button,int *x,int *y)
{
	i.x.ax=3;
	int86(0X33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
}

void draw_color_panel()
{
	int clr=0,x=0;
	int color;

	color=getcolor();

	setcolor(GREEN);
	rectangle(4,431,635,457);
	setcolor(RED);
	settextstyle(5,HORIZ_DIR,1);
	outtextxy(6,428,"COLORS:");

	//Displaying Colors
	for(x=0;x<390;x+=26)
	{
		setfillstyle(SOLID_FILL,color);
		bar(100+x,435,116+x,453);        //x=100,480     y=435,453
		color++;
	}
	setcolor(color);
}

void draw_shape_panel()
{
	int y,color;

	color=getcolor();

	setcolor(GREEN);
	rectangle(525,40,633,285);

	for(y=0;y<=210;y+=30)
	{
		rectangle(530,44+y,628,70+y);    //x 530,628  y 44,250
	}
	setcolor(RED);
	settextstyle(2,HORIZ_DIR,6);
	outtextxy(540,47,"BAR");
	outtextxy(540,77,"LINE");
	outtextxy(540,107,"PIXEL");
	outtextxy(540,137,"ELLIPSE");
	outtextxy(540,167,"FREEHAND");
	outtextxy(538,197,"RECTANGLE");
	outtextxy(540,227,"CLEAR");
	outtextxy(540,257,"ERASER");

	setcolor(color);
}

void ChangeColor(int x,int y)
{
	int c;

	for(c=0;c<=364;c+=26)
	{
		if(x>(100+c) && x<(116+c))
		{
			setcolor((c/26)-1);
		}
	}
}

char ChangeShape(int x,int y)
{
	if(x>530 && x<628 && y>44 && y<70)   //x 530,628  y 44,250
		return 'b';
	else if(x>530 && x<628 && y>74 && y<100)
		return 'l';
	else if(x>530 && x<628 && y>104 && y<130)
		return 'p';
	else if(x>530 && x<628 && y>134 && y<160)
		return 'e';
	else if(x>530 && x<628 && y>164 && y<190)
		return 'f';
	else if(x>530 && x<628 && y>194 && y<220)
		return 'r';
	else if(x>530 && x<628 && y>224 && y<250)
		return 'c';
	else if(x>530 && x<628 && y>254 && y<280)
		return 'a';
}