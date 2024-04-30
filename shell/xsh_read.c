#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

shellcmd xsh_read(int nargs, char* args[])
{
	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

	int value = atoi(args[1]);

	//if (value != 0)
	//{
	//	if (value % 2 == 0)
	//	{
	//		kprintf("Value is even! %d\n", value);
	//	}
	//	else
	//	{
	//		kprintf("Value is odd! %d\n", value);
	//	}
	//}
	//else
	//{
	//	kprintf("Not a valid number! %d\n", value);
	//}

	readClass(value);

	return 0;
}