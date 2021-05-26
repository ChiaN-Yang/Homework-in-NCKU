#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main(int argc, char *argv[])
{
	srand((unsigned) time(NULL));
	int n = atoi(argv[1]), p = atoi(argv[2]);	//n是數字範圍 p是數字個數 
	int m[p];
	int i;
	
	for(i=0; i < p; i++)
		m[i] = rand()%n + 1;	//設定答案 
	
	int u[p], h=0, x=0, k;		//h是完全正確 x是位置不對
	
	while(1)
	{
		for(i=0; i<p; i++){
			scanf("%d", &u[i]);		//使用者輸入數字 
			if(u[i] == m[i])		//檢查幾個完全正確 h
				h++;
		}
			
		for(k=0; k<p; k++){		//檢查幾個數字相同 x
			for(i=0; i<p; i++){
				if(u[k] == m[i]){
					x++;
					break;
			}
		}
		}
		x = x-h;	//扣掉重複計算 
			
		printf("	-> %dH %dX \n", h, x);
		 
		if(h == p)		//猜中 -> 跳出迴圈 
			break;
			
		h=x=0;		//重置HX
		
	}
	
	printf("You are right. Game over.\n");
	
	return 0;
	
}
