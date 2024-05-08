#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void CreateProcess()
{
	kprintf("%d\n", getpid());
}

int CheckValue(int value)
{
	if (value == 0)
	{
		value = 20;
	}

	return value;
}

shellcmd xsh_class5(int nargs, char* args[])
{
	pid32 processOne;
	pid32 processTwo;
	pid32 processThree;

	int value1 = 0;
	int value2 = 0;
	int value3 = 0;

	switch (nargs)
	{
	case 4:
		value1 = atoi(args[3]);
		kprintf("Value 3: %d\n", value1);
	case 3:
		value2 = atoi(args[2]);
		kprintf("Value 2: %d\n", value2);
	case 2:
		value3 = atoi(args[1]);
		kprintf("Value 1: %d\n", value3);
		break;
	default:
		fprintf(stderr, "%s: invalid arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
		break;
	}

	processOne = create(CreateProcess, 1024, CheckValue(value3), "pro1", 1, 1);
	processTwo = create(CreateProcess, 1024, CheckValue(value2), "pro2", 1, 1);
	processThree = create(CreateProcess, 1024, CheckValue(value1), "pro3", 1, 1);

	resume(processOne);
	resume(processTwo);
	resume(processThree);

	return 0;
}