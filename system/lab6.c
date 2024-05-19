#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

int firstTime = TRUE;
pid32 process1;

void forever()
{
	umsg32* messages = receivek();

	int i = 0;
	for (; i < NMESSAGES; ++i)
	{
		kprintf("Message %d: %d\n", i, messages[i]);
	}

	freemem(messages, NMESSAGES * sizeof(umsg32));
}

void Lab6(int processToRun, int numOfMessagesToSend)
{
	if (processToRun == 1)
	{
		kprintf("Send message to Process1 \n");
		process1 = create(forever, 1024, 10, "process1", 0);
		int i = 0;
		for (; i < numOfMessagesToSend; ++i)
		{
			sendk(process1, rand() % (120 - 20) + 20);
		}
	}
	else if (processToRun == 2)
	{
		kprintf("Receive Message From Process1 %d\n", process1);

		resume(process1);
	}
	kprintf("Process1 %d\n", process1);
}