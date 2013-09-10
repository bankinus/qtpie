#pragma once

#include <sched.h>
#include "config.h"

class Spinlock
{
	private:
    Spinlock(const Spinlock& copy); //do not copy
	volatile int lock_var;

	public:
	Spinlock()
	{
		__sync_lock_release(&lock_var);
	}

	bool tryLock()
	{
		return __sync_lock_test_and_set(&lock_var, 1) == 0;
	}

	void lock()
	{
		do
		{
			while(lock_var != 0)
			{
				//asm volatile
				//(
				//	"pause\n\t":::
				//);
				sched_yield();
			}
		}
		while(__sync_lock_test_and_set(&lock_var, 1));
	}

	void unlock()
	{
		__sync_lock_release(&lock_var);
	}
};
