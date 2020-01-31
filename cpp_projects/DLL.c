#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


struct list
{
	struct list* next;
	struct list* prev;
};

//#define NUM = 10
struct node
{
	int data;
	char *field[5];
	struct list list;
	
};

struct node *head = NULL;
struct node* tail = NULL;
struct node* curr = NULL;

struct node* getnewnode(struct node* h, int val);
void insert(int val);
void delete(int val);
void reverse();
void print();

struct node* getnewnode(struct node* h, int val)
{
	//struct node* newnode;
	h = (struct node*) malloc(sizeof(struct node));
	h->list.next = NULL;
	h->list.prev = NULL;
	//newnode->next = NULL;
	//newnode->prev = NULL;
	h->data = val;


	return h;
}

void insert(int val)
{

	
	struct node* newnode = NULL;

	newnode = getnewnode(&newnode, val);
	if (head == NULL)
	{
		head = newnode;
		curr = head;
	}
	else
	{
		newnode->list.prev = curr;
		curr->list.next = newnode;
		curr = curr->list.next;
		tail = curr;
	}


}

void delete(int val)
{
	struct node* temp;
	struct node* trail;
	struct node* curr;
	temp = curr = head;

	while (temp != NULL)
	{
		trail = temp;
		temp = temp->list.next;
		if (trail->data != val)
			continue;
		curr = trail->list.prev;
		curr->list.next = temp;
		temp->list.prev = curr;
		trail->list.next = NULL;
		trail->list.prev = NULL;
		free(trail);
		break;
			
	}
}

void reverse()
{
	struct node* t;
	struct node* temp;
	t = head;

	while (t != NULL)
	{
		temp = t->list.next;
		t->list.next = t->list.prev;
		t->list.prev = temp;
		t = temp;
	}
	
	head = tail;
}

void print()
{
	struct node* temp;
	temp = head;

	while (temp != NULL)
	{
		printf("%d%s", temp->data, "->");
		temp = temp->list.next;
	}

}

int main(int argc, int *argv[])
{

	for (int i = 100; i < 112;i++)
	{
		insert(i);
	}
	print();
	delete(105);
	delete(108);
	delete(109);
	printf("%s", "\nafter deletion\n");
	print();
    printf("%s", "\nreverse DLL\n");
	reverse();
	print();

	//printf("%s", "hello world");
	system("pause");
	return 0;
}