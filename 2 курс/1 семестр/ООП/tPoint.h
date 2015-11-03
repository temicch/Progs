class tPoint
{
	protected:
		int x, y, x_speed, y_speed, color, movement;
	public:
		tPoint(void);
		~tPoint(void);
		void SetSpeed(int X_speed, int Y_speed);
		void SetXY(int X, int Y);
		void Move();
		int GetSpeedX(void);
		int GetSpeedY(void);
		int GetX(void);
		int GetY(void);
};
