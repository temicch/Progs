#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

const int window_x = 500, window_y = 500;

#include "tPoint.h"

using namespace std;



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
    	x_speed = -4 + rand() % 9;
    	y_speed = -4 + rand() % 9;
	}
}

void tPoint::SetSpeed(int X_speed, int Y_speed)
{
	x_speed = X_speed;
	y_speed = Y_speed;
}

void tPoint::Move(void)
{
	if(x + x_speed >= window_x) x_speed *= -1;
	if(x + x_speed <= 0) x_speed *= -1;
	if(y + y_speed >= window_y) y_speed *= -1;
	if(y + y_speed <= 0) y_speed *= -1;
	setfillstyle(1, 0);
	setcolor(0);
	fillellipse(x, y, 5, 5);
	x += x_speed;
	y += y_speed;
	setfillstyle(1, color);
	fillellipse(x, y, 5, 5);
}

void tPoint::SetXY(int X, int Y)
{
	x = X;
	y = Y;
}

int tPoint::GetSpeedX(void)	{return x_speed;}
int tPoint::GetSpeedY(void)	{return y_speed;}
int tPoint::GetX(void)	{return x;}
int tPoint::GetY(void)	{return y;}

const int N = 100;

int main()
{
	tPoint *point;
	point = new tPoint[N]; 
	initwindow(window_x, window_y);
	for(int i = 0; i < N; i++)
	{
		point[i].SetXY(rand() % window_x, rand() % window_y);
	}
	while(1)
	{
		for(int i = 0; i < N; i++)
			point[i].Move();
	}
}
