/* receivek.c - receive */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------
 *  receivek  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32* receivek(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent* prptr;		/* ptr to process' table entry	*/

	mask = disable();

	prptr = &proctab[currpid];

	umsg32* messages = (umsg32*)getmem(NMESSAGES * sizeof(umsg32));

	int i = 0;
	for (; i < NMESSAGES; ++i)
	{
		//If first entry is false we have no messages in array
		if (i == 0 && prptr->prhasmsgs[0] == FALSE) {
			kprintf("Wait For Message %d\n", i);
			prptr->prstate = PR_RECV;
			resched();		/* block until message arrives	*/
		}

		//now check each message to see if it is false
		//if not get the message
		if (prptr->prhasmsgs[i] != FALSE)
		{
			messages[i] = prptr->prmsgs[i];		/* retrieve message		*/
			prptr->prhasmsgs[i] = FALSE;	/* reset message flag		*/
		}
		//if so there are no new messages
		else
		{
			messages[i] = 0;
		}
	}

	restore(mask);
	return messages;
}