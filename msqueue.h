#pragma once

#include "config.h"
#include "constants.h"
#include "queues/cpointer.h"
#include "queue.h"
#include "Chain.h"

#define T Chain

class MSQueue:Queue
{
	public:
    CPointer<T> head;
    CPointer<T> tail;
	T dummy;

	MSQueue() INLINE_ATTR {head.setPtr(&dummy); tail.setPtr(&dummy);}

	bool isEmpty() volatile INLINE_ATTR
	{
		for(;;)
		{
			//get local copies
			CPointer<T> chead = head;
			CPointer<T> ctail = tail;
			CPointer<T> next = chead.getPtr()->next;

			//this is important, check if copies are consistent
			if(unlikely(chead != head))
				continue;

			if(chead.getPtr() == ctail.getPtr())//only one element in the queue
			{
				return next.getPtr() == 0;
			}

			return false;
		}
	}

	void enqueue(T *chain) volatile INLINE_ATTR
	{
		chain->next.setCounter(chain->next.getCounter() + 1);//incrementing the counter may not be important... do it anyways
		chain->next.setPtr(0);//set next to 0, indicating the last element of the queue

		for(;;)
		{
			//get local copies
			CPointer<T> ctail = tail;
			CPointer<T> next = ctail.getPtr()->next;

			//this is important, check if copies are consistent
			if(unlikely(ctail != tail))
				continue;

			if(next.getPtr() == 0)//enqueueing at end of queue
			{
				CPointer<T> cnext(chain, next.getCounter() + 1);
				if(likely(CPointer<T>::CAS(&(ctail.getPtr()->next), next, cnext)))
				{
					//this is not needed in general, but in this system, leave it here
					CPointer<T> tnext(chain, ctail.getCounter() + 1);
					CPointer<T>::CAS(&(tail), ctail, tnext);
					//
					break;//successfully enqueued, done
				}

				continue;
			}

			//else tail is falling behind
			//advance it to next
			CPointer<T> tnext(next.getPtr(), ctail.getCounter() + 1);
			CPointer<T>::CAS(&(tail), ctail, tnext);
		}
	}

	T* dequeue() volatile INLINE_ATTR
	{
		for(;;)
		{
			//get local copies
			CPointer<T> chead = head;
			CPointer<T> ctail = tail;
			CPointer<T> next = chead.getPtr()->next;

			//this is important, check if copies are consistent
			if(unlikely(chead != head))
				continue;

			if(chead.getPtr() == ctail.getPtr())//only one element in the queue
			{
				if(next.getPtr() == 0)//only the dummy node, queue is empty
					return 0;

				//tail is falling behind, advance it, try again
				CPointer<T> tnext(next.getPtr(), ctail.getCounter() + 1);
				CPointer<T>::CAS(&(tail), ctail, tnext);
				continue;
			}

			//else there are elements in the queue try to advance head pointer
			CPointer<T> hnext(next.getPtr(), chead.getCounter() + 1);
			if(likely(CPointer<T>::CAS(&(head), chead, hnext)))
			{
				//here we successfully dequeued an element
				//the pointer is volatile because &(dummy)
				//is volatile too and they get compared later
				T * volatile outchain = chead.getPtr();

				//incrementing the counter may not be important... do it anyways
				outchain->next.setCounter(outchain->next.getCounter() + 1);
				outchain->next.setPtr(0);

				//if it is not the dummy node return element
				if(outchain != &(dummy))
				{
					return outchain;
				}

				//else enqueue dummy node and try again
				enqueue(outchain);
			}
		}
	}
} __attribute__ ((aligned (CACHE_ALIGN)));

