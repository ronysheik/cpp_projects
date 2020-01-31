/* Author: Rony Sheik
   Emails: rshiek@sfu.ca/ ronysheikh431@gmail.com
*/

#include <iostream>
#include <string>
#include <vector>
#include "list.h"
#include "stack.h"

using namespace std;

// head of the linked list
list* head = NULL;
list* temp = NULL;

list* list::getnewnode(string s)
{
	// new node construction using constructor
	list* node = new list(s);
	return node;
}

// destructor gets called each time delete nodes
list::~list() {};

// pusing and poping from the stack and return the reverse string
string list::reverse(list* n)
{
	stack* obj = NULL;
	int len = (n->str).size() - 1;

	// push the string to the stack
	for (int i = 0;i <= len;i++){
		obj->push(n->str[i]);
	}

	// pop the string fromt the stack
	for (int j = 0;j <= len;j++){
		n->str[j] = obj->pop();
	}

	return n->str;
}

list* list::insert(string &st)
{
	list* newnode = getnewnode(st);
	list* node = head;
	list* tar = NULL;
	list* prev = NULL;
	
	// check if the string alreay in the list
	bool flag = IsAlreadyIn(head, newnode->str);
	int target_len = st.length();

	if (!flag)
	{
		if (head == NULL)
		{
			head = newnode;
			temp = head;
		}
		else
		{
			temp->next = newnode;
			temp = newnode;
		}
	}
	else
	{
		// get the reverse string and link it to the list
		newnode->str = reverse(newnode);
		temp->next = newnode;
		temp = newnode;
	}

	return head;
}

void list::print()
{
	list* node = head;
	if (head == NULL)
	{
		cout << "nothing" << endl;
	}

	while (node != NULL)
	{
		cout << node->str << "->";
		node = node->next;
	}

}

void list::remove(string &target)
{
	list* node = head;
	list* tar = NULL;
	list* prev = NULL;
	prev = tar = head;

	// remove from the head
	if (head != NULL && head->str == target)
	{
		head = head->next;
		prev = head;
		tar->next = NULL;
		delete tar;
	}
	else
	{
		// tarverse the list to find the target and remove 
		while (node->next != NULL)
		{
			prev = node;
			node = node->next;
			if (node->str != target)
				continue;
			prev->next = prev->next->next;
			node->next = NULL;
			delete node;
			break;

		}
	}
}

// check if the current element is already in the list 
bool list::IsAlreadyIn(list* n,string& s)
{
	list* node = head;
	if (head == NULL)
	{
		return false;;
	}
	while (node != NULL)
	{
		if (node->str == s)
		{
			return true;
		}
		node = node->next;
	}

	return false;
}

// sort the list and take head as paramater
void list::sort(list* n)
{
	bool flag;
	string temp;
	list* newhead = NULL;
	list* root = NULL;
	if (n == NULL)
	{
		cout << "empty list" << endl;
	}

	// sorting
	do
	{
		flag = false;
		root = n;

		while (root->next != NULL)
		{
			if ((root->next->str).length() > (root->str).length())
			{
				temp = root->str;
				root->str = root->next->str;
				root->next->str = temp;
				flag = true;
			}
			root = root->next;
		}
	} 
	while (flag);
	
}

int main()
{

	list* root = NULL;
	size_t i;
	// original list
	vector<string> orgList = { "one", "two", "three" };
	//orgList.push_back("one");
	//orgList.push_back("two");
	//orgList.push_back("three");
	//orgList.push_back("four");
	size_t len = orgList.size();
	for (i = 0;i <len ;i++)
	{
		root = root->insert(orgList[i]);
	}
	cout << "\nOriginal List:\n";
	root->print();

	// add more elements 
	vector<string> AddList = { "one", "two", "five", "six" };
	len = AddList.size();
	//AddList.push_back("one");
	//AddList.push_back("hundred");
	//AddList.push_back("three");
	cout << "\n\nElements will be added\n" << "[";
	for (i = 0;i < len;i++)
	{
		cout << AddList[i] << "->";
		root->insert(AddList[i]);
	}
	cout << "]\n";
	cout << "\nNew List with added elements and reverse elements if matches:\n";
	root->print();
	

	// delete list
	vector<string> DelList = { "two", "five" };
	len = DelList.size();
	//myvec.push_back("one");
	//myvec.push_back("six");
	//myvec.push_back("two");
	cout << "\n\nElements will be deleted\n" << "[";
	for (i = 0;i<len;i++)
	{
		cout << DelList[i] << "->";
		root->remove(DelList[i]);
	}
	cout << "]\n";
	cout << "\n\nNew List After Deletion:\n";
	root->sort(head);
	root->print();
	cin.get();
	return 0;
}

/*test scenario 

Features:

List shall only contain unique values
- List shall be ordered as follows
--- Most character count to least character count
--- In the event of a tie, reverse alphabetical

// ********* In the list also contains the reverse string that has a tie *************

 Original List = ['one', 'two', 'three',]
 Add List = ['one', 'two', 'five', 'six]
 Delete List = ['two', 'five']
 Result List = ['three', 'six', 'one']*

*/