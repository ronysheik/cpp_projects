#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct node
{
	int data;
	struct node *left, *right;
	
};

struct stack
{
	struct node* t;
	struct stack* next;
	struct stack* temp;
};

struct stack* head = NULL;
struct stack* temp = NULL;
struct node* curr = NULL;


void push(struct node* bst)
{
	struct stack* newnode = NULL;
	newnode = (struct stack*)malloc(sizeof(*newnode));
	newnode->t = bst;
	newnode->next = NULL;

	if (head == NULL)
	{
		head = newnode;
		temp = head;
	}
	else
	{
	    newnode->next = temp;
		head = newnode;
		temp = head;
	}

}

void pop()
{
	struct stack* trail = head;

	if (head == NULL)
	{
		exit;
	}
	else
	{
		
		printf("%s%d%s", "removed value:", trail->t->data, "\n");
		head = head->next;
		trail->next = NULL;
		free(trail);
	}
}

void print()
{

	struct stack* trail = head;
	while (trail != NULL)
	{
		printf("%u%s", trail->t->data, "->");
		trail = trail->next;
	}

}

struct node* getnewnode(int val)
{
	struct node* newnode = NULL;
	newnode = (struct node*) malloc(sizeof(struct node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->data = val;

	return newnode;

}

struct node* insert(struct node* newroot, int dat)
{
	//struct node* temp = NULL;
	

	if (newroot == NULL)
	{
		newroot = getnewnode(dat);
	}
	else if( dat <= newroot->data)
	{
		newroot->left = insert(newroot->left, dat);
	}
	else if (dat >= newroot->data)
	{
		newroot->right = insert(newroot->right, dat);
	}

	return newroot;


}

struct node* inorder(struct node* temp)
{

	if (temp->left != NULL)
	{
		temp->left = inorder(temp->left);
	}
	printf("%d%s", temp->data, "->");
	if (temp->right != NULL)
	{
		temp->right = inorder(temp->right);
	}
	
	return temp;
}

struct node* inorder_iterative(struct node* temp)
{
	curr = temp;
	while (curr != NULL)
	{
		push(curr);
		curr = curr->left;
	}

}

struct node* postorder(struct node* temp)
{

	if (temp->left != NULL)
	{
		temp->left = inorder(temp->left);
	}
	
	if (temp->right != NULL)
	{
		temp->right = inorder(temp->right);
	}

	printf("%d%s", temp->data, "->");

	return temp;
}
struct node* preorder(struct node* temp)
{
	printf("%d%s", temp->data, "->");
	if (temp->left != NULL)
	{
		temp->left = inorder(temp->left);
	}
	
	if (temp->right != NULL)
	{
		temp->right = inorder(temp->right);
	}

	return temp;
}

int main(int argc, char* argv[])
{

	//int *arr[] = { 1,2,3,4,5 };
	//int *p = &arr;

	struct node* root = NULL;

	root = insert(root, 10);
	insert(root, 5);
	insert(root, 15);
	insert(root, 2);
	insert(root, 17);
	insert(root, 12);

	
	printf("%s", "Inorder\n");
	inorder(root);
	inorder_iterative(root);
	//printf("%s", "\npostorder\n");
	//postorder(root);
	//printf("%s", "\npreorder\n");
	//preorder(root);
	pop();
	printf("%s", "\nstack\n");
	print();
	
	//printf("%d", arr[2]);

	system("pause");
	return 0;
}