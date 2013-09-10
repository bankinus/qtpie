#pragma once

#include "constants.h"

class IrqChain
{
	public:
	IrqChain *next;
	bool isqueued;
	void *arg;
	void (*epilogue)(void*);
	
	IrqChain() INLINE_ATTR : next(0), isqueued(false), arg(0), epilogue(0) {}
} __attribute__ ((aligned (CACHE_ALIGN)));

class IrqQueue
{
	private:
	IrqChain head;
	IrqChain *tail;

	public:
	IrqQueue() INLINE_ATTR : tail(&head) {}

	void enqueue(IrqChain *chain) INLINE_ATTR
	{
		chain->next = 0;

		IrqChain *last = tail;
		tail = chain;

		while(last->next)
		{
			last = last->next;
		}

		last->next = chain;


		//simpler implementation:
		//chain->next = 0;
		//tail->next = chain;
		//tail = chain;
	}

	IrqChain* removeAll() INLINE_ATTR
	{
		IrqChain *out = head.next;
		if(out == 0) return 0;

		head.next = 0;
		tail = &head;

		return out;
	}

} __attribute__ ((aligned (CACHE_ALIGN)));
