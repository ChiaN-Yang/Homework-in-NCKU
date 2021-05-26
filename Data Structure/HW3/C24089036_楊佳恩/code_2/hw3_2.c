#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct queue_node {
	char suit;
	struct queue_node* link;
};
typedef struct queue_node queue;
typedef struct queue_node* q_pointer;

q_pointer front = NULL;
q_pointer rear = NULL;

void enqueue(char s);
void dequeue();
void print_queue();

int main()
{
	//store read information
	char StrLine[10];
	char trash;
	char s;
	char card[14] = { "KQJ198765432A" };
	
	while (scanf("%[^\n]%c", &StrLine, &trash) != EOF)
	{
		enqueue(StrLine[0]);
	}
	rear->link = front;

	for (int i = 0; i < 13; i++)
	{
		print_queue();

		while (front->suit != card[i])
		{
			front = front->link;
			rear = rear->link;
			print_queue();
		}
		dequeue();
	}

	return 0;
}

void enqueue(char s)
{
	q_pointer temp = (q_pointer)malloc(sizeof(queue));
	temp->suit = s;
	temp->link = NULL;

	if (front)	(rear)->link = temp;
	else front = temp;
	rear = temp;
}

void dequeue()
{
	q_pointer temp = front;
	front = temp->link;
	rear->link = front;
	free(temp);
}

void print_queue()
{
	for (q_pointer i = front; i != rear; i = i->link)
	{
		printf("%c", i->suit);
		if (i->suit == '1') printf("0");
		printf(" ");
	}
	printf("%c", rear->suit);
	if (rear->suit == '1') printf("0");
	printf(" \n");
}
