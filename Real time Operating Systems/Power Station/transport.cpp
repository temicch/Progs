transport::transport(int x, int y, int tTcount = 0)
{
    if (tTcount == 0)
        myNum = tCount++;
    else
        myNum = tTcount;
    X = x;
    startX = X;
    Y = y;
    picture = Picture(x, y);
    rect = Rect(0, 0, 30, 30, 0, RGB(0, 200, 0), picture);
    char count[1];
    count[0] = myNum + 48;
    text = Text(9, 6, count, RGB(255, 255, 255), picture);
    Fill(rect, cGreen);
    Show(picture);
    value = 0;
    hide();
}

transport::~transport()
{
    Delete(picture);
}

void transport::show()
{
    Fill(rect, cGreen);
}

void transport::hide()
{
    Fill(rect, cLightGreen);
}

void transport::move(int x, int y)
{
    X = x;
    Y = y;
    MoveTo(X, Y, picture);
}