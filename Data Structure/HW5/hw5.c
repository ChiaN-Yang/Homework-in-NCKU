#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 13
#define PRIME 7

void insert(int hash_table[TABLE_SIZE], int key);
void print_table(int hash_table[TABLE_SIZE]);

int main()
{
	int key;
	int hash_table[TABLE_SIZE];
	for(int i = 0; i <TABLE_SIZE; i++)
		hash_table[i] = -1;
	
	while(scanf("%d", &key) != EOF)
		insert(hash_table, key);
	
	print_table(hash_table);
	
	return 0;
}

void insert(int hash_table[TABLE_SIZE], int key)
{
	int hash1 = key % TABLE_SIZE;
	int hash2 = PRIME - (key % PRIME);
	int hash = hash1 % TABLE_SIZE;
	int i = 1;
	
	while(1){
		if (hash_table[hash] == -1)
		{
			hash_table[hash] = key;
			break;
		}
		else
		{
			hash = (hash1 + i*hash2)%TABLE_SIZE;
			i++;
		}
	}
}

void print_table(int hash_table[TABLE_SIZE])
{
	int count = 0;
	
	while(1)
	{
		if(hash_table[count] == -1)	count++;
		else
		{
			printf("%d->%d", count, hash_table[count]);
			count++;
			break;
		}
	}
	
	for(int i = count; i < TABLE_SIZE; i++)
	{
		if(hash_table[i] != -1)
			printf("\n%d->%d", i, hash_table[i]);
	}
}
