#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include "tPoint7.h"

using namespace std;

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
    setlocale(0, "");
    int N;
    cout<<"Введите количество объектов каждого типа: ";
    cin>>N;
    tPoint *main[N*7];
	for(int i = 0; i < N*7; i++)
    {
        if(i % 7 == 0) main[i] = new tPoint();
    	if(i % 7 == 1) main[i] = new tLine(); 
    	if(i % 7 == 2) main[i] = new tTriangle();
    	if(i % 7 == 3) main[i] = new tRhomb();
    	if(i % 7 == 4) main[i] = new tRectangle();
    	if(i % 7 == 5) main[i] = new tEllipse(rand()%60);
    	if(i % 7 == 6) main[i] = new tCircle(); 
    }
	initwindow(window_x, window_y);
	while(1)
	{
		for(int j = 0; j < 7 * N; j++)
    		{
    			main[j]->Move();
            }
	}
}
