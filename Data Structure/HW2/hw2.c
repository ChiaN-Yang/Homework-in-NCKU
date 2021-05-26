#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//read file
	char filename[] = "input.txt";
	FILE* fp;
	
	//store read information--put in StrLine and seperate to op and num 
	char StrLine[16];
	char op[10];
	char num[5];
	int x = 0;

	//line A
	int A[128];
	int rear_a = -1;
	int front_a = -1;

	//line B
	int B[128];
	int rear_b = -1;
	int front_b = -1;
	
	//plate stack
	int plate[10] = {0};
	int top = -1;


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
			plate[++top] = atoi(num);
		}
		else if(strcmp(op, "POP") == 0)
		{
			x = plate[top--];
		}
		else if(strcmp(op, "ENQUEUE") == 0)
		{
			if (num[0] == 'A')
				A[++rear_a] = x;
			else if (num[0] == 'B')
				B[++rear_b] = x;
		}
		else if(strcmp(op, "DEQUEUE") == 0)
		{
			if (num[0] == 'A')
				plate[++top] = A[++front_a];
			else if (num[0] == 'B')
				plate[++top] = B[++front_b];
		}
		
	}
	
	fclose(fp);
	
	for(int i = top; i > -1; i--)
		printf("%d\n",  plate[i]);
	
	
	return 0;
}
