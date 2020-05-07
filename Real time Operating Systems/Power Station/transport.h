int cGreen = RGB(0, 255, 0);
int cLightGreen = RGB(155, 255, 155);
int tCount = 1;

class transport
{
    private:
        int picture, rect, text;
    public:
        int X, Y, startX, value, myNum;
        transport(int x, int y, int tTcount = 0);
        ~transport();
        void show();
        void hide();
        void move(int x, int y);
};