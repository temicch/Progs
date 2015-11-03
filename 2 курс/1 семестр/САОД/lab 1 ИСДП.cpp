#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

using namespace std;

struct tree
{
	int data;
	tree *Left;
	tree *Right;
};

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void QuickSort(int *a, int L, int R);
void CreateIdealTree(tree *&A, int *mas2, int n);
tree *ISDP(int L, int R, int *mas);
void PrintTree(tree * p, int level);
void LeftToRight(tree *p);
int SizeTree(tree *p);
int HighTree(tree *p);
int SumTree(tree *p);
double SHighTree(tree *p);
int SPD(tree *p, int L);

char buffer[256];

void TreeP(tree *p, int left, int right, int level);

const int mnoz = 85;

void TreePaint(tree *p)
{
	int window_x = 960, window_y = 640;
	initwindow(window_x, window_y);
    TreeP(p, 0, window_x, 0);
}

void TreeP(tree *p, int left, int right, int level = 0)
{
    if(!p) return;
	sprintf(buffer, "%d", p->data);
	settextjustify(1, 2);
	setcolor(0);
	setbkcolor(15);
	fillellipse((left + right) / 2, 10+level * mnoz, 15, 15);
	setcolor(15);
	if(p->Left)		line((left + right) / 2, level * mnoz, ( left + (left + right) / 2) / 2, (level + 1) * mnoz);
	if(p->Right)	line((left + right) / 2, level * mnoz, ( right + (left + right) / 2) / 2, (level + 1) * mnoz);
	setcolor(0);
	outtextxy((left + right) / 2, level * mnoz, buffer); 
	TreeP(p->Left, left, (left + right) / 2, level + 1);
	TreeP(p->Right, (left + right) / 2, right, level + 1);
}

const int N = 50;

int main()
{
	int A[N];
	tree *MainTree;
	
	

	
	
	A[0] = 14;
	A[1] = 1;
	A[2] = 12;
	A[3] = 19;
	A[4] = 10;
	A[5] = 14;
	A[6] = 16;
	A[7] = 3;
	A[8] = 1;
	A[9] = 18;
	A[10] = 20;
	A[11] = 6;
	A[12] = 14;
	A[13] = 19;
	A[14] = 6;
	A[15] = 18;
	A[16] = 4;
	A[17] = 6;
	A[18] = 6;
	A[19] = 3;
	A[20] = 10;
	A[21] = 25;
	
	//for(int i = 0; i < N; i++)	A[i] = rand() %  160;
	CreateIdealTree(MainTree, A, 22);
	cout<<"Obxod:"<<endl;
	LeftToRight(MainTree);
	cout<<endl<<"Size: "<<SizeTree(MainTree)<<endl<<"High: "<<HighTree(MainTree)<<endl<<"Sum: "<<SumTree(MainTree)<<endl<<"Sred High: "<<SHighTree(MainTree)<<endl<<"Tree:"<<endl;
	TreePaint(MainTree);
	cout<<21/2;
	getch();
}

void LeftToRight(tree *p)
{
	if(!p) return;
	LeftToRight(p->Left);
	cout<<p->data<<" ";
	LeftToRight(p->Right);
}

int SizeTree(tree *p)
{
	if(!p) return 0;
	return 1 + SizeTree(p->Left) + SizeTree(p->Right);
}

int HighTree(tree *p)
{
	if(!p) return 0;
	return 1 + max(HighTree(p->Left), HighTree(p->Right));
}

int SumTree(tree *p)
{
	if(!p) return 0;
	return 1 + p->data + SumTree(p->Left) + SumTree(p->Right);
}

double SHighTree(tree *p)
{
	return (double)SPD(p, 1)/SizeTree(p);
}

int SPD(tree *p, int L)
{
	if(!p) return 0;
	return L + SPD(p->Left, L + 1) + SPD(p->Right, L + 1);
}

void QuickSort(int *a, int L, int R)
{
	int x= a[(L+R)/2];
	int i = L;
	int j = R;
	do
	{
		while(a[i] < x) i++;
		while(a[j] > x) j--;
		if(i<=j) 
		{
			swap(a[i],a[j]); 
			i++; 
			j--; 
		}	
	}while(i<=j);
	if(L<j) QuickSort(a, L, j);
	if(R>i) QuickSort(a, i, R);
}

void CreateIdealTree(tree *&A, int *mas2, int n)
{
	int mas[n];
	for(int i = 0; i < n; i++) mas[i] = mas2[i];
	QuickSort(mas, 0, n - 1);
	A = ISDP(0, n - 1, mas);
}

tree *ISDP(int L, int R, int *mas)
{
	int m;
	if(L > R) return NULL;
	else m = (L+R)/2;
	tree *x = new tree;
	x->data = mas[m];
	x->Left = ISDP(L, m - 1, mas);
	x->Right = ISDP(m + 1, R, mas);
	return x;
}
