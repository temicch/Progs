#include <iostream>
#include <stdlib.h>

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

struct ABL
{
	ABL*left, *right;
	int data, bal;
};


void ABL_LL(ABL *&p)
{
	ABL *q = p->left;
	p->bal = 0;
	q->bal = 0;
	p->left = q->right;
	q->right = p;
	p = q;
}

void ABL_RR(ABL *&p)
{
	ABL *q = p->right;
	p->bal = 0;
	q->bal = 0;
	p->right = q->left;
	q->left = p;
	p = q;
}

void ABL_LR(ABL *&p)
{
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
				//Rost = true;
			}
			else
			{
				if(p->left->bal < 0)
				{
					ABL_LL(p);
					//Rost = false;
				}
				else 
				{
					ABL_LR(p);
					Rost = false;
				}
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
				//Rost = true;
			}
			else
			{
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
	for(int i = 0; i < 200; i++) ABL_Add(root, rand() % 2000);
	LeftToRight(root);
}
