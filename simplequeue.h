#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

#include "config.h"
#include "queue.h"
#include "Chain.h"

#include <iostream>

class SimpleQueue : public Queue {
	private:
    Chain *head;
	uint8_t paddingh[CACHE_ALIGN - sizeof(Chain*)];
    Chain * volatile *tail;
	uint8_t paddingt[CACHE_ALIGN - sizeof(Chain*)];

	public:
	SimpleQueue() INLINE_ATTR : head(0), tail(&head) {}

	void enqueue(Chain *chain) INLINE_ATTR
	{
		chain->next = 0;

		//lock or begin transaction;
			*tail = chain;
			tail = &chain->next;
		//unlock or end transaction;
	}

	Chain* dequeue() INLINE_ATTR
	{
		Chain *out;

		//lock or begin transaction;
			if((out = head) && !(head = out->next))
			{
				tail = &head;
			}
		//unlock or end transaction;

		return out;
	}
};

#endif
