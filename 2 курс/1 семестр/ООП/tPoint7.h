#include <stdio.h>

int poly[32];

#define PI 3.14159265358979323846 

double DegToRad(double x)
{
    while(x >= 360) x -= 360;       
    return x * (3.14159265358979323846 / 180);
}

const int window_x = 1980, window_y = 1020;

class tPoint
{
	protected:
		int x, y, x_speed, y_speed, color, movement;
	public:
		tPoint(void);
		~tPoint(void);
		void SetSpeed(int X_speed, int Y_speed);
		void SetXY(int X, int Y);
		virtual 
        void Move(void);
        virtual 
        void Draw(int color); 
		int GetSpeedX(void);
		int GetSpeedY(void);
		int GetX(void);
		int GetY(void);
};

class tLine: public tPoint
{
    protected:
        int angle, angle_speed, radius;
    public:
		tLine(void);// : tPoint(void);   
        //virtual 
        void Draw(int color); 
        //virtual 
        void Move(void); 
};

class tTriangle: public tLine
{
    private:
        int radius;
    public:
        tTriangle(void)
        {
            radius = 20;
        	x = rand() % window_x;
        	y = rand() % window_y;
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
            //printf("Вызван треугольник\n");
        }
        void Draw(int color); 
        //void Move(void); 
};

class tRhomb: public tLine
{
    private:
        int radius;
    public:
		tRhomb(void);
        void Draw(int color); 
        //void Move(void); 
};

class tRectangle: public tLine
{
    private:
        int radius;
    public:
		tRectangle(void);
        void Draw(int color); 
        //void Move(void); 
};

class tEllipse: public tLine
{
    private:
        int radius;
    public:
		tEllipse(void);
		tEllipse(int radius1);
        void Draw(int color); 
        //void Move(void); 
};

class tCircle: public tLine
{
    private:
        int radius;
    public:
		tCircle(void);
        void Draw(int color); 
        //void Move(void); 
};

tPoint::tPoint(void)
{
	x = rand() % window_x;
	y = rand() % window_y;
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
    //cout<<"Вызов из точки"<<endl;
	setfillstyle(1, color);
	setcolor(color);
	fillellipse(x, y, 5, 5);     
}

void tPoint::Move(void)
{
    //cout<<"Вызов из точки"<<endl;
	Draw(0);
	if(x + x_speed >= window_x) x_speed *= -1;
	if(x + x_speed <= 0) x_speed *= -1;
	if(y + y_speed >= window_y) y_speed *= -1;
	if(y + y_speed <= 0) y_speed *= -1;

	x += x_speed;
	y += y_speed;
	Draw(color);
}

tLine::tLine(void);//:tPoint(void)
{
    radius = 20;
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
    //cout<<"Вызов из линии"<<endl;
    //cout<<"Rad: "<<radius<<endl;
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
    //cout<<"Вызов из линии"<<endl;
	Draw(0);
	x += x_speed;
	y += y_speed;
	angle += angle_speed;
	Draw(color);
}

void tTriangle::Draw(int color)
{
    //cout<<"Вызов из треугольника"<<endl;
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

tRhomb::tRhomb(void)
{
    radius = 20;
	x = rand() % window_x;
	y = rand() % window_y;
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
    //cout<<"Вызов из ромба"<<endl;
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

tRectangle::tRectangle(void)
{
    radius = 20;
	x = rand() % window_x;
	y = rand() % window_y;
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
    //cout<<"Вызов из прямоугольника"<<endl;
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

tEllipse::tEllipse(void)
{
    radius = 20;
	x = rand() % window_x;
	y = rand() % window_y;
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

tEllipse::tEllipse(int radius1)
{
    radius = radius1;
	x = rand() % window_x;
	y = rand() % window_y;
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
    //cout<<"Вызов из эллипса"<<endl;
    //printf("%d\n",radius);
    int a = radius, b = radius * 0.8;
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
	x = rand() % window_x;
	y = rand() % window_y;
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
    //cout<<"Вызов из круга"<<endl;
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
