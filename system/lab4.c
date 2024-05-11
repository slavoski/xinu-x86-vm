#include <xinu.h>
#include <lab4.h>
#include <stdio.h>
#include <stdlib.h>

sid32 lab4semaphore;
sid32 lab4WaitForAlice;
sid32 lab4WaitForBob;
sid32 waitForBobAndAlice;

void Lab4()
{
	lab4semaphore = semcreate(0);
	lab4WaitForAlice = semcreate(0);
	lab4WaitForBob = semcreate(0);
	waitForBobAndAlice = semcreate(0);

	//srand(time(NULL));
	int process1Priority = rand() % (20 - 1) + 1;
	int process2Priority = rand() % (20 - 1) + 1;

	kprintf("\nProcess 1 priority: %d\nProcess 2 priority: %d\n\n", process1Priority, process2Priority);

	resume(create(ProcessAlice, 1024, process1Priority, "alice", 1, 1));
	resume(create(ProcessBob, 1024, process2Priority, "bob", 1, 2));
	signaln(lab4semaphore, 3);

	wait(waitForBobAndAlice);
	wait(waitForBobAndAlice);
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