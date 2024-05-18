#include <xinu.h>

pid32 process1;
pid32 process2;

void forever()
{
	while (1);
	kprintf("Low Priority Process Ran\n");
}

void Lab6(int processToRun)
{
	process1 = create(forever, 1024, 20, "process1", 0);
	process2 = create(forever, 1024, 20, "process2", 0);

	int i = 0;
	for (; i < 10; ++i)
	{
		sendk(process1, i);
	}

}