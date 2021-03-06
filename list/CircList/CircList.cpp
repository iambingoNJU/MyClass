#ifndef __CIRCLIST_CPP__
#define __CIRCLIST_CPP__

#include <iostream>
using namespace std;

#include <assert.h>

template <class T>
struct CircNode {
	T data;
	CircNode<T> *next;
	CircNode(CircNode<T> *ptr=NULL) { next=ptr; }
	CircNode(T item,CircNode<T> *ptr=NULL) { data=item; next=ptr; }
};

template <class T>
class CircList
{
protected:
	CircNode<T> *head;
public:
	CircList() { head=NULL; }
	CircList(CircList<T> &L);
	~CircList() { clear(); }
	void clear();
	int lenth();
	bool isEmpty() { return head==NULL; }
	CircNode<T>* getHead() { return head; }
	CircNode<T>* locate(int i);
	CircNode<T>* search(T x);
	bool getData(int i,T &x);
	bool setData(int i,T x);
	bool insert(int i,T x);
	bool remove(int i,T &x);
	void input(T endFlag,int type);
	void output();
	CircList<T>& operator=(CircList<T>& L);
};


template <class T>
CircList<T>::CircList(CircList<T>& L)
{
	if(!L.isEmpty())
	{
		CircNode<T> *lhead=L.getHead();
		T temp;
		L.getData(0,temp);
		head=new CircNode<T>(temp);
		CircNode<T> *srcptr=lhead->next, *tail=head;
		if(srcptr->next!=lhead)
		{
			while(srcptr->next!=lhead)
			{
				temp=srcptr->data;
				tail->next=new CircNode<T>(temp);
				tail=tail->next;
				srcptr=srcptr->next;
			}
			temp=srcptr->data;
			tail->next=new CircNode<T>(temp);
			tail=tail->next;
		}
		tail->next=head;
	}
}

template <class T>
CircList<T>& CircList<T>::operator=(CircList<T>& L)
{
	if(!L.isEmpty())
	{
		CircNode<T> *lhead=L.getHead();
		T temp;
		L.getData(0,temp);
		head=new CircNode<T>(temp);
		CircNode<T> *srcptr=lhead->next, *tail=head;
		if(srcptr->next!=lhead)
		{
			while(srcptr->next!=lhead)
			{
				temp=srcptr->data;
				tail->next=new CircNode<T>(temp);
				tail=tail->next;
				srcptr=srcptr->next;
			}
			temp=srcptr->data;
			tail->next=new CircNode<T>(temp);
			tail=tail->next;
		}
		tail->next=head;
	}
	return *this;
}

template <class T>
void CircList<T>::clear()
{
	if(head==NULL) return;
	CircNode<T> *temp,*originHead=head;
	while(head->next!=originHead)
	{
		temp=head;
		head=head->next;
		delete temp;
	}
	delete head;
	head=NULL;
}

template <class T>
int CircList<T>::lenth()
{
	if(head==NULL) return 0;
	int cnt=0;
	CircNode<T> *temp=head;
	while(temp->next!=head)
	{
		cnt++;
		temp=temp->next;
	}
	return cnt+1;
}

template <class T>
CircNode<T>* CircList<T>::locate(int i)
{
	if(i<0 || i>=lenth()) return NULL;
	CircNode<T> *temp=head;
	while(i>0)
	{
		temp=temp->next;
		i--;
	}
	return temp;
}

template <class T>
void CircList<T>::input(T endFlag,int type)
{
	if(type==0)
	{
		cout<<"Current list:"<<endl;
		output();
		cout<<"Please enter list elements(END with "<<endFlag<<"):"<<endl;
		T temp;
		CircNode<T> *newNode;
		while((cin>>temp)&&(temp!=endFlag))
		{
			newNode=new CircNode<T>(temp);
			assert(newNode!=NULL);
			newNode->next=head;
			head=newNode;
		}
		CircNode<T> *tail=locate(lenth()-1);
		tail->next=head;

	}
	else if(type==1)
	{
		cout<<"Current list:"<<endl;
		output();
		cout<<"Please enter list elements(END with "<<endFlag<<"):"<<endl;
		T temp;
		CircNode<T> *newNode,*tail=locate(lenth()-1);
		while((cin>>temp)&&(temp!=endFlag))	
		{
			newNode=new CircNode<T>(temp);
			assert(newNode!=NULL);
			if(tail==NULL)
			{
				tail=newNode;
				head=tail;
			}
			else
			{
				tail->next=newNode;
				tail=newNode;
			}
		}
		tail->next=head;
	}
	else
		cout<<"You give 'input' a wrong arguments. It should be 0 or 1."<<endl; 
}

template <class T>
void CircList<T>::output()
{
	if(head==NULL)
	{
		cout<<"NULL List!"<<endl;
		return;
	}
	CircNode<T> *temp=head;
	cout<<"List elements: "<<"("<<lenth()<<")[ ";
	while(temp->next!=head)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<temp->data<<" ";
	cout<<"]"<<endl;
}

template <class T>
CircNode<T>* CircList<T>::search(T x)
{
	if(head==NULL) return NULL;
	CircNode<T> *temp=head;
	while(temp->next!=head)
	{
		if(temp->data==x)
			break;
		temp=temp->next;
	}
	if(temp->data==x)
		return temp;
	else
		return NULL;
}

template <class T>
bool CircList<T>::getData(int i,T& x)
{
	CircNode<T> *temp=locate(i);
	if(temp==NULL)
		return false;
	x=temp->data;
	return true;
}

template <class T>
bool CircList<T>::setData(int i,T x)
{
	CircNode<T> *temp=locate(i);
	if(temp==NULL)
		return false;
	temp->data=x;
	return true;
}

template <class T>
bool CircList<T>::insert(int i,T x)
{
	if(i==-1)
	{
		CircNode<T> *newNode=new CircNode<T>(x), *tail=locate(lenth()-1);
		newNode->next=head;
		head=newNode;
		if(tail!=NULL)
			tail->next=head;
		else
			head->next=head;
		return true;
	}
	CircNode<T> *temp=locate(i);
	if(temp==NULL)
		return false;
	CircNode<T> *newNode=new CircNode<T>(x);
	newNode->next=temp->next;
	temp->next=newNode;
	return true;
}

template <class T>
bool CircList<T>::remove(int i,T& x)
{
	CircNode<T> *temp=locate(i),*pre=locate(i-1);
	if(temp==NULL)
		return false;

	x=temp->data;
	if(pre==NULL)
	{
		CircNode<T> *tail=locate(lenth()-1);
		head=head->next;
		tail->next=head;
	}
	else
		pre->next=temp->next;
	delete temp;
	return true;
}


#endif
