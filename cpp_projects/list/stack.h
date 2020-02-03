
#include "list.h"
#include<string>

using namespace std;

class stack
{
public:

	char strs;
	stack* next;

	stack(const char &c)
	{
		this->strs = c;
		this->next = NULL;
	}
	~stack();
	void push(char &c);
	char pop();
	void print();
};
