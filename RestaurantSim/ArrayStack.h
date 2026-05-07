

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"

template<typename T>
class ArrayStack : public StackADT<T>
{
	enum { MAX_SIZE = 100 };
protected:  
	T items[MAX_SIZE];		
	int top;                   
	
public:

	ArrayStack()
	{
		top = -1;
	}  

	bool isEmpty() const
	{
		return top == -1;	
	}  

	bool push(const T& newEntry)
	{
		if( top == MAX_SIZE-1 ) return false;	

		top++;
		items[top] = newEntry;   
		return true;
	}  

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		top--;
		return true;
	}  
	
	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		return true;
	}  

}; 

#endif
