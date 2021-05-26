#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char name[20];
	char phone[20];
	struct node* left, * right;
	int ht;
}node;

node* insert(node* T, char name[], char phone[]);
int BF(node* T);
int height(node* T);
node* rotateright(node* x);
node* rotateleft(node* x);
node* RR(node* T);
node* LL(node* T);
node* LR(node* T);
node* RL(node* T);
void preorder(node* T);
void preorder_in(node* T);
node* search(node* root, char name[20]);

node* insert(node* T, char name[], char phone[])
{
	if (T == NULL)
	{
		T = (node*)malloc(sizeof(node));
		strncpy(T->name, name, 19);
		strncpy(T->phone, phone, 19);
		T->left = NULL;
		T->right = NULL;
	}
	else
		if (strcmp(name, T->name) > 0)		// insert in right subtree
		{
			T->right = insert(T->right, name, phone);
			if (BF(T) == -2)
				if (strcmp(name, T->right->name) > 0)
					T = RR(T);
				else
					T = RL(T);
		}
		else
			if (strcmp(name, T->name) < 0)
			{
				T->left = insert(T->left, name, phone);
				if (BF(T) == 2)
					if (strcmp(name, T->left->name) < 0)
						T = LL(T);
					else
						T = LR(T);
			}

	T->ht = height(T);

	return(T);
}

int BF(node* T)
{
	int lh, rh;
	if (T == NULL)
		return(0);

	if (T->left == NULL)
		lh = 0;
	else
		lh = 1 + T->left->ht;

	if (T->right == NULL)
		rh = 0;
	else
		rh = 1 + T->right->ht;

	return(lh - rh);
}

int height(node* T)
{
	int lh, rh;
	if (T == NULL)
		return(0);

	if (T->left == NULL)
		lh = 0;
	else
		lh = 1 + T->left->ht;

	if (T->right == NULL)
		rh = 0;
	else
		rh = 1 + T->right->ht;

	if (lh > rh)
		return(lh);

	return(rh);
}

node* rotateright(node* x)
{
	node* y;
	y = x->left;
	x->left = y->right;
	y->right = x;
	x->ht = height(x);
	y->ht = height(y);
	return(y);
}

node* rotateleft(node* x)
{
	node* y;
	y = x->right;
	x->right = y->left;
	y->left = x;
	x->ht = height(x);
	y->ht = height(y);

	return(y);
}

node* RR(node* T)
{
	T = rotateleft(T);
	return(T);
}

node* LL(node* T)
{
	T = rotateright(T);
	return(T);
}

node* LR(node* T)
{
	T->left = rotateleft(T->left);
	T = rotateright(T);

	return(T);
}

node* RL(node* T)
{
	T->right = rotateright(T->right);
	T = rotateleft(T);
	return(T);
}

void preorder(node* T)
{
	if (T != NULL)
	{
		printf("%s", T->name);
		if (T->left != NULL)	printf(" ");
		preorder(T->left);
		if (T->right != NULL)	printf(" ");
		preorder(T->right);
	}
}

node* search(node* root, char name[20])
{
	if (!root) return NULL;		//root not exist
	if (strcmp(name, root->name) == 0) return root;		//root is key
	if ((strcmp(name, root->name) < 0 && root->left == NULL) || (strcmp(name, root->name) > 0 && root->right == NULL))
		return NULL;
	if (strcmp(name, root->name) < 0)
		return  search(root->left, name);		//go left
	return search(root->right, name);		//go right
}

int main()
{
	node* AVLtree = NULL;
	node* temp = NULL;
	char name1[] = "Bob";
	char name2[] = "Alice";
	char name3[] = "Paul";
	char name4[] = "David";
	char name5[] = "Ruby";
	char name6[] = "Charlie";
	char name7[] = "Amy";
	char phone1[] = "0900000000";
	char phone2[] = "0900000001";
	char phone3[] = "0900000002";
	char phone4[] = "0900000003";
	char phone5[] = "0900000004";
	char phone6[] = "0900000005";
	AVLtree = insert(AVLtree, name1, phone1);
	AVLtree = insert(AVLtree, name2, phone2);
	AVLtree = insert(AVLtree, name3, phone3);
	AVLtree = insert(AVLtree, name4, phone4);
	AVLtree = insert(AVLtree, name5, phone5);
	AVLtree = insert(AVLtree, name6, phone6);
	preorder(AVLtree);
	temp = search(AVLtree, name3);
	if(temp)	printf("\n%s %s", temp->name, temp->phone);
	else printf("\n%s null", name3);
	temp = search(AVLtree, name7);
	if (temp)	printf("\n%s %s", temp->name, temp->phone);
	else printf("\n%s null", name7);
	temp = search(AVLtree, name5);
	if (temp)	printf("\n%s %s", temp->name, temp->phone);
	else printf("\n%s null", name5);

	return 0;
}
