#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main(int argc, char *argv[])
{
	srand((unsigned) time(NULL));
	int n = atoi(argv[1]), p = atoi(argv[2]);	//n�O�Ʀr�d�� p�O�Ʀr�Ӽ� 
	int m[p];
	int i;
	
	for(i=0; i < p; i++)
		m[i] = rand()%n + 1;	//�]�w���� 
	
	int u[p], h=0, x=0, k;		//h�O�������T x�O��m����
	
	while(1)
	{
		for(i=0; i<p; i++){
			scanf("%d", &u[i]);		//�ϥΪ̿�J�Ʀr 
			if(u[i] == m[i])		//�ˬd�X�ӧ������T h
				h++;
		}
			
		for(k=0; k<p; k++){		//�ˬd�X�ӼƦr�ۦP x
			for(i=0; i<p; i++){
				if(u[k] == m[i]){
					x++;
					break;
			}
		}
		}
		x = x-h;	//�������ƭp�� 
			
		printf("	-> %dH %dX \n", h, x);
		 
		if(h == p)		//�q�� -> ���X�j�� 
			break;
			
		h=x=0;		//���mHX
		
	}
	
	printf("You are right. Game over.\n");
	
	return 0;
	
}
