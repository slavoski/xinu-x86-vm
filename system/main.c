/* hello.c - main*/
#include <xinu.h>
#include "../include/lab1.h"
#include "../include/lab2.h"
/* main - just say hello, then exit */

int main(int argc, char** argv)
{
	//LAB 1
	//resume(create(Lab1Code, 1024, 20, "lab", 0));

	//LAB 2
	//resume(create(Lab2Code, 1024, 20, "lab2", 0));

	uint32 retval;

	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}
	while (1);

	return OK;
}