#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include<windows.h> 

using namespace std;

#define ABSNULL (1<<31)

struct list
{
	int data;
	list *next;
};

list *ListCreate()
{
	list *p = new list;
	p->data = ABSNULL;
	p->next = NULL;
	return p;
}

bool ListAdd_A(list *p, int data, int k)
{
	for(int i = 0; i < k; i++)
	{
		if(!p) return 0;
		p = p->next;
	}
	list *newlist = new list;
	newlist->data = data;
	newlist->next = p->next;
	p->next = newlist;
	return 1;
}

bool ListRemove_B(list *p, int k)
{
	for(int i = 0; i < k-1; i++)
	{
		if(!p) return 0;
		p = p->next;
	}
	if(!p) return 0;
	list *cur = p->next;
	p->next = p->next->next;
	delete cur;
	return 1;
}

int ListCount(list *p)
{
	int i = 0;
	p = p->next;
	while(p) 
	{
		i++;
		p = p->next;
	}
	return i;
}

void ListPrint(list *p)
{
	list *p_2 = p->next;
	int i = 1;
	cout<<"Number\t";
	while(p_2)
	{
		p_2 = p_2->next;
		cout<<i<<"\t";
		i++;
	}
	p = p->next;
	cout<<endl<<"List:\t";
	while(p)
	{
		cout<<p->data<<"\t";
		p = p->next;
	}
	cout<<endl;
}

bool ListMove(list *l, int p, int k)
{
	if(p < 1 || k < 1) return 0;
	list 	*l_1,
			*l_2,
			*l_temp;
	for(int i = 0; i <= ((p >= k) ? p : k); i++)
	{
		if(i == p - 1) l_1 = l;
		if(i == k) l_2 = l;
		l = l->next;
		if(!l) return 0;
	}
	l_temp = l_2->next;
	l_2->next = l_1->next;
	l_1->next = l_1->next->next;
	l_2->next->next = l_temp;
	return 1;
}

void ListFix(list *main)
{
	list *p = main, *p_2;
	int ind = 0, j = 0;
	while(p)
	{
		p_2 = p->next;
		j = ind + 1;
		while(p_2)
		{
			if(!p_2) break;
			if(p->data == p_2->data)
			{
				p_2 = p_2->next;
				ListRemove_B(main, j);
				continue;
			}
			p_2 = p_2->next;
			j++;
		}
		p = p->next;
		ind++;
	}
}

struct stack
{
	stack 	*next, 
			*head;
	int data;
};

struct queue
{
	queue	*next,
			*tail;
	int data;
};

queue *QueueCreate(void)
{
	queue *h = new queue;
	h->tail = h;
	h->next = NULL;	
	return h;
}

void *QueueAdd(queue *begin, int data)
{
	queue *p = new queue;
	p->data = data;
	p->next = NULL;
	(begin->tail)->next = p;
	begin->tail = p;
}

void *QueueRemove(queue *begin)
{
	if(begin->next != NULL) 
	{
		queue *s = begin->next;
		begin->next = s->next;		
		if(begin->next == NULL) 
		{
			begin->tail = begin;
		}
		delete s;
	}
}

void *QueueShow(queue *begin)
{
	queue *p = begin->next;
	while(p != NULL)
	{
		cout<<p->data<<"\t";
		p = p->next;
	}	
}

stack *StackCreate(void)
{
	stack *p = new stack;
	p->head = NULL;
	p->next = NULL;
	return p;
}

void StackAdd(stack *begin, int data)
{
	stack *p = new stack;
	p->data = data;
	begin->head = p;
	p->next = begin->next;
	begin->next = p;
}

void StackRemove(stack *begin)
{
	if(begin->head != NULL)
	{
		stack *p = (begin->head)->next;
		delete begin->head;
		begin->next = p;
		begin->head = p;
	}
}

void StackShow(stack *begin)
{
	begin = begin->head;
	while(begin != NULL)
	{
		cout<<begin->data<<"\t";
		begin = begin->next;	
	}	
	printf("\n");
}

enum ConsoleColor 
{ 
	Black = 0, 
	Blue = 1, 
	Green = 2, 
	Cyan = 3, 
	Red = 4, 
	Magenta = 5, 
	Brown = 6, 
	LightGray = 7, 
	DarkGray = 8, 
	LightBlue = 9, 
	LightGreen = 10, 
	LightCyan = 11, 
	LightRed = 12, 
	LightMagenta = 13, 
	Yellow = 14, 
	White = 15 
}; 

void setcolor(ConsoleColor text, ConsoleColor background) 
{ 
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); 
} 

int main()
{
	setcolor(White, Black);
	setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
	list *main = ListCreate();
	int N = 10;
	int A[N];	
	for(int i = 0; i < N; i++)	A[i] = rand() % (i+1);
	ListAdd_A(main, A[0], 0);
	for(int i = 1; i < N; i++)
	{
		ListAdd_A(main, A[i] * A[i], i);	
	}
	cout<<"Исходный список:"<<endl;
	ListPrint(main);
	ListMove(main, 6, 1);
	cout<<endl<<"Перемещение"<<endl;
	ListPrint(main);
	ListFix(main);	
	cout<<"Пофикшеный список:"<<endl;
	ListPrint(main);
	cout<<"Длина списка: "<<ListCount(main)<<endl;
	cout<<"Нажмите любую клавишу для демонстрации стека/очереди: ";
	getch();
	stack *st = StackCreate();
	queue *qu = QueueCreate();
	int var;
	system("CLS");
	while(1)
	{
		cout<<endl<<endl<<"1)Добавить элемент\n2)Удалить элемент"<<endl;
		cin>>var;
		if(var == 1)
		{
			cout<<"Введите целое число: ";
			cin>>var;
			StackAdd(st, var);
			QueueAdd(qu, var);
			
			system("CLS");
			cout<<"Стэк:"<<endl;
			setcolor(LightGreen, Black);
			cout<<"=>\t";
			setcolor(White, Black);
			StackShow(st);
			cout<<"Очередь:"<<endl;
			QueueShow(qu);			
			setcolor(LightGreen, Black);
			cout<<"<=\t";
			setcolor(White, Black);
		}
		else if(var == 2)
		{
			StackRemove(st);
			QueueRemove(qu);

			system("CLS");
			cout<<"Стэк:"<<endl;
			setcolor(LightRed, Black);
			cout<<"=>\t";
			setcolor(White, Black);
			StackShow(st);
			cout<<"Очередь:"<<endl;
			setcolor(LightRed, Black);
			cout<<"=>\t";
			setcolor(White, Black);	
			QueueShow(qu);					
		}
		
	}
	return 1;
}

