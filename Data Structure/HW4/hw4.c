#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int data;
	struct node* left_child;
	struct node* right_child;
};
typedef struct node tree;
typedef struct node* tree_pointer;

void level_order(tree_pointer ptr);
tree_pointer search(tree_pointer root, int key);
void insert_node(tree_pointer* node, int num);
tree_pointer minValueNode(tree_pointer node);
tree_pointer delete_node(tree_pointer root, int key);

int main()
{
	tree_pointer search_tree = NULL;
	char add[1024]={'\0'}, dele[1024]={'\0'};
	gets(add);
	gets(dele);
	
	for(int i = 0; i < 1023; i++)
	{
		if(add[i]>47 && add[i]<58)
			insert_node(&search_tree, atoi(&add[i]));
	}
	
	for(int i = 0; i < 1023; i++)
	{
		if(dele[i]>47 && dele[i]<58)
			search_tree = delete_node(search_tree, atoi(&dele[i]));
	}
	
	level_order(search_tree);

	return 0;
}

void level_order(tree_pointer ptr)
{
	int front = 0, rear = 0;
	tree_pointer queue[2000];
	if (!ptr) return;	//empty tree

	queue[++rear] = ptr;

	ptr = queue[++front];
	printf("%d", ptr->data);
	if (ptr->left_child)
		queue[++rear] = ptr->left_child;
	if (ptr->right_child)
		queue[++rear] = ptr->right_child;

	for (;;)
	{
		ptr = queue[++front];
		if (ptr)
		{
			printf("\n%d", ptr->data);
			if (ptr->left_child)
				queue[++rear] = ptr->left_child;
			if (ptr->right_child)
				queue[++rear] = ptr->right_child;
		}
		else break;
	}
}


tree_pointer search(tree_pointer root, int key)
{
	if (!root) return NULL;		//root not exist
	if (key == root->data) return root;		//root is key
	if ((key < root->data && root->left_child == NULL) || (key > root->data && root->right_child == NULL))
		return root;
	if (key < root->data)
		return  search(root->left_child, key);		//go left
	return search(root->right_child, key);		//go right
}

void insert_node(tree_pointer* node, int num)
{
	tree_pointer ptr, temp = search(*node, num);

	if (temp || !(*node))	//num is not in the tree
	{
		ptr = (tree_pointer)malloc(sizeof(tree));

		ptr->data = num;
		ptr->left_child = ptr->right_child = NULL;

		if (*node)	//insert it
			if (num < temp->data) temp->left_child = ptr;
			else temp->right_child = ptr;
		else *node = ptr;
	}
}

tree_pointer minValueNode(tree_pointer node)
{
	tree_pointer current = node;

	while (current && current->left_child != NULL)
		current = current->left_child;

	return current;
}

tree_pointer delete_node(tree_pointer root, int key)
{
	if (root == NULL)	return root;

	if (key < root->data)
		root->left_child = delete_node(root->left_child, key);
	else if (key > root->data)
		root->right_child = delete_node(root->right_child, key);
	else	//key is same as data
	{
		//node with one child or no child
		if (root->left_child == NULL)
		{
			tree_pointer temp = root->right_child;
			free(root);
			return temp;
		}
		else if (root->right_child == NULL)
		{
			tree_pointer temp = root->left_child;
			free(root);
			return temp;
		}
		//node with twochild
		tree_pointer temp = minValueNode(root->right_child);
		root->data = temp->data;
		root->right_child = delete_node(root->right_child, temp->data);
	}
	return root;
}
