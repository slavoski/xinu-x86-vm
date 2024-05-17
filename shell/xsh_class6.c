#include <xinu.h>
#include <stdio.h>

shellcmd xsh_class6(int nargs, char* args[])
{
	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

	int processToRun = atoi(args[1]);

	class6(processToRun);

	return 0;
}