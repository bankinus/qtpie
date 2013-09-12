#ifndef TRANS_QUEUE_H
#define TRANS_QUEUE_H

#include "config.h"
#include "queue.h"
#include "Chain.h"
#include "trans.h"

#include <iostream>

class TransQueue : public Queue {
	private:
    Chain *head;
	uint8_t paddingh[CACHE_ALIGN - sizeof(Chain*)];
    Chain * volatile *tail;
	uint8_t paddingt[CACHE_ALIGN - sizeof(Chain*)];

	public:
	TransQueue() INLINE_ATTR : head(0), tail(&head) {}

	void enqueue(Chain *chain) INLINE_ATTR
	{
		chain->next = 0;
		//lock or begin transaction;
		XFAIL(lock1);
		XBEGIN(lock1);
			*tail = chain;
			tail = &chain->next;
		//unlock or end transaction;
		XEND();
	}

	Chain* dequeue() INLINE_ATTR
	{
		Chain *out;

		//lock or begin transaction;
		XFAIL(lock2);
		XBEGIN(lock2);
			if((out = head) && !(head = out->next))
			{
				tail = &head;
			}
		//unlock or end transaction;
		XEND();
		return out;
	}
};

#endif
