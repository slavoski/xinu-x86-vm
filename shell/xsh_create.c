#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// xsh_create - Shell command to create process with user specified priority

shellcmd xsh_create(int nargs, char *args[])   {

    int32 user_enter;
    pid32 testpid;

    if (nargs == 1)  {
        user_enter = 20;
    }

    else if (nargs == 2)    {
        user_enter = atoi(args[1]);
    }

    testpid = create(runforever, 1024, user_enter, "Test", 0);
    resume(testpid);
    return 0;
}