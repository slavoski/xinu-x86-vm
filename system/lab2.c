#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include "../lib/libxc/strlen.c"
#include "../include/lab2.h"

int pidWidth = 7;
int namWidth = 15;
int keyWidth = 15;
int nxtWidth = 7;
int prvWidth = 7;
int tableWidth;

sid32 lab2semaphore;
pid32 m2pid;

void PrintNumbers()
{
	int num = 0;

	for (; num <= 2000; ++num)
	{
		printf("%d ", num);
		wait(lab2semaphore);
	}
	kill(m2pid);
}

void PrintSentence()
{
	while (1)
	{
		printf("I am running\n");
		signaln(lab2semaphore, 5);
	}
	
}

void lab2Process(int process)
{
	tableWidth = pidWidth + namWidth + keyWidth + nxtWidth + prvWidth - 3;
	signal(lab2semaphore);
	while (1);
}

void Lab2Code()
{
	lab2semaphore = semcreate(20);
	//printf("Lab2 Code\n");
	//resume(create(lab2Process, 1024, 20, "pro1", 1, 1));
	//wait(lab2semaphore);
	//resume(create(lab2Process, 1024, 20, "pro2", 1, 2));
	//wait(lab2semaphore);
	//resume(create(PrintProcessQueueTable, 1024, 20, "pro3", 0));

	resume(create(PrintNumbers, 1024, 30, "Print Num", 0));
	m2pid = create(PrintSentence, 1024, 20, "Print Sent", 0);
	resume(m2pid);
}

void PrintHorizontalLines(int numberOfLines)
{
	int i = 0;
	for (; i < numberOfLines - 1; ++i)
	{
		printf("-");
	}
	printf("|");
}

void PrintHorizontalDivider()
{
	printf("|");
	PrintHorizontalLines(tableWidth - 2);
	printf("\n");
}

void PrintHeaderCentered(char* data, int totalSize)
{
	int dataSize = strlen(data);
	if (dataSize < totalSize)
	{
		int padding = (totalSize - dataSize - 2) / 2;
		printf("%*s%s", padding, "", data);

		if (padding % 2 == 0)
			padding -= 1;

		printf("%*s|", padding);
	}
	else
	{
		printf("%s|", data);
	}
}

void PrintDataRight(char* data, int totalSize)
{
	int dataSize = strlen(data);
	if (dataSize < totalSize)
	{
		int padding = (totalSize - dataSize - 2);
		printf("%*s%s|", padding, "", data);
	}
	else
	{
		printf("%s|", data);
	}
}

void PrintHeader()
{
	PrintHorizontalDivider();
	printf("|");
	PrintHeaderCentered("QueueTable", tableWidth);
	printf("\n");
	PrintHorizontalDivider();

	PrintPIDColumn();
	PrintNamColumn();
	PrintKeyColumn();
	PrintNxtColumn();
	PrintPrvColumn();
	printf("\n");

	PrintBrokenUpDivider();
}

void PrintProcessQueueTable()
{
	PrintHeader();
	PrintProcesses();
}

void PrintPIDColumn()
{
	printf("|");
	PrintHeaderCentered("PID", pidWidth);
}

void PrintNamColumn()
{
	PrintHeaderCentered("NAM", namWidth);
}

void PrintKeyColumn()
{
	PrintHeaderCentered("Key", keyWidth);
}

void PrintNxtColumn()
{
	PrintHeaderCentered("NXT", nxtWidth);
}

void PrintPrvColumn()
{
	PrintHeaderCentered("PRV", prvWidth);
}

void PrintBrokenUpDivider()
{
	printf("|");
	PrintHorizontalLines(pidWidth - 1);
	PrintHorizontalLines(namWidth - 1);
	PrintHorizontalLines(keyWidth - 1);
	PrintHorizontalLines(nxtWidth - 1);
	PrintHorizontalLines(prvWidth - 1);
	printf("\n");
}

void PrintProcesses()
{
	//int sizeOfArray = sizeof(queuetab) / sizeof(queuetab[0]);
	int i = 0;
	char data[20];
	for (; i < NQENT; ++i)
	{
		if (queuetab[i].qkey == 0 && queuetab[i].qnext == 0)
			break;

		printf("|");

		sprintf(data, "%d", i);
		PrintDataRight(data, pidWidth);
		PrintDataRight(proctab[i].prname, namWidth);

		sprintf(data, "%d", queuetab[i].qkey);
		PrintDataRight(data, keyWidth);

		sprintf(data, "%d", queuetab[i].qnext);
		PrintDataRight(data, nxtWidth);

		sprintf(data, "%d", queuetab[i].qprev);
		PrintDataRight(data, prvWidth);

		printf("\n");
		PrintBrokenUpDivider();
	}

	printf("|");
	PrintHeaderCentered("uninitialized ", tableWidth);
	printf("\n");
	PrintBrokenUpDivider();

	printf("|");
	PrintDataRight("99", pidWidth);
	PrintDataRight("", namWidth);
	PrintDataRight("0", keyWidth);
	PrintDataRight("0", nxtWidth);
	PrintDataRight("0", prvWidth);

	printf("\n");
	PrintHorizontalDivider();
}