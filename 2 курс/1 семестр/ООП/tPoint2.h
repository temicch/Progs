class tPoint
{
	protected:
		int x, y, x_speed, y_speed, color, movement;
	public:
		tPoint(void);
		~tPoint(void);
		void SetSpeed(int X_speed, int Y_speed);
		void SetXY(int X, int Y);
		void Move(void);
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
		tLine(void);   
        virtual 
        void Draw(int color); 
        void Move(void); 
};

class tTriangle: public tLine
{
    private:
        int radius;
    public:
		tTriangle(void);
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
