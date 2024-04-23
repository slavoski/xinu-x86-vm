/* hello.c - main*/
#include <xinu.h>
#include "../include/lab1.h"
#include "../include/lab2.h"
/* main - just say hello, then exit */




void main(void)
{
	//printf("Hello, world!\n");

	//LAB 1
	//resume(create(Lab1Code, 1024, 20, "lab", 0));
	resume(create(Lab2Code, 1024, 20, "lab2", 0));
}