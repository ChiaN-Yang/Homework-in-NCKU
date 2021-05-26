#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct vertex_node
{
	int activity;
	int ver;
	int weight;
	struct vertex_node* link;
};
typedef struct vertex_node vertex;
typedef struct vertex_node* v_pointer;

struct array_node
{
	int count;
	v_pointer top;
	v_pointer link;
};
typedef struct array_node node;

void add(int activity, int ver, int weight, v_pointer* top)
{
	v_pointer temp = (v_pointer)malloc(sizeof(vertex));
	temp->activity = activity;
	temp->ver = ver;
	temp->weight = weight;
	*top = temp;
}

vertex pop(v_pointer* top)
{
	v_pointer temp = *top;
	vertex item;
	item.activity = temp->activity;
	item.ver = temp->ver;
	item.weight = temp->weight;
	*top = temp->link;
	free(temp);
	return item;
}

void print_graph(int network_size, node graph[])
{
	vertex temp;
	for (int i = 0; i < network_size; i++)
	{
		temp = pop(&graph[i].top);
		printf("%d %d %d\n", temp.activity, temp.ver, temp.weight);
	}
}

int main()
{
	node aoe[MAX_SIZE];
	//input network size
	int network_size = 0;
	scanf("%d", &network_size);
	for (int i = 0; i < network_size; i++)
	{
		aoe[i].count = 0;
		aoe[i].top = NULL;
	}

	//build graph
	int activity, start_vertex, ending_vertex, weight;
	for (int i = 0; i < network_size; i++)
	{
		scanf("%d%d%d%d", &activity, &start_vertex, &ending_vertex, &weight);
		aoe[ending_vertex].count++;
		add(activity, ending_vertex, weight, &aoe[start_vertex].top);
	}
	print_graph(network_size, aoe);

	return 0;
}
