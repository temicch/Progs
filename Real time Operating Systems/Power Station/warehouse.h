class warehouse
{
    int value, X, Y, rects[10], color;
    public:
        warehouse(int x, int y, int val, int lColor)
        {
            color = lColor;
            SetColor(RGB(0, 200, 0));
            for(int i = 0; i < 10; i++)
            {
                rects[i] = Rect(x, y + 18 * i, 80, 15);
                Hide(rects[i]);
                Fill(rects[i], color);
            }
            X = x;
            Y = y;
            value = val;
            ReDraw();
            SetColor(color);
            Line(x - 10, y - 3, x + 80 + 10, y - 3);
            SetColor(RGB(0, 0, 0));
        }
        void ReDraw()
        {
            for(int i = 0; i < value; i++)
            {
                Show(rects[i]);
            }
            for(int i = value; i < 10; i++)
            {
                Hide(rects[i]);
            }
        }
        void Add()
        {
            value++;
            if(value > 10)
                value = 10;
            ReDraw();
        }
        void Remove()
        {
            value--;
            if(value < 0)
                value = 0;
            ReDraw();
        }
        bool isEmpty()
        {
            if(!value)
                return true;
            return false;
        }
        bool isFull()
        {
            if(value == 10)
                return true;
            return false;
        }
        int getX()
        {
            return X;
        }
        int getValue()
        {
            return value;
        }
};