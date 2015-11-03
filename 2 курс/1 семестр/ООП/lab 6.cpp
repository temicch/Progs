#include <iostream>
#include <conio.h>

using namespace std;

class tList
{
	private:
		tList *next;
	protected:
		int data;
	public:
		template <class T>
		friend void show(T);		
		tList()
		{
			this->next = NULL;
			this->data = 0;
		}
		virtual void push(int data)
		{
			tList *p = this;
			while(p->next)
			{
				p = p->next;
			}
			tList *newlist = new tList;
			p->next = newlist;
			newlist->data = data;
			newlist->next = NULL;
		}
		virtual void pop()
		{
			tList *p = this;
			while(p->next->next)
			{
				p = p->next;
			}
			delete p->next;
			p->next = NULL;
		}
};

class tStack: public tList
{
	private:
		tStack *next, *head;
	public:
		template <class T>
		friend void show(T);		
		tStack()
		{
			this->next = NULL;
			this->head = NULL;
			this->data;
		}
		void push(int data)
		{
			tStack *p = new tStack;
			p->data = data;
			head = p;
			p->next = next;
			next = p;
		}
		void pop()
		{
			if(head != NULL)
			{
				tStack *p = head->next;
				delete head;
				next = p;
				head = p;
			}
		}
};

class tQueue: public tList
{
	private:
		tQueue *next, *tail;
	public:
		template <class T>
		friend void show(T);		
		tQueue()
		{
			this->next = NULL;
			this->tail = this;
		}
		void push(int data)
		{
			tQueue *newqueue = new tQueue;
			newqueue->data = data;
			newqueue->next = NULL;
			this->tail->next = newqueue;
			this->tail = newqueue;
		}
		void pop()
		{
            try
            {
    			if(!this->next) throw 0;
    			tQueue *p = this->next->next;
    			delete this->next;
    			this->next = p;
            }
            catch(int h)
            {
                cout<<"Очередь пуста"<<endl;
            }
		}
};

template <class T>
void show(T object)
{
	T *p = (&(object))->next;
	while(p)
	{
		cout<<p->data<<"\t";
		p = p->next;
	}	
	cout<<endl;
}

int main()
{
	tStack stack;
	tList list;
	tQueue queue;
	for(int i = 0; i < 6; i++)	
	{
		stack.push(i);
		queue.push(i);
		list.push(i);
	}
	cout<<"Обычный список:"<<endl;
	show(list);
	cout<<"Стек:"<<endl;
	show(stack);
	cout<<"Очередь:"<<endl;
	show(queue);
	for(int i = 0; i <= 6; i++)   queue.pop();
	getch();
}
