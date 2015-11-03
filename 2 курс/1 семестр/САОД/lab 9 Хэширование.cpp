#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define HashNull (1<<31)

using namespace std;

#define clrscr {for(int i = 0; i < 5; i++) cout<<endl;}

struct listHash
{
	int data;
	listHash *next;
};

void CreateHashList(listHash **A, int m, int *B, int n, int &collisions);
bool CreateHashQuad(int *&A, int m, int *B, int n, int &collisions);
bool CreateHashLine(int *&A, int m, int *B, int n, int &collisions);
void ShowHash(int *A, int m);
void ShowHashList(listHash **A, int m);
int SearchHashLine(int *A, int m, int key);
int SearchHashQuad(int *A, int m, int key);
int SearchHashList(listHash **A, int m, int key);
void ClearHashList(listHash **A, int m);

int main()
{
	srand(time(NULL));
    int *HashLine,
		*HashQuad, 
		m = 11, 
		n = 20, 
		mas[n*10],
		collisionsQuad,
		collisionsLine,
		collisionsList,
		ind;
    for(int i = 0; i < (n * 10); i++)
    	mas[i] = 1 + rand() % 1000;
    	//mas[i] = i;
    	
    printf("%10s%10s%20s%20s\n", "Size hash", "Size mas", "Line collisions", "Quad collisions");
    for(int i = 1; i < 10; i++)
    {
	    CreateHashLine(HashLine, i * 5, mas, i * 10, collisionsLine);
	    CreateHashQuad(HashQuad, i * 5, mas, i * 10, collisionsQuad);
    	printf("%10d%10d%15d%17d\n", i * 5, i * 10, collisionsLine, collisionsQuad);
	}
	
    printf("\n\n\n%10s%10s%20s%20s\n", "Size hash", "Size mas", "Line collisions", "Quad collisions");
    int zx;
    for(int i = 1; i < 10; i++)
    {
            switch (i)
            {
                   case 1: zx = 3; break;
                   case 2: zx = 11;break;
                   case 3: zx = 13;break;
                   case 4: zx = 23;break;
                   case 5: zx = 37;break;
                   case 6: zx = 53;break;
                   case 7: zx = 101;break;
                   case 8: zx = 151;break;
                   case 9: zx = 157;break;
            }
	    CreateHashLine(HashLine, zx, mas, i * 10, collisionsLine);
	    CreateHashQuad(HashQuad, zx, mas, i * 10, collisionsQuad);
    	printf("%10d%10d%15d%17d\n", zx, i * 10, collisionsLine, collisionsQuad);
	}
	
    cout<<endl<<endl<<endl<<"Quad Hash:"<<endl;
    if(!CreateHashQuad(HashQuad, m, mas, n, collisionsQuad))	cout<<"Quad Hash overflow"<<endl;
    ShowHash(HashQuad, m);
    cout<<endl<<endl<<"Line Hash:"<<endl;
    if(!CreateHashLine(HashLine, m, mas, n, collisionsLine))	cout<<"Line Hash overflow"<<endl;
    ShowHash(HashLine, m);
    listHash *List[m*5];
    CreateHashList(List, m, mas, n, collisionsList);
    cout<<endl<<endl<<"List Hash:"<<endl;
    ShowHashList(List, m);
    cout<<endl<<endl<<endl<<"Poisk?";
    getch();
    clrscr;
    while(1)
    {
	    system("CLS");  
		cout<<"Massiv:\n"; 	
	    for(int i = 0; i < n; i++)	cout<<mas[i]<<"\t";
	    cout<<endl<<"Quad:"<<endl;
	    ShowHash(HashQuad, m);
	    cout<<endl<<"Line:"<<endl;
	    ShowHash(HashLine, m);
	    cout<<endl<<endl<<"List Hash:"<<endl;
	    ShowHashList(List, m);
	    cout<<"Enter key (Line): ";
	    int key;
	    cin>>key;
	    ind = SearchHashLine(HashLine, m, key);
	    if(ind != -1)	cout<<"Found in "<<ind<<" cell"<<endl;
	    else cout<<"Not found!"<<endl;
	    cout<<"Enter key (Quad): ";
	    cin>>key;
	    ind = SearchHashQuad(HashQuad, m, key);
	    if(ind != -1)	cout<<"Found in "<<ind<<" cell"<<endl;
	    else cout<<"Not found!"<<endl;
	    cout<<"Enter key (List): ";
	    cin>>key;
	    if(SearchHashList(List, m, key) != -1)	cout<<"Found!"<<endl;
	    else cout<<"Not found!"<<endl;
	    getch();
	}
    
}

