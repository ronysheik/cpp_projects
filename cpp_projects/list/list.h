#pragma once
#include <string>

using namespace std;

class list
{
public:
	string str;
	list* next;

	list(string &str)
	{
		this->str = str;
		this->next = NULL;
	}
	~list();
	list* getnewnode(string s);
	list* insert(string &st);
	void print();
	bool IsAlreadyIn(list* n, string& target);
	string reverse(list* n);
	void remove(string &target);
	void sort(list* n);

};
