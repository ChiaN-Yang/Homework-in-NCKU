#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Nmax 30 

int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	
    int grid[N+2][N+2], *p, *q, *op;
    int i, j;
    int op_x, op_y;
    int n = 0;
    int over = 0;

	//initial
	for (p = &grid[0][0]; p <= &grid[N+1][N+1]; p++)
		*p = 0;
	
	//put_mine
	srand(time(NULL));
	do {
        int mine_x = rand() % N +1;
        int mine_y = rand() % N +1;
        int *mine = &grid[mine_x][mine_y];
        if (*mine != -1) {
            *mine = -1;
            n++;
        }
    } while (n < M);
    
    //calculate_num_of_cells
    for (p = &grid[0][0]; p <= &grid[N+1][N+1]; p++){
    		if (*p == 0){
    			for (i = -(N+2); i <= (N+2); i+=(N+2)){
    				for (q = p+i - 1; q <= p+i + 1; q++)
					if (*q == -1)	*p+=1;
				}
			}
		}
	
	//print_blanks
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
			printf(" ?");
        printf("\n");
    }
	
    while (over == 0){
    	//N is greater than Nmax
    	if (N > Nmax) {
    	printf("N is too large ");
    	system("clear");
    	break;
		}
    	
    	//choose a position
    	scanf("%d%d", &op_x, &op_y);
    	op_x++;
    	op_y++;
    	op = &grid[op_x][op_y];
    
    	system("clear"); //clear screen
    	
    	//assign_inf_after_open
    	if (*op == -1)	*op = -2;
    	if (*op >= 0 && *op <= 8)	*op += 10;
    	
    	open_surrounding(grid[N+2][N+2], op, N);	//open_surrounding
    	
    	//check_over
    	over = 1;
    	if (*op == -2)	over = -1;
    	else
    		for (i = 1; i <= N; i++)
        		for (p = grid[i]+1; p <= grid[i]+N; p++)
        			if (*p >= 0 && *p <= 8)
        				over = 0;
    	
    	if (over == 0)	//print_cells
    	{
    		for (i = 1; i <= N; i++) {
        		for (p = grid[i]+1; p <= grid[i]+N; p++) { 
            		if (*p < 10)
                		printf(" ?");
            		else if (*p == 10)
                		printf(" _");
            		else
                		printf(" %d", *p - 10);
        		}
        	printf("\n");
			}
	    	printf("\n");
		}
    	else
		{
    		for (i = 1; i <= N; i++) {
        		for (p = grid[i]+1; p <= grid[i]+N; p++) { 
            		if (*p < 10 && *p >= 0)
                		printf(" ?");
                	else if (*p <= -1)
                		printf(" *");
            		else if (*p == 10)
                		printf(" _");
            		else
                		printf(" %d", *p - 10);
        		}
        	printf("\n");
			}
			printf("\n");
			if (over == 1)
				printf("you win ");
			if (over == -1)
				printf("you are dead ");
		}
	}

    return(0);
}


void open_surrounding(int grid[][Nmax], int *op, int N)
{
	int *p, i;
    if (*op == 10)
	{
     	for (i = -(N+2); i <= (N+2); i+=(N+2)){
     		for (p = op+i - 1; p <= op+i + 1; p++){
     			if (*p >= 0 && *p <=8)
				{
               	 	*p += 10;
                	open_surrounding(grid, op, N);
             	}
        	}
		}
	}
}
