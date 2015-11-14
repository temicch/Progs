#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

using namespace std;

struct ABL
{
	ABL *left, *right;
	int data, bal;
};

bool 	Rost = false,
		D=0;
int main_window = -1;

// Отрисовка - начало
char buffer[256];

void TreeP(ABL *p, int left, int right, int level);

const int mnoz = 90;

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
	int window_x = getmaxwidth() / 2, window_y = getmaxheight() * 0.75;
	if(main_window == -1) main_window = initwindow(window_x, window_y, "Test", getcurrentwindow() * window_x / ( -3 ));
	setcolor(0);
	setfillstyle(1, 0);
	bar(0, 0, getmaxwidth(), getmaxheight());
	setcolor(15);
	setfillstyle(1, 15);
    TreeP(p, 0, window_x, 0);
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

void RR1(ABL *&p)
{
	ABL *q=p->right;
	if (q->bal==0) 
	{
		p->bal=1; 
		q->bal=-1; 
		D=0;
	}
	else
	{
		p->bal=0; 
		q->bal=0;
	}
	p->right=q->left;
	q->left=p;
	p=q;
}

void RL(ABL *&p)
{
	ABL *q = p->right;
	ABL *r=q->left;
	if (r->bal>0) 
		p->bal=-1;
	else 
		p->bal=0;
	if (r->bal<0) 
		q->bal=1;
	else 
		q->bal=0;
	r->bal=0;
	p->right=r->left;
	q->left=r->right;
	r->right=q;
	r->left=p;
	p=r;
}

void LR(ABL *&p)
{
	ABL *q=p->left;
	ABL *r=q->right;
	if (r->bal<0) 
		p->bal=1;
	else 
		p->bal=0;
	if (r->bal>0) 
		q->bal=-1;
	else 
		q->bal=0;
	r->bal=0;
	p->left=r->right;
	q->right=r->left;
	r->left=q;
	r->right=p;
	p=r;
}

void LL1(ABL *&p)
{
	ABL *q=p->left;
	if (q->bal==0) 
	{
		p->bal=-1; 
		q->bal=1; 
		D=0;
	}
	else
	{
		p->bal=0; 
		q->bal=0;
	}
	p->left=q->right;
	q->right=p;
	p=q;
}

void BL (ABL *&p)
{
	ABL *q,*r;
	if (p->bal==-1) 
		p->bal=0;
	else
	if (p->bal==0) 
	{
		p->bal=1; 
		D=0;
	}
	else
	if (p->bal==1)
		if (p->right->bal>=0)
		{
			//RR1
			//puts("\nRR1");
			RR1(p);
		}
		else
		{
			//RL
			//puts("\nRL");
			RL(p);
		}
	return;
}

void BR (ABL *&p)
{
	ABL *q,*r;
	if (p->bal==1) 
		p->bal=0;
	else
	if (p->bal==0) 
	{
		p->bal=-1; 
		D=0;
	}
	else
	if (p->bal == -1)
		if (p->left->bal<=0)
		{
			//LL1
			//puts("\nLL1");
			LL1(p);
		}
		else
		{
			//LR
			//puts("\nLR");
			LR(p);
		}
	return;
}

void DelOne (ABL *&q, ABL *&r)
{
	if (r->right!=NULL)
	{
		DelOne(q,r->right);
		if (D==1) BR(r);
	}
	else
	{
		q->data=r->data;
		q=r;
		r=r->left;
		D=1;
	}
	return;
}

void DelAVL(int x, ABL *&p)
{
	ABL *q;
	if (p==NULL) 
	{
		printf ("\n%d Not found",x); 
		return;
	}
	else
	{
		if (p->data > x)
		{
			DelAVL(x,p->left);
			if (D==1) 
				BL(p);
		}
		else
		if (p->data < x)
		{
			DelAVL (x,p->right);
			if (D==1) 
				BR (p);
		}
		else
		{
			q=p;
			if (q->right==NULL) 
			{
				p=q->left; 
				D=1;
			}
			else
			if (q->left==NULL) 
			{
				p=q->right; 
				D=1;
			}
			else
			{
				DelOne (q,q->left);
				if (D==1) 
					BL(p);
			}
			free (q);
		}
	}
	return;
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

int main()
{
	ABL *root = NULL;
	int N = 10;
	int mas[N], x;
	for(int i = 0; i < N; i++) 
    {
        mas[i] = rand() % 100;
        ABL_Add(root, mas[i]);
    }
	TreePaint(root);
	cout<<"Вводите числа:"<<endl;
	for(int i = 0; i < N; i++) 
    {
        cout<<endl;
        cin>>x;
        DelAVL(x, root);   
        TreePaint(root);
    	LeftToRight(root);
    }
	//cout<<endl<<"n=100\tРазмер\tКонтрольная сумма\tВысота\tСредняя высота\nИСДП\t"<<SizeTree(root)<<"\t"<<SumTree(root)<<"\t\t\t"<<HighTree(root)<<"\t"<<SHighTree(root)<<endl<<"СДП\t"<<SizeTree(root)<<"\t"<<SumTree(root)<<"\t\t\t"<<HighTree(root)<<"\t"<<SHighTree(root);
	getch();
}
