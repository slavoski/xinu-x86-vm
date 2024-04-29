#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include "../include/lab4.h"

sid32 lab4semaphore;
sid32 lab4WaitForAlice;
sid32 lab4WaitForBob;
sid32 waitForBobAndAlice;

shellcmd xsh_lab4(int nargs, char* args[])
{
	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

	lab4semaphore = semcreate(0);
	lab4WaitForAlice = semcreate(0);
	lab4WaitForBob = semcreate(0);
	waitForBobAndAlice = semcreate(0);

	resume(create(ProcessAlice, 1024, 20, "alice", 1, 1));
	resume(create(ProcessBob, 1024, 20, "bob", 1, 2));
	signaln(lab4semaphore, 3);
	
	wait(waitForBobAndAlice);
	wait(waitForBobAndAlice);

	return 0;
}


void PrintMessage(char* message)
{
	wait(lab4semaphore);
	kprintf("%s\n", message);
	signal(lab4semaphore);
}

void ProcessAlice()
{
	wait(lab4semaphore);
	PrintMessage("My first statement appears before Bob’s second statement.");
	signal(lab4WaitForAlice);
	wait(lab4WaitForBob);
	PrintMessage("This is Alice’s second statement.");
	signal(waitForBobAndAlice);
}

void ProcessBob()
{
	wait(lab4semaphore);
	PrintMessage("My first statement appears before Alices’s second statement.");
	signal(lab4WaitForBob);
	wait(lab4WaitForAlice);
	PrintMessage("This is Bob’s second statement.");
	signal(waitForBobAndAlice);
}