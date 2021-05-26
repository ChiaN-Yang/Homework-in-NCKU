#include <math.h> 
#include <stdio.h>
#include <stdlib.h>

int float_to_bit (int a, int location);
int double_to_bit (long long a, long long location);
int intBinary_to_decimal (long long n);
double floatBinary_to_decimal (double n);
double doubleBinary_to_decimal (double n);


typedef union{
	float f;
	double d;
	struct{
		double mantissa;
		long long exponent;
		int sign;
	} bitpattern;
} u_float;

struct s_float{
	float f;
	double d;
	double mantissa;
	long long exponent;
	int sign;
};


int main(int argc, char *argv[])
{
	int s = (int)atoi(argv[1]);
	u_float uf;
	struct s_float sf;
	
	if(s == 1){    //float number to bit pattern
		uf.f = (float)atof(argv[2]);    //union
		int *b;
		b = &uf.f;
		int i;
		for(i=31; i>=0; i--)
			printf("%d",float_to_bit(*b,i));
		printf("\n");
		
		sf.f = (float)atof(argv[2]);    //struct
		int *a;
		a = &sf.f;
		for(i=31; i>=0; i--)
			printf("%d",float_to_bit(*a,i));
		printf("\n");
	}
	else if(s == 2){    //double number to bit pattern  
		uf.d = (double)atof(argv[2]);    //union
		long long *b;
		b = &uf.d;
		int i;
		for(i=63; i>=0; i--)
			printf("%d",double_to_bit(*b,i));
		printf("\n");
		
		sf.d = (double)atof(argv[2]);    //struct
		long long *a;
		a = &sf.d;
		for(i=63; i>=0; i--)
			printf("%d",double_to_bit(*a,i));
		printf("\n");
	}
	else if(s == 3){    //bit pattern (float) to float number
		uf.bitpattern.sign = (int)atoi(argv[2]);    //union
		uf.bitpattern.exponent = (long long)atoll(argv[3]);
		uf.bitpattern.mantissa = (double)atof(argv[4]) * pow(10,-23);
		int e = intBinary_to_decimal(uf.bitpattern.exponent) - 127;
		double f = floatBinary_to_decimal(uf.bitpattern.mantissa) +1;
		uf.d = f * pow(2,e) * pow(-1,uf.bitpattern.sign);
		printf("%.3lf\n",uf.d);
		
		sf.sign = (int)atoi(argv[2]);    //struct
		sf.exponent = (long long)atoll(argv[3]);
		sf.mantissa = (double)atof(argv[4]) * pow(10,-23);
		e = intBinary_to_decimal(sf.exponent) - 127;
		f = floatBinary_to_decimal(sf.mantissa) +1;
		sf.d = f * pow(2,e) * pow(-1,sf.sign);
		printf("%.3lf\n",uf.d);
	}
	else if(s == 4){    //bit pattern (double) to float number
		uf.bitpattern.sign = (int)atoi(argv[2]);    //union
		uf.bitpattern.exponent = (long long)atoll(argv[3]);
		uf.bitpattern.mantissa = (double)atof(argv[4]) * pow(10,-52);
		int e = intBinary_to_decimal(uf.bitpattern.exponent) - 1023;
		double f1 = doubleBinary_to_decimal(uf.bitpattern.mantissa);
		double f = f1 +1;
		uf.d = f * pow(2,e) * pow(-1,uf.bitpattern.sign);
		printf("%lf\n",uf.d);
		
		sf.sign = (int)atoi(argv[2]);    //struct
		sf.exponent = (long long)atoll(argv[3]);
		sf.mantissa = (double)atof(argv[4]) * pow(10,-52);
		e = intBinary_to_decimal(sf.exponent) - 1023;
		f1 = doubleBinary_to_decimal(sf.mantissa);
		f = f1 +1;
		sf.d = f * pow(2,e) * pow(-1,sf.sign);
		printf("%lf\n",sf.d);
	}
	else{
		printf("you put wrong s");
	}
	return 0;
}


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
