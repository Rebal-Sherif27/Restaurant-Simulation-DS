#include "LinkedQueue.h"
#include <iostream>		//To use C++ console I/O functionality
using namespace std;	//This statement enables us to use classes and objects in the standard C++ library
						//without prefixing them with "std::"


/*
Function: removeFirstPostitive
	A function the removes the first non-zero items in a queue
	The function stops either because a zero-item is encounted or queue becomes empty
*/
template <typename T>
void removeFirstPostitive(LinkedQueue<T> & Q) 
{
	T x;
	while(Q.peek(x))	//Have a look first before dequeuing it
		if( x <= 0)
			return;
		else
			Q.dequeue(x);
}

//A function that prints queue contents
template <typename T>
void PrintQueue(LinkedQueue<T> Q) 
{
	T K;
	cout<<"\nQueue contents: ";
	while(Q.dequeue(K))
		cout << K << " ";
	cout<<endl;
}

//A function that prints queue contents
template <typename T>
bool ReplaceAll(LinkedQueue<T> & Source, T value, T newValue)	//Soruce is passe by ref
{
	LinkedQueue<T> tempQ;	//a temp queue is needed
	T x;
	bool found = false;
	while (Source.dequeue(x))
	{
		if (x == value)		//repalce the value if found
		{
			tempQ.enqueue(newValue);
			found = true;
		}
		else
			tempQ.enqueue(x);
	}

	//After the above loop, stack "Source" is empty
	//Restore Source stack again
	while (tempQ.dequeue(x))
		Source.enqueue(x);

	return found;
}

//A function that returns the sum of an integer queue
int QueueSum(LinkedQueue<int> Q) 
{
	int s=0;
	int x;
	while(Q.dequeue(x))
		s += x;
	return s;
}



//This is the program starting point.
int main()
{
	//Declare a queue of integers named "queue1"
	LinkedQueue<int> queue1;
	int x, n;

	cout<<"\nEnter no. of values to enqueue:";
	cin>>n;

	//Test the 1st stack by pushing n values then poping
	cout << "Filling queue 1:" << endl;
	cout << "Enqueuing "<<n<<" values:" << endl;

	cout<<"Please Enter the "<<n<<" values to enqueue in queue1 :";
	for(int i = 0; i < n; i++)
	{
		cin>>x;
		queue1.enqueue(x); //pushing x to stack2
	}

	PrintQueue(queue1);
	cout<<"\nSum of queue items = "<<QueueSum(queue1);

	int a, b;
	cout << "\nEnter a value to replace:";
	cin >> a;
	cout << "\nEnter the new value:";
	cin >> b;

	bool isFound = ReplaceAll(queue1, a, b);
	if (isFound)
		cout << "\nValue replaced";
	else
		cout << "\nValue not found";
	PrintQueue(queue1);


	cout << "\nRemoving first +ve items:";
	removeFirstPostitive(queue1);

	cout << "After removal: ";	
	PrintQueue(queue1);
	
	cout<<endl;

	//Write code to test empty case and to test peekFront function
	return 0;
}
  