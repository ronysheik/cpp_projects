/* Author: Rony Sheik
   Emails: rshiek@sfu.ca/ ronysheikh431@gmail.com
*/

#include<iostream>
#include<string>
#include "stack.h"
#include "list.h"


stack *root = NULL;
stack *trav = NULL;

stack::~stack(){}

void stack::push(char &c)
{
	stack *node = new stack(c);

	if (root == NULL)
	{
		root = node;
		trav = root;
	}
	else
	{
		node->next = root;
		root = trav = node;
	}

}
char stack::pop()
{

	stack* trail = root;

	if (root == NULL){
		return NULL;
	}
	
	root = root->next;
	trav = root;
	trail->next = NULL;
	return trail->strs;
}
void stack::print()
{
	stack *traverse = root;
	string str;
	
	if (traverse == NULL)
	{
		exit(1);
	}
	
	while (traverse->next != NULL)
	{
		cout << traverse->next << endl;
		traverse = traverse->next;
	}

}