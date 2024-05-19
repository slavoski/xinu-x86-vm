#include <xinu.h>
#include <stdio.h>

shellcmd xsh_lab6(int nargs, char* args[])
{
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tSends and Receives Messages for Current Process\n");
		printf("Options:\n");
		printf("\t1 {Enter A Number between 1 - 25}\t Send X random messages\n");
		printf("\t2\t Receive %d messages\n", NMESSAGES);
		printf("\t--help\t display this help and exit\n");
		return 0;
	}

	if (nargs > 3 || nargs == 1) {
		fprintf(stderr, "%s:Incorrect arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

	int argument1 = atoi(args[1]);
	int argument2 = 1;
	if (argument1 == 1)
	{
		argument2 = atoi(args[2]);
		if (argument2 < 1)
			argument2 = 1;
		else if (argument2 > 25)
			argument2 = 25;
	}

	Lab6(argument1, argument2);

	return 0;
}