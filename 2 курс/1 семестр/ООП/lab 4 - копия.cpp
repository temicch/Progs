#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include "tPoint2.h"

int poly[32];

#define PI 3.14159265358979323846 

using namespace std;

double DegToRad(double x)
{
    while(x >= 360) x -= 360;       
    return x * (3.14159265358979323846 / 180);
}

const int window_x = 500, window_y = 500;

tPoint::tPoint(void)
{
	x = 0;
	y = 0;
	color = 1 + rand() % 15;
	movement = rand() % 2;
	x_speed = 0;
	y_speed = 0;
	if(!movement)
	{
		if(!(rand() % 2))
		{
			x_speed = -4 + 8 * (rand() % 2);
			y_speed = 0;
		}
		else
		{
			x_speed = 0;
			y_speed = -4 + 8 * (rand() % 2);
		}
	}
	else
	{
    	x_speed = -2 + 4 * (rand() % 2);
    	y_speed = -2 + 4 * (rand() % 2);
	}
}

void tPoint::SetSpeed(int X_speed, int Y_speed)
{
	x_speed = X_speed;
	y_speed = Y_speed;
}

void tPoint::Draw(int color)
{
	setfillstyle(1, color);
	setcolor(color);
	fillellipse(x, y, 5, 5);     
}

void tPoint::Move(void)
{
	Draw(0);
	if(x + x_speed >= window_x) x_speed *= -1;
	if(x + x_speed <= 0) x_speed *= -1;
	if(y + y_speed >= window_y) y_speed *= -1;
	if(y + y_speed <= 0) y_speed *= -1;

	x += x_speed;
	y += y_speed;
	Draw(color);
}

tLine::tLine(void)
{
    radius = 20;
	x = 0;
	y = 0;
	color = 1 + rand() % 15;
	movement = rand() % 2;
	x_speed = 0;
	y_speed = 0;
	angle_speed = 0;
	angle = 0;
	if(!movement)
	{
		if(!(rand() % 2))
		{
			x_speed = -4 + 8 * (rand() % 2);
			y_speed = 0;
		}
		else
		{
			x_speed = 0;
			y_speed = -4 + 8 * (rand() % 2);
		}
	}
	else angle_speed = -1 + 2 * (rand() % 2);
}

void tLine::Draw(int color)
{
    setcolor(color);
    setfillstyle(0, color);
    int x1 = x + cos(DegToRad(angle)) * radius;
    int y1 = y + sin(DegToRad(angle)) * radius;
    int x2 = x + cos(DegToRad(angle + 180)) * radius;
    int y2 = y + sin(DegToRad(angle + 180)) * radius;
    
	if(x1 + x_speed >= window_x || x2 + x_speed >= window_x) x_speed = -abs(x_speed);
	if(x1 + x_speed <= 0 || x2 + x_speed <= 0) x_speed = abs(x_speed);
	if(y1 + y_speed >= window_y || y2 + y_speed >= window_y) y_speed = -abs(y_speed);
	if(y1 + y_speed <= 0 || y2 + y_speed <= 0) y_speed = abs(y_speed);    
    
    line(x1, y1, x2, y2);
}

void tLine::Move()
{
	Draw(0);
	x += x_speed;
	y += y_speed;
	angle += angle_speed;
	Draw(color);
}

tTriangle::tTriangle(void)
{
    radius = 20;
	x = 0;
	y = 0;
	color = 1 + rand() % 15;
	movement = rand() % 2;
	x_speed = 0;
	y_speed = 0;
	angle_speed = 0;
	angle = 0;
	if(!movement)
	{
		if(!(rand() % 2))
		{
			x_speed = -4 + 8 * (rand() % 2);
			y_speed = 0;
		}
		else
		{
			x_speed = 0;
			y_speed = -4 + 8 * (rand() % 2);
		}
	}
	else angle_speed = -1 + 2 * (rand() % 2);
}

void tTriangle::Draw(int color)
{
    setcolor(color);
    setfillstyle(1, color);
    poly[0] = x + cos(DegToRad(angle)) * radius;
    poly[1] = y + sin(DegToRad(angle)) * radius;
    poly[2] = x + cos(DegToRad(angle + 90)) * radius;
    poly[3] = y + sin(DegToRad(angle + 90)) * radius;
    poly[4] = x + cos(DegToRad(angle + 225)) * radius;
    poly[5] = y + sin(DegToRad(angle + 225)) * radius;
    
    fillpoly(3, poly);
    
	if(poly[0] + x_speed >= window_x || poly[2] + x_speed >= window_x || poly[4] + x_speed >= window_x) x_speed = -abs(x_speed);
	if(poly[0] + x_speed <= 0 || poly[2] + x_speed <= 0 || poly[4] + x_speed <= 0) x_speed = abs(x_speed);
	if(poly[1] + y_speed >= window_y || poly[3] + y_speed >= window_y || poly[5] + y_speed >= window_y) y_speed = -abs(y_speed);
	if(poly[1] + y_speed <= 0 || poly[3] + y_speed <= 0 || poly[5] + y_speed <= 0) y_speed = abs(y_speed);    
}
/*
void tTriangle::Move()
{
	Draw(0);
	x += x_speed;
	y += y_speed;
	angle += angle_speed;
	Draw(color);
}
*/
tRhomb::tRhomb(void)
{
    radius = 20;
	x = 0;
	y = 0;
	color = 1 + rand() % 15;
	movement = rand() % 2;
	x_speed = 0;
	y_speed = 0;
	angle_speed = 0;
	angle = 0;
	if(!movement)
	{
		if(!(rand() % 2))
		{
			x_speed = -4 + 8 * (rand() % 2);
			y_speed = 0;
		}
		else
		{
			x_speed = 0;
			y_speed = -4 + 8 * (rand() % 2);
		}
	}
	else angle_speed = -1 + 2 * (rand() % 2);
}

void tRhomb::Draw(int color)
{
    setcolor(color);
    setfillstyle(1, color);
    poly[0] = x + cos(DegToRad(angle)) * radius / 2;
    poly[1] = y + sin(DegToRad(angle)) * radius / 2;
    poly[2] = x + cos(DegToRad(angle + 90)) * radius;
    poly[3] = y + sin(DegToRad(angle + 90)) * radius;
    poly[4] = x + cos(DegToRad(angle + 180)) * radius / 2;
    poly[5] = y + sin(DegToRad(angle + 180)) * radius / 2;
    poly[6] = x + cos(DegToRad(angle + 270)) * radius;
    poly[7] = y + sin(DegToRad(angle + 270)) * radius;
    
    fillpoly(4, poly);
    
	if(poly[0] + x_speed >= window_x || poly[2] + x_speed >= window_x || poly[4] + x_speed >= window_x || poly[6] + x_speed >= window_x) x_speed = -abs(x_speed);
	if(poly[0] + x_speed <= 0        || poly[2] + x_speed <= 0        || poly[4] + x_speed <= 0        || poly[6] + x_speed <= 0)        x_speed = abs(x_speed);
	if(poly[1] + y_speed >= window_y || poly[3] + y_speed >= window_y || poly[5] + y_speed >= window_y || poly[7] + y_speed >= window_y) y_speed = -abs(y_speed);
	if(poly[1] + y_speed <= 0        || poly[3] + y_speed <= 0        || poly[5] + y_speed <= 0        || poly[7] + y_speed <= 0)        y_speed = abs(y_speed);    
}
/*
void tRhomb::Move()
{
	Draw(0);
	x += x_speed;
	y += y_speed;
	angle += angle_speed;
	Draw(color);
}
*/
tRectangle::tRectangle(void)
{
    radius = 20;
	x = 0;
	y = 0;
	color = 1 + rand() % 15;
	movement = rand() % 2;
	x_speed = 0;
	y_speed = 0;
	angle_speed = 0;
	angle = 0;
	if(!movement)
	{
		if(!(rand() % 2))
		{
			x_speed = -4 + 8 * (rand() % 2);
			y_speed = 0;
		}
		else
		{
			x_speed = 0;
			y_speed = -4 + 8 * (rand() % 2);
		}
	}
	else angle_speed = -1 + 2 * (rand() % 2);
}

void tRectangle::Draw(int color)
{
    setcolor(color);
    setfillstyle(1, color);
    poly[0] = x + cos(DegToRad(angle + 30)) * radius;
    poly[1] = y + sin(DegToRad(angle + 30)) * radius;
    poly[2] = x + cos(DegToRad(angle + 150)) * radius;
    poly[3] = y + sin(DegToRad(angle + 150)) * radius;
    poly[4] = x + cos(DegToRad(angle + 210)) * radius;
    poly[5] = y + sin(DegToRad(angle + 210)) * radius;
    poly[6] = x + cos(DegToRad(angle + 330)) * radius;
    poly[7] = y + sin(DegToRad(angle + 330)) * radius;
    
    fillpoly(4, poly);
    
	if(poly[0] + x_speed >= window_x || poly[2] + x_speed >= window_x || poly[4] + x_speed >= window_x || poly[6] + x_speed >= window_x) x_speed = -abs(x_speed);
	if(poly[0] + x_speed <= 0        || poly[2] + x_speed <= 0        || poly[4] + x_speed <= 0        || poly[6] + x_speed <= 0)        x_speed = abs(x_speed);
	if(poly[1] + y_speed >= window_y || poly[3] + y_speed >= window_y || poly[5] + y_speed >= window_y || poly[7] + y_speed >= window_y) y_speed = -abs(y_speed);
	if(poly[1] + y_speed <= 0        || poly[3] + y_speed <= 0        || poly[5] + y_speed <= 0        || poly[7] + y_speed <= 0)        y_speed = abs(y_speed);    
}
/*
void tRectangle::Move()
{
	Draw(0);
	x += x_speed;
	y += y_speed;
	angle += angle_speed;
	Draw(color);
}
*/
tEllipse::tEllipse(void)
{
    radius = 20;
	x = 0;
	y = 0;
	color = 1 + rand() % 15;
	movement = rand() % 2;
	x_speed = 0;
	y_speed = 0;
	angle = 0;
	angle_speed = 0;
	if(!movement)
	{
		if(!(rand() % 2))
		{
			x_speed = -4 + 8 * (rand() % 2);
			y_speed = 0;
		}
		else
		{
			x_speed = 0;
			y_speed = -4 + 8 * (rand() % 2);
		}
	}
	else angle_speed = -1 + 2 * (rand() % 2);
}

void tEllipse::Draw(int color)
{
    int a = 20, b = 30;
    setcolor(color);
    setfillstyle(1, color);
    double plus = 0.4;
    int j = 0;
    for(double i = 0; i < 2 * PI; i += plus)
    {
        poly[j++] = x + ((cos(i) * a)  *cos(DegToRad(angle)) + (sin(i) * b) * sin(DegToRad(angle)));
        poly[j++] = y + (-(cos(i) * a) *sin(DegToRad(angle)) + (sin(i) * b) * cos(DegToRad(angle)));
    }
    fillpoly(j / 2, poly);
    
	for(int i = 0; i < j - 1; i++)
	{
        if(poly[i] + x_speed >= window_x)     x_speed = -abs(x_speed);
        if(poly[i + 1] + y_speed >= window_y) y_speed = -abs(y_speed);
        if(poly[i] + x_speed <= 0)            x_speed = abs(x_speed);
        if(poly[i + 1] + y_speed <= 0)        y_speed = abs(y_speed);
    }
}
/*
void tEllipse::Move()
{
	Draw(0);
	x += x_speed;
	y += y_speed;
	angle += angle_speed;
	Draw(color);
}
*/
tCircle::tCircle(void)
{
    radius = 20;
	x = 0;
	y = 0;
	color = 1 + rand() % 15;
	movement = rand() % 2;
	x_speed = 0;
	y_speed = 0;
	angle = 0;
	angle_speed = 0;
	if(!movement)
	{
		if(!(rand() % 2))
		{
			x_speed = -4 + 8 * (rand() % 2);
			y_speed = 0;
		}
		else
		{
			x_speed = 0;
			y_speed = -4 + 8 * (rand() % 2);
		}
	}
	else angle_speed = -1 + 2 * (rand() % 2);
}

void tCircle::Draw(int color)
{
    setcolor(color);
    setfillstyle(1, color);
    fillellipse(x, y, radius, radius);
	if(x + x_speed >= window_x) x_speed = -fabs(x_speed);
	if(y + y_speed >= window_y) y_speed = -fabs(y_speed);
	if(x + x_speed <= 0)        x_speed = fabs(x_speed);
	if(y + y_speed <= 0)        y_speed = fabs(y_speed);    
}
/*
void tCircle::Move()
{
	Draw(0);
	x += x_speed;
	y += y_speed;
	angle += angle_speed;
	Draw(color);
}
*/
void tPoint::SetXY(int X, int Y)
{
	x = X;
	y = Y;
}

int tPoint::GetSpeedX(void)	{return x_speed;}
int tPoint::GetSpeedY(void)	{return y_speed;}
int tPoint::GetX(void)	{return x;}
int tPoint::GetY(void)	{return y;}

enum ConsoleColor 
{ 
	Black = 0, 
	Blue = 1, 
	Green = 2, 
	Cyan = 3, 
	Red = 4, 
	Magenta = 5, 
	Brown = 6, 
	LightGray = 7, 
	DarkGray = 8, 
	LightBlue = 9, 
	LightGreen = 10, 
	LightCyan = 11, 
	LightRed = 12, 
	LightMagenta = 13, 
	Yellow = 14, 
	White = 15 
}; 

bool points_ind = 1,
     lines_ind = 1,
     triangles_ind = 1,
     rhombs_ind = 1,
     rectangles_ind = 1,
     ellipses_ind = 1,
     circles_ind = 1;
     
void setcolor(ConsoleColor text, ConsoleColor background) 
{ 
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); 
}      
         
void Text()
{
     system("CLS");
     setcolor(White, Black);
     printf("Фигура\tТочка\tОтрезок\tТреугольник\tРомб\tПрямоугольник\tЭллипс\tОкружность\nКлавиша\t");
     if(points_ind) setcolor(LightGreen, Black);
     else setcolor(LightRed, Black);
     cout<<"1\t";
     if(lines_ind) setcolor(LightGreen, Black);
     else setcolor(LightRed, Black);
     cout<<"2\t";
     if(triangles_ind) setcolor(LightGreen, Black);
     else setcolor(LightRed, Black);
     cout<<"3\t\t";
     if(rhombs_ind) setcolor(LightGreen, Black);
     else setcolor(LightRed, Black);
     cout<<"4\t";
     if(rectangles_ind) setcolor(LightGreen, Black);
     else setcolor(LightRed, Black);
     cout<<"5\t\t";
     setcolor(White, Black);
     if(ellipses_ind) setcolor(LightGreen, Black);
     else setcolor(LightRed, Black);
     cout<<"6\t";
     setcolor(White, Black);
     if(circles_ind) setcolor(LightGreen, Black);
     else setcolor(LightRed, Black);
     cout<<"7\n";
     setcolor(White, Black);
     cout<<"Нажимайте клавиши для добавления / удаления фигур"<<endl;
}

int main()
{
    srand(time(NULL));
    //setlocale(0, "");
    
    int N;
    cout<<"Введите количество объектов каждого типа: ";
    cin>>N;

	tPoint *points = new tPoint[N]; 
	tLine *lines = new tLine[N]; 
	tTriangle *triangles = new tTriangle[N]; 
	tRhomb *rhombs = new tRhomb[N]; 
	tRectangle *rectangles = new tRectangle[N]; 
	tEllipse *ellipses = new tEllipse[N]; 
	tCircle *circles = new tCircle[N]; 

	initwindow(window_x, window_y);
	for(int i = 0; i < N; i++)
	{
		points[i].SetXY(rand() % window_x, rand() % window_y);
		lines[i].SetXY(rand() % window_x, rand() % window_y);
		triangles[i].SetXY(rand() % window_x, rand() % window_y);
		rhombs[i].SetXY(rand() % window_x, rand() % window_y);
		rectangles[i].SetXY(rand() % window_x, rand() % window_y);
		ellipses[i].SetXY(rand() % window_x, rand() % window_y);
		circles[i].SetXY(rand() % window_x, rand() % window_y);
	}
	Text();
	while(1)
	{
        if(kbhit())
        {
            switch(getch())
            {
                case 49: points_ind = 1 - points_ind; cleardevice(); break;
                case 50: lines_ind = 1 - lines_ind; cleardevice(); break;
                case 51: triangles_ind = 1 - triangles_ind; cleardevice(); break;
                case 52: rhombs_ind = 1 - rhombs_ind; cleardevice(); break;
                case 53: rectangles_ind = 1 - rectangles_ind; cleardevice(); break;
                case 54: ellipses_ind = 1 - ellipses_ind; cleardevice(); break;
                case 55: circles_ind = 1 - circles_ind; cleardevice(); break;
            }    
            Text();           
        }
        if(points_ind)
    		for(int i = 0; i < N; i++)
    			points[i].Move();
        if(lines_ind)
    		for(int i = 0; i < N; i++)
    			lines[i].Move();
        if(triangles_ind)
    		for(int i = 0; i < N; i++)
    			triangles[i].Move();
        if(rhombs_ind)
    		for(int i = 0; i < N; i++)
    			rhombs[i].Move();
        if(rectangles_ind)
    		for(int i = 0; i < N; i++)
    			rectangles[i].Move();
        if(ellipses_ind)
    		for(int i = 0; i < N; i++)
    			ellipses[i].Move();
        if(circles_ind)
    		for(int i = 0; i < N; i++)
    			circles[i].Move();
        delay(2);
	}
}
