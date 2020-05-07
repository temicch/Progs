class warehouse
{
    int value, X, Y, rects[10], color;
    public:
        warehouse(int x, int y, int val, int lColor);
        void ReDraw();
        void Add();
        void Remove();
        bool isEmpty();
        bool isFull();
        int getX();
        int getValue();
};