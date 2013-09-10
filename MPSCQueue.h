#ifndef __MPSCQUEUE_H__
#define __MPSCQUEUE_H__

#include "Chain.h"


#include "queue.h"


#ifndef CAS
	#define CAS(p, o, n) \
		__sync_bool_compare_and_swap((uintptr_t*) (p), (uintptr_t) (o), (uintptr_t) (n))
#endif


class MPSCQueue : public Chain {
	Chain** tail;
public:
	MPSCQueue() : Chain(0), tail((Chain**volatile)&next) { }
	void enqueue(Chain* item);
	Chain* dequeue();
	Chain* peek() const { return (Chain*) next; }
	ListIterator begin() {
		return ListIterator(const_cast<Chain*>(next), this);
	}
	Chain* remove(ListIterator& it);
};

inline void MPSCQueue::enqueue(Chain* item) {
	Chain** volatile last;
	item->next = 0;		/* make item last chain element */
	do {
		last = tail;
	} while (!CAS(&tail, last, &(item->next)));
	*last = item;		//CAS successful, so I can now link safely
	dLabel(MPSCenqueue);
}

inline Chain* MPSCQueue::dequeue() {
	Chain* volatile item;
	if ((item = next) && !(next = item->next)) {
		if (!CAS(&tail, &(item->next), &next)) {
			while(item->next == 0) { }
			next = item->next;
		}
	}
	return (Chain*)item;
}

inline Chain* MPSCQueue::remove(ListIterator& it) {
	Chain* volatile item = it.getElement();
	Chain** volatile prevLink = const_cast<Chain** volatile>(&(it.getPrevElement()->next));
	if ((item != 0) && !(*prevLink = item->next)) {
		if (!CAS(&tail, &(item->next), prevLink)) {
			while(item->next == 0) { }
			*prevLink = item->next;
		}
	}
	return (Chain*)item;
}

}

}

#endif
