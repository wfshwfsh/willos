#include <stdio.h>

extern int cmain(int argc, char *argv[]);
extern int add(int a, int b);

int cmain(int argc, char *argv[])
{
	printf("cmain HERE\n");
	return 0;
}

int add(int a, int b)
{
	printf("add function\n");
	return (a+b);
}
