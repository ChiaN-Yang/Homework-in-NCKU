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
node* search(node* root, char name[20]);

int main()
{
	char op;
	char name[20], phone[20];
	node* AVLtree = NULL;
	node* temp = NULL;

	scanf("%c", &op);
	switch (op)
	{
		case 'D':	while(1)
					{
						for (int i = 0; i < 20; i++)
						{
							name[i] = '\0';
							phone[i] = '\0';
						}
						scanf("%s", &name);
						if(name[0] == 'S' && name[1] == '\0')
							break;
						if (name[0] == 'E' && name[1] == '\0')
							return 0;
						scanf("%s", &phone);
						AVLtree = insert(AVLtree, name, phone);
					}
					preorder(AVLtree);

		case 'S':	while (1)
					{
						for (int i = 0; i < 20; i++)
							name[i] = '\0';
						scanf("%s", &name);
						if (name[0] == 'E' && name[1] == '\0')
							break;
						temp = search(AVLtree, name);
						if (temp)
							printf("\n%s %s", temp->name, temp->phone);
						else
							printf("\n%s null", name);
					}

		case 'E':	return 0;
	}
}

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
		if (T->left)	printf(" ");
		preorder(T->left);
		if (T->right)	printf(" ");
		preorder(T->right);
	}
}

node* search(node* root, char name[20])
{
	if (!root) return NULL;		//root not exist
	if (strcmp(name, root->name) == 0) return root;		//root is key
	if (strcmp(name, root->name) < 0)
		return  search(root->left, name);		//go left
	return search(root->right, name);		//go right
}