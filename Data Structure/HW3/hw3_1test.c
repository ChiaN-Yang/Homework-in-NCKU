#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue_node {
	int num;
	struct queue_node* link;
};
typedef struct queue_node queue;
typedef struct queue_node* q_pointer;

struct stack_node {
	int num;
	struct stack_node* link;
};
typedef struct stack_node stack;
typedef struct stack_node* s_pointer;

q_pointer front_a = NULL;
q_pointer rear_a = NULL;
q_pointer front_b = NULL;
q_pointer rear_b = NULL;
s_pointer top = NULL;


void push(int item)
{
	s_pointer temp = (s_pointer)malloc(sizeof(stack));
	temp->num = item;
	temp->link = top;
	top = temp;
}

int pop()
{
	s_pointer temp = top;
	int item = temp->num;
	top = temp->link;
	free(temp);
	return item;
}

void enqueue(char line, int item)
{	
	q_pointer temp = (q_pointer)malloc(sizeof(queue));
	temp->num = item;
	temp->link = NULL;
	
	switch(line)
	{
		case 'A':
			if (front_a)	(rear_a)->link = temp;
			else front_a = temp;
			rear_a = temp;
			break;
		case 'B':
			if (front_b)	(rear_b)->link = temp;
			else front_b = temp;
			rear_b = temp;
			break;
	}
	
}

void dequeue(char line)
{
	int item = 0;
	q_pointer temp;
	switch(line)
	{
		case 'A':
			temp = front_a;
			item = temp->num;
			front_a = temp->link;
			free(temp);
			push(item);
			break;
		case 'B':
			temp = front_b;
			item = temp->num;
			front_b = temp->link;
			free(temp);
			push(item);
			break;
	}

}


int main()
{
	//read file
	char filename[] = "p1_input.txt";
	FILE* fp;
	
	//store read information--put in StrLine and seperate to op and num 
	char StrLine[16];
	char op[10];
	char num[5];
	int x = 0;
	int n = 0;
	

	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("open file error!");
		return -1;
	}
	
	while (fgets(StrLine, 15, fp) != NULL)
	{
		sscanf(StrLine, "%s %s", &op, &num);

		if(strcmp(op, "PUSH") == 0)
		{
			n = atoi(num);
			push(n);
		}
		else if(strcmp(op, "POP") == 0)
		{
			x = pop();
		}
		else if(strcmp(op, "ENQUEUE") == 0)
		{
			enqueue(num[0], x);
		}
		else if(strcmp(op, "DEQUEUE") == 0)
		{
			dequeue(num[0]);
		}
		
	}
	
	fclose(fp);
	
	for (s_pointer i = top; i != NULL; i = i->link)
		printf("%d\n", i->num);
	
	
	return 0;
}
