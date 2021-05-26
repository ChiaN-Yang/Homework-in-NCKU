#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int getopt(int argc, char * const argv[], const char *optstring);
void substr(char *dest, const char* src, unsigned int start, unsigned int cnt);
int get_num(const char* data, unsigned int start);
char double_to_bit (int a, int location);
int intBinary_to_decimal (int n);
int base_num(const char* src, unsigned int start);
void int_to_base(char target[32], int num[32], int word_len, const char b64[], int word_left);

int main(int argc, char** argv)
{
    //put commandline into path
	int opt = 0;
    char filename[] = "input.txt";
	char out_filename[] ="output.txt";

    //read file
    FILE* file;
    char data[32];	//2123
    char data1[32];	//21232A30393C3F405B5E606F7E

    if ((file = fopen(filename, "r")) == NULL)
    {
        printf("open_file_error");
        exit(1);
    }

    fgets(data, 32, file);
    strcpy(data1, data);
    fgets(data, 32, file);

    fclose(file);

    //Compress
    int len1 = strlen(data1);
    int len2 = strlen(data);

    int num1[32] = { 0 };
    int num2[32] = { 0 };

    for (int i = 0; i < len1; i++)
        num1[i] = get_num(data1, i);

    for (int i = 0; i < len2; i++)
        num2[i] = get_num(data, i);

    //the binary data store in nibble1 and nibble2
    char nibble1[128] = { 0 };
    char nibble2[128] = { 0 };
    int k = 0;

    for (int j = 0; j < len1; j++)
        for (int i = 3; i >= 0; i--)
        {
            nibble1[k] = double_to_bit(num1[j], i);
            k++;
        }

    k = 0;

    for (int j = 0; j < len2; j++)
        for (int i = 3; i >= 0; i--)
        {
            nibble2[k] = double_to_bit(num2[j], i);
            k++;
        }

    //the int data store in base1 and base2
    int word_len1 = (len1 - 1) * 4 / 6 + 1;
    int word_len2 = (len2 - 1) * 4 / 6 + 1;
    int word_left1 = (len1 - 1) * 4 % 6;
    int word_left2 = (len2 - 1) * 4 % 6;
    if (word_len1 == 0)
        word_len1 -= 1;
    if (word_len2 == 0)
        word_len2 -= 1;


    int base1[32];
    int base2[32];

    for (int i = 0; i < word_len1; i++)
        base1[i] = base_num(nibble1, i * 6);

    for (int i = 0; i < word_len2; i++)
        base2[i] = base_num(nibble2, i * 6);

    //trsform number to word
    const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    char final_base1[32];
    char final_base2[32];

    int_to_base(final_base1, base1, word_len1, b64chars, word_left1);
    int_to_base(final_base2, base2, word_len2, b64chars, word_left2);

    printf("%s\n", final_base1);
    printf("%s\n", final_base2);

    //write file
    FILE* outfile;

    if ((outfile = fopen(out_filename, "w")) == NULL)
    {
        printf("open_file_error");
        exit(1);
    }

    fprintf(outfile, "%s\n%s", final_base1, final_base2);

    fclose(outfile);

    return 0;

}

void substr(char* dest, const char* src, unsigned int start, unsigned int cnt)
{
    strncpy(dest, src + start, cnt);
    dest[cnt] = 0;
}

int get_num(const char* data, unsigned int start)
{
    int num;
    char num_cp[1];

    substr(num_cp, data, start, 1);

    if (strncmp(num_cp, "A", 1) < 0)
        num = atoi(num_cp);
    else if (strncmp(num_cp, "A", 1) == 0)
        num = 10;
    else if (strncmp(num_cp, "B", 1) == 0)
        num = 11;
    else if (strncmp(num_cp, "C", 1) == 0)
        num = 12;
    else if (strncmp(num_cp, "D", 1) == 0)
        num = 13;
    else if (strncmp(num_cp, "E", 1) == 0)
        num = 14;
    else if (strncmp(num_cp, "F", 1) == 0)
        num = 15;

    return num;
}

char double_to_bit(int a, int location)
{
    int b = 1;
    int bit = a & b << location;

    if (bit == 0) return '0';
    else return '1';
}

int intBinary_to_decimal(int n)
{
    int decimal = 0, i = 0, remain;
    while (n != 0)
    {
        remain = n % 10;
        n /= 10;
        for (int j = 0; j < i; j++)
            remain = remain * 2;
        decimal += remain;
        ++i;
    }
    return decimal;
}

int base_num(const char* src, unsigned int start)
{
    int a, b;
    char n[8];
    substr(n, src, start, 6);
    a = atoi(n);
    b = intBinary_to_decimal(a);
    return b;
}

void int_to_base(char target[32], int num[32], int word_len, const char b64[], int word_left)
{
    for (int i = 0; i < word_len; i++)
        target[i] = b64[num[i]];
	
	if (word_left == 2) {
        target[word_len] = b64[64];
        target[word_len + 1] = b64[64];
    }
    if (word_left == 4)
        target[word_len] = b64[64];
        
}
