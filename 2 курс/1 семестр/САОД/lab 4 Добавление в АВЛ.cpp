#include <iostream>
#include <stdlib.h>
#include <graphics.h>

int main_window = -1;

char buffer[256];

const int mnoz = 40;

struct ABL
{
	ABL *left, *right;
	int data, bal;
};

void TreeP(ABL *p, int left, int right, int level = 0)
{
    if(!p) return;
	sprintf(buffer, "%d", p->data);
	settextjustify(1, 2);
	setcolor(0);
	setbkcolor(15);
	fillellipse((left + right) / 2, 10+level * mnoz, 15, 15);
	setcolor(15);
	if(p->left)		line((left + right) / 2, level * mnoz, ( left + (left + right) / 2) / 2, (level + 1) * mnoz);
	if(p->right)	line((left + right) / 2, level * mnoz, ( right + (left + right) / 2) / 2, (level + 1) * mnoz);
	setcolor(0);
	outtextxy((left + right) / 2, level * mnoz, buffer); 
	TreeP(p->left, left, (left + right) / 2, level + 1);
	TreeP(p->right, (left + right) / 2, right, level + 1);
}

void TreePaint(ABL *p)
{
	double window_x = getmaxwidth() / 2, window_y = getmaxheight() * 0.75;
	if(main_window == -1) main_window = initwindow(window_x, window_y, "Test", getcurrentwindow() * window_x / ( -3 ));
	setcolor(0);
	setfillstyle(1, 0);
	bar(0, 0, getmaxwidth(), getmaxheight());
	setcolor(15);
	setfillstyle(1, 15);
    TreeP(p, 0, window_x, 0);
}

using namespace std;

bool Rost = false;

template <class tree>
void LeftToRight(tree *p)
{
	if(!p) return;
	LeftToRight(p->left);
	cout<<p->data<<" ";
	LeftToRight(p->right);
}


void ABL_LL(ABL *&p)
{
    cout<<"LL POVOROT"<<endl;
	ABL *q = p->left;
	p->bal = 0;
	q->bal = 0;
	p->left = q->right;
	q->right = p;
	p = q;
}

void ABL_RR(ABL *&p)
{
    cout<<"RR POVOROT"<<endl;
	ABL *q = p->right;
	p->bal = 0;
	q->bal = 0;
	p->right = q->left;
	q->left = p;
	p = q;
}

void ABL_LR(ABL *&p)
{
    cout<<"LR POVOROT"<<endl;
	ABL *q = p->left,
		*r = q->right;
	if(r->bal < 0)
		p->bal = 1;
	else
		p->bal = 0;
	if(r->bal > 0)
		q->bal = -1;
	else q->bal = 0;
	r->bal = 0;
	p->left = r->right;
	q->right = r->left;
	r->left = q;
	r->right = p;
	p = r;
}

void ABL_RL(ABL *&p)
{
    cout<<"RL POVOROT"<<endl;
	ABL *q = p->right,
		*r = q->left;
	if(r->bal > 0)
		p->bal = -1;
	else
		p->bal = 0;
	if(r->bal < 0)
		q->bal = 1;
	else q->bal = 0;
	r->bal = 0;
	p->right = r->left;
	q->left = r->right;
	r->left = p;
	r->right = q;
	p = r;
}

void ABL_Add(ABL *&p, int data)
{
	if(!p)
	{
		p = new ABL;
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		p->bal = 0;
		Rost = true;
		return;
	}
	else if(p->data > data)
	{
		ABL_Add(p->left, data);
		if(Rost)
		{
			if(p->bal > 0)
			{
				p->bal = 0;
				Rost = false;
			}
			else if(p->bal == 0)
			{
				p->bal = -1;
				Rost = true;
			}
			else
			if(p->left->bal < 0)
			{
				ABL_LL(p);
				Rost = false;
			}
			else 
			{
				ABL_LR(p);
				Rost = false;
			}
		}
	}
	else if(p->data < data)
	{
		ABL_Add(p->right, data);
		if(Rost)
		{
			if(p->bal < 0)
			{
				p->bal = 0;
				Rost = false;
			}
			else if(p->bal == 0)
			{
				p->bal = 1;
				Rost = true;
			}
			else
			if(p->right->bal > 0)
			{
				ABL_RR(p);
				Rost = false;
			}
			else
			{
				ABL_RL(p);
				Rost = false;
			}
		}
	}
	else 
	{
		Rost = false;
		return;
	}
}

int main()
{
	ABL *root = NULL;
	int mas[] = {14,1,12,19,10,16,3,18,20,6,4,25};
	for(int i = 0; i < 12; i++)
	{
        ABL_Add(root, mas[i]);
    	TreePaint(root);
        //getch();
    }
	//for(int i = 0; i < 20; i++) ABL_Add(root, i);
	LeftToRight(root);
	getch();
}
