/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendk(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* contents of message		*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];

	int i = 0;
	for (; i < 5; ++i)
	{
		if (prptr->prhasmsgs[i] == FALSE)
		{
			break;
		}
	}

	
	if ((prptr->prstate == PR_FREE) || i >= 5) {
		kprintf("Message %d failed\n", msg);
		restore(mask);
		return SYSERR;
	}

	kprintf("Message %d\n", i);

	prptr->prmsgs[i] = msg;		/* deliver message		*/
	prptr->prhasmsgs[i] = TRUE;		/* indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid, RESCHED_YES);
	}
	else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid, RESCHED_YES);
	}
	

	restore(mask);		/* restore interrupts */
	return OK;
}
