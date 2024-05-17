#include <xinu.h>

sid32 semaphore;
sid32 finishedSemaphore;

void Process()
{
	while (1);
}

void Process1()
{
	kprintf("Low Priority Process Ran\n");
}

void Process2()
{
	sleep(5);
	kprintf("High Priority Process Ran\n");
	signal(finishedSemaphore);
}

void Process1Semaphore()
{
	kprintf("Low Priority Process Ran\n");
	signal(semaphore);
}

void Process2Semaphore()
{
	wait(semaphore);
	kprintf("High Priority Process Ran\n");
	signal(finishedSemaphore);
}



void class6(int processToRun)
{
	finishedSemaphore = semcreate(0);
	if (processToRun == 1)
	{
		create(Process, 1024, 20, "process1", 0);
		create(Process, 1024, 20, "process2", 0);
		create(Process, 1024, 20, "process3", 0);
	}
	else if(processToRun == 2)
	{
		resume(create(Process1, 1024, 20, "process1", 0));
		resume(create(Process2, 1024, 40, "process2", 0));
	}
	else if (processToRun == 3)
	{
		semaphore = semcreate(0);
		resume(create(Process1Semaphore, 1024, 20, "process1", 0));
		resume(create(Process2Semaphore, 1024, 40, "process2", 0));
	}

	wait(finishedSemaphore);
}