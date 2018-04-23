#include "stdafx.h"
#include "stdio.h"
#include "string.h"
void charAddresses(char *string);
void printWord(char *start);
void commaToSpace(char *str);
char *nextWord(char *start);

void main()
{
	int i = 0;
	char location[200] = "7825,CREEK VALLEY,SACRAMENTO,95828,CA";
	char *ptr;

	charAddresses(location);
	printf("\n");

	commaToSpace(location);
	printf("\n");

	puts("\nFirst Word:");
	printWord(location);

	puts("\nSecond Word");
	printWord(location + 5);

	puts("\nThird Word");
	printWord(location + 11);
	puts("");
	printf("\n");

	ptr = location;
	//while (ptr) (used for loop instead because string wasn't terminating and was printing garbage characters at the end)
	for(i=0;i<strlen(ptr);i++)
	{
	printWord(ptr);
	printf("\n");
	ptr = nextWord(ptr);
	}

}
void charAddresses(char *string)
{
	int len, i;
	len = strlen(string);
	printf("Address \t Char\n");
	for (i = 0; i < len; i++)
	{
		printf(" %X \t %c\n", string, *string);
		*string++;
	}
}
void commaToSpace(char *str)
{
	printf("Without commas:\n");
	int len, i;
	len = strlen(str);

	for (i = 0; i < len; i++)
	{
		if (*str == ',')
		{
			*str = ' ';
		}
		printf("%c", *str);

		*str++;
	}
}
void printWord(char *start)
{
	while (*start != ' ')
	{
		putchar(*start);
		*start++;
	}
}
char *nextWord(char *start)
{
	char *pointer;
	pointer = start; 
	while (*pointer != ' ')
	{
		*pointer++;

	}
	if (*pointer = ' ')
		return pointer + 1; 
	return NULL;
}


