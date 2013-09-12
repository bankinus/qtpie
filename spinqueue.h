#ifndef SPINLOCK_QUEUE_H
#define SPINLOCK_QUEUE_H

#include "config.h"
#include "queue.h"
#include "Chain.h"
#include "spinlock.h"

#include <iostream>

class Spinqueue : public Queue {
	private:
    Chain *head;
	uint8_t paddingh[CACHE_ALIGN - sizeof(Chain*)];
    Chain * volatile *tail;
	uint8_t paddingt[CACHE_ALIGN - sizeof(Chain*)];

	Spinlock *qlock;

	public:
	Spinqueue() INLINE_ATTR : head(0), tail(&head) {
		nqlock = new Spinlock();
	}

	void enqueue(Chain *chain) INLINE_ATTR
	{
		chain->next = 0;
		//lock or begin transaction;
		qlock->lock();
			*tail = chain;
			tail = &chain->next;
		//unlock or end transaction;
		qlock->unlock();
	}

	Chain* dequeue() INLINE_ATTR
	{
		Chain *out;

		//lock or begin transaction;
		qlock->lock();
			if((out = head) && !(head = out->next))
			{
				tail = &head;
			}
		//unlock or end transaction;
		qlock->unlock();

		return out;
	}
};

#endif
