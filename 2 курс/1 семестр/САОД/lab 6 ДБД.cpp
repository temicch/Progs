#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

using namespace std;

struct DBDTree
{
	DBDTree *left, *right;
	int data, bal;
};

struct ABL
{
	ABL *left, *right;
	int data, bal;
};

bool Rost = false;
int main_window = -1;

// Отрисовка - начало
char buffer[256];

void TreeP(DBDTree *p, int left, int right, int level);

const int mnoz = 90;

void TreePaint(DBDTree *p)
{
	int window_x = getmaxwidth() / 2, window_y = getmaxheight() * 0.75;
	if(main_window == -1) main_window = initwindow(window_x, window_y, "Test", getcurrentwindow() * window_x / ( -3 ));
	setcolor(0);
	setfillstyle(1, 0);
	bar(0, 0, getmaxwidth(), getmaxheight());
	setcolor(15);
	setfillstyle(1, 15);
    TreeP(p, 0, window_x, 0);
}

void TreeP(DBDTree *p, int left, int right, int level = 0)
{
    if(!p) return;
	sprintf(buffer, "%d", p->data);
	settextjustify(1, 2);
	setcolor(0);
	setbkcolor(15);
	fillellipse((left + right) / 2, 10+level * mnoz, 15, 15);
	setcolor(15);
	if(p->left)		line((left + right) / 2, level * mnoz, ( left + (left + right) / 2) / 2, (level + 1) * mnoz);
	if(p->bal)
	{
    	line((left + right) / 2, level * mnoz, (left + right)/2 + (right - left)/4, level * mnoz);
    }
    else
	{
    	if(p->right)	line((left + right) / 2, level * mnoz, ( right + (left + right) / 2) / 2, (level + 1) * mnoz);
    }
	setcolor(0);
	outtextxy((left + right) / 2, level * mnoz, buffer); 
	if(p->bal)
	{
		TreeP(p->right, (left + right) / 2, right, level);
		TreeP(p->left, left, (left + right) / 2, level + 1);
	}
	else
	{
		TreeP(p->left, left, (left + right) / 2, level + 1);
		TreeP(p->right, (left + right) / 2, right, level + 1);
	}
}

// Отрисовка - конец

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

template <class tree>
void LeftToRight(tree *p)
{
	if(!p) return;
	LeftToRight(p->left);
	cout<<p->data<<" ";
	LeftToRight(p->right);
}

template <typename T>
int SizeTree(T *p)
{
	if(!p) return 0;
	return 1 + SizeTree(p->left) + SizeTree(p->right);
}

template <typename T>
int HighTree(T *p)
{
	if(!p) return 0;
	return 1 + max(HighTree(p->left), HighTree(p->right));
}

template <typename T>
int SumTree(T *p)
{
	if(!p) return 0;
	return 1 + p->data + SumTree(p->left) + SumTree(p->right);
}

template <typename T>
int SPD(T *p, int L)
{
	if(!p) return 0;
	return L + SPD(p->left, L + 1) + SPD(p->right, L + 1);
}

template <typename T>
double SHighTree(T *p)
{
	return (double)SPD(p, 1)/SizeTree(p);
}

int VR, HR;

void B2Insert(DBDTree *&p, int data)
{
	DBDTree *q;
	if(!p)
	{
		p = new DBDTree;
		p->data = data;
		p->left = p->right = NULL;
		p->bal = 0;
		VR = 1;
	}
	else if(p->data > data)
	{
		B2Insert(p->left, data);
		if(VR == 1)
		{
			if(p->bal == 0)
			{
				q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->bal = 1;
				VR = 0;
				HR = 1;
			}
			else
			{
				p->bal = 0;
				VR = 1;
				HR = 0;
			}
		}
		else
			HR = 0;
	}
	else if(p->data < data)
	{
		B2Insert(p->right, data);
		if(VR)
		{
			p->bal = 1;
			HR = 1;
			VR = 0;
		}
		else if(HR)
		{
			if(p->bal)
			{
				q = p->right;
				p->bal = 0;
				q->bal = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				VR = 1;
				HR = 0;
			}
			else
				HR = 0;
		}
	}
}

int main()
{
	DBDTree *dbd = NULL;
	ABL *abl = NULL;
	//int mas[] = {12, 21,18,1,17,16,3,6,13,15,10,20};
	/*
	for(int i = 0; i < 20; i++)
	{
        int mas = rand() % 300;
		B2Insert(dbd, mas);
		ABL_Add(abl, mas);
	}*/
	int mas[] = {14,16,18,9,3,6,4,13,1,5,10,25};
	for(int i = 0; i < 12; i++)
	{
        B2Insert(dbd, mas[i]);
    	TreePaint(dbd);
        getch();
    }
	cout<<"Обход ДБД:"<<endl;
    LeftToRight(dbd);
	cout<<endl<<"n=100\tРазмер\tКонтрольная сумма\tВысота\tСредняя высота\nАВЛ\t"<<SizeTree(abl)<<"\t"<<SumTree(abl)<<"\t\t\t"<<HighTree(abl)<<"\t"<<SHighTree(abl)<<endl<<"ДБД\t"<<SizeTree(dbd)<<"\t"<<SumTree(dbd)<<"\t\t\t"<<HighTree(dbd)<<"\t"<<SHighTree(dbd);
	TreePaint(dbd);
	getch();
}
