#ifndef TWOLOCK_TRANSACTION_QUEUE_H
#define TWOLOCK_TRANSACTION_QUEUE_H

#include "config.h"
#include "queue.h"
#include "Chain.h"
#include "trans.h"

#include <iostream>

class TLTransQueue : public Queue {
	private:
	Chain *head;
	uint8_t paddingh[CACHE_ALIGN - sizeof(Chain*)];
   	Chain *tail;
	uint8_t paddingt[CACHE_ALIGN - sizeof(Chain*)];

	Chain c;


	public:
	TLTransQueue() INLINE_ATTR {
		c = new Chain(0);
		head = &c;
		tail = &c;
	}

	void enqueue(Chain *chain) INLINE_ATTR volatile
	{
		chain->next = 0;
		
		//lock or begin transaction;
		XFAIL(lock1);
		XBEGIN(lock1);

			tail->next = chain;
			tail = chain;
		//unlock or end transaction;
		XEND();
	}

	Chain* dequeue() INLINE_ATTR volatile
	{
		Chain *out;
		Chain *newhead;
		

		XFAIL(lock2);
		newhead	= head->next;
		if (newhead == 0){
			return 0;
		}
		//lock or begin transaction;
		XBEGIN(lock2);
			head->data = newhead->data;
			out = head;
			head = newhead;
		//unlock or end transaction;
		XEND();
		return out;
	}
};

#endif
