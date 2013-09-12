#ifndef MUTEX_QUEUE_H
#define MUTEX_QUEUE_H

#include "config.h"
#include "queue.h"
#include "Chain.h"
#include <mutex>

#include <iostream>

class MutexQueue : public Queue {
	private:
    Chain *head;
	uint8_t paddingh[CACHE_ALIGN - sizeof(Chain*)];
    Chain * volatile *tail;
	uint8_t paddingt[CACHE_ALIGN - sizeof(Chain*)];

	mutex *mut;

	public:
	MutexQueue() INLINE_ATTR : head(0), tail(&head) {
		mut = new mutex();
	}

	void enqueue(Chain *chain) INLINE_ATTR
	{
		chain->next = 0;
		//lock or begin transaction;
		mut->lock();
			*tail = chain;
			tail = &chain->next;
		//unlock or end transaction;
		mut->unlock();
	}

	Chain* dequeue() INLINE_ATTR
	{
		Chain *out;

		//lock or begin transaction;
		mut->lock();
			if((out = head) && !(head = out->next))
			{
				tail = &head;
			}
		//unlock or end transaction;
		mut->unlock();

		return out;
	}
};

#endif
