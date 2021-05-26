#include <math.h> 
#include <stdio.h>
#include <stdlib.h>

int float_to_bit (int a, int location)
{
	int bit = a & 1<<location;
	
	if(bit == 0) return 0;
	else return 1;
}


int double_to_bit (long long a, long long location)
{
	long long b = 1;
	long long bit = a & b<<location;
	
	if(bit == 0) return 0;
	else return 1;
}


int intBinary_to_decimal (long long n)
{
	int decimal = 0, i = 0, remain;
	while(n!=0)
	{
		remain = n%10;
		n /= 10;
		decimal += remain*pow(2,i);
		++i;
	}
	return decimal;
}


double floatBinary_to_decimal (double n)
{
	double decimal = 0;
	int i;
	for(i=-1; i>=-23; i--)
	{
		n *= 10;
		if(n > 1){
			n -= 1;
			decimal += pow(2,i);
		}
	}
	return decimal;
}


double doubleBinary_to_decimal (double n)
{
	double decimal = 0;
	int i;
	for(i=-1; i>=-52; i--)
	{
		n *= 10;
		if(n > 1){
			n -= 1;
			decimal += pow(2,i);
		}
	}
	return decimal;
}


int main(int argc, char *argv[])
{
	int s = (int)atoi(argv[1]);
	
	if(s == 1){					//float number to bit pattern
		float a = (float)atof(argv[2]);
		int *b;
		b = &a;
		
		int i;
		for(i=31; i>=0; i--)
			printf("%d",float_to_bit(*b,i));
	}
	else if(s == 2){			//double number to bit pattern
		double a = (double)atof(argv[2]);
		long long *b;
		b = &a;
		
		int i;
		for(i=63; i>=0; i--)
			printf("%d",double_to_bit(*b,i));
	}
	else if(s == 3){			//bit pattern (float) to float number
		int sig = (int)atoi(argv[2]);
		long long exp = (long long)atoll(argv[3]);
		double fra = (double)atof(argv[4]) * pow(10,-23);
		
		int e = intBinary_to_decimal(exp) - 127;
		double f = floatBinary_to_decimal(fra) +1;
		double floatNumber = f * pow(2,e) * pow(-1,sig);
		printf("%lf\n",floatNumber);
	}
	else if(s == 4){						//bit pattern (double) to float number
		int sig = (int)atoi(argv[2]);
		long long exp = (long long)atoll(argv[3]);
		double fra = (double)atof(argv[4]) * pow(10,-52);
		
		int e = intBinary_to_decimal(exp) - 1023;
		double f1 = doubleBinary_to_decimal(fra);
		double f = f1 +1;
		double floatNumber = f * pow(2,e) * pow(-1,sig);
		printf("%lf\n",floatNumber);
	}
	else{
		printf("you put wrong s");
	}
	return 0;
}
