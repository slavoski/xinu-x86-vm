#include <xinu.h>
#include "../include/lab1.h"

void sndA()
{
	while (1)
	{
		putc(CONSOLE, 'A');
	}
}

void sndB()
{
	while (1)
	{
		putc(CONSOLE, 'B');
	}
}

void Lab1Code()
{
	resume(create(sndA, 1024, 40, "sndA", 0));
	resume(create(sndB, 1024, 20, "sndb", 0));
}