bool CreateHashQuad(int *&A, int m, int *B, int n, int &collisions)
{
	collisions = 0;
	A = new int[m];
	int h, d;
	for(int i = 0; i < m; i++) A[i] = HashNull;
	for(int i = 0; i < n; i++)
	{
		h = B[i] % m;
		d = 1;
		while(1)
		{
			if(A[h] == B[i])	break;
			if(A[h] == HashNull)
			{
				A[h] = B[i];
				break;
			}
			collisions++;
			if(d >= m)	return 0;
			h += d;
			if(h >= m)	h -= m;
			d += 2;
		}
	}
	return 1;
}

bool CreateHashLine(int *&A, int m, int *B, int n, int &collisions)
{
	collisions = 0;
	A = new int[m];
	int h, h1;
	for(int i = 0; i < m; i++) A[i] = HashNull;
	for(int i = 0; i < n; i++)
	{
		h = B[i] % m;
		h1 = h;
		while(1)
		{
			if(A[h] == B[i])	break;
			if(A[h] == HashNull)
			{
				A[h] = B[i];
				break;
			}
			collisions++;
			h += 1;
			if(h >= m)	h = 0;
			if(h == h1) return 0;
		}
	}
	return 1;
}

void CreateHashList(listHash **A, int m, int *B, int n, int &collisions)
{
	collisions = 0;
	int h;
	listHash *temp;
	for(int i = 0; i < m; i++)
	{
		A[i] = new listHash;
		A[i]->data = HashNull;
		A[i]->next = NULL;
	}
	for(int i = 0; i < n; i++)
	{
		h = B[i] % m;
		temp = A[h];
		while(temp->next != NULL) 
		{
			if(temp->data == B[i])	break;
			temp = temp->next;
			collisions++;
		}
		if(temp->data == B[i])	continue;
		temp->next = new listHash;
		(temp->next)->data = B[i];
		(temp->next)->next = NULL;
	}
}

void ClearHashList(listHash **A, int m)
{
	listHash *temp, *prev;
	for(int i = 0; i < m; i++)
	{
		temp = A[i]->next;
		prev = A[i];
		while(temp)
		{
			delete prev;
			prev = temp;
			temp = temp->next;
		}
	}
}

void ShowHashList(listHash **A, int m)
{
	listHash *temp;
	for(int i = 0; i < m; i++)
	{
		printf("[%d]\t", i);
		temp = A[i]->next;
		while(temp)
		{
			printf("%d%4s", temp->data, "->");
			temp = temp->next;
		}
		cout<<endl;
	}
}

void ShowHash(int *A, int m)
{
	printf("%10s", "HASH");
	for(int i = 0; i < m; i++) printf("%5d", i);
	printf("\n%10s", "Value");
	for(int i = 0; i < m; i++) 
	{
		if(A[i] == HashNull)
		printf("%5s", "");
		else
		printf("%5d", A[i]);
	}
	cout<<endl;
}

int SearchHashLine(int *A, int m, int key)
{
	int h = key % m,
		d = 1;
	while(1)
	{
		if(A[h] == key)	break;
		if(d >= m)	return -1;
		h += d;
		if(h >= m)	h -= m;
		d += 1;
	}
	return h;
}

int SearchHashQuad(int *A, int m, int key)
{
	int h = key % m,
		d = 1;
	while(1)
	{
		if(A[h] == key)	break;
		if(d >= m)	return -1;
		h += d;
		if(h >= m)	h -= m;
		d += 2;
	}
	return h;
}

int SearchHashList(listHash **A, int m, int key)
{
	int h = key % m;
	listHash *temp = A[h];
	while(temp)
	{
		if(temp->data == key) return h;
		temp = temp->next;
	}
	return -1;
}