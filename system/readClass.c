#include <xinu.h>

void readClass(int value)
{
	if (value != 0)
	{
		if (value % 2 == 0)
		{
			kprintf("Value is even! %d\n", value);
		}
		else
		{
			kprintf("Value is odd! %d\n", value);
		}
	}
	else
	{
		kprintf("Not a valid number! %d\n", value);
	}
}