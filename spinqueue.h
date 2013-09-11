#ifndef SPINLOCK_QUEUE_H
#define SPINLOCK_QUEUE_H

#include "config.h"
#include "queue.h"
#include "Chain.h"
#include "spinlock.h"


class Spinqueue : public Queue {
	private:
    Chain *head;
	uint8_t paddingh[CACHE_ALIGN - sizeof(Chain*)];
    Chain * volatile *tail;
	uint8_t paddingt[CACHE_ALIGN - sizeof(Chain*)];

	Spinlock *nqlock;
	Spinlock *dqlock;

	public:
	Spinqueue() INLINE_ATTR : head(0), tail(&head) {
		nqlock = new Spinlock();
		dqlock = new Spinlock();
	}

	void enqueue(Chain *chain) INLINE_ATTR
	{
		chain->next = 0;

		//lock or begin transaction;
		nqlock->lock();
			*tail = chain;
			tail = &chain->next;
		//unlock or end transaction;
		nqlock->unlock();
	}

	Chain* dequeue() INLINE_ATTR
	{
		Chain *out;

		//lock or begin transaction;
		dqlock->lock();
			if((out = head) && !(head = out->next))
			{
				tail = &head;
			}
		//unlock or end transaction;
		dqlock->unlock();

		return out;
	}
};

#endif
