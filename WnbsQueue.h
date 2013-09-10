#ifndef __LIB_ADT_WNBSQUEUE_H__
#define __LIB_ADT_WNBSQUEUE_H__

#include "Chain.h"
#include "queue.h"

#ifndef CAS
	#define CAS(p, o, n) \
		__sync_bool_compare_and_swap((uintptr_t*) (p), (uintptr_t) (o), (uintptr_t) (n))

#endif


typedef Chain Chain_p;

class WnbsQueue : public Queue {
	Chain head;
	Chain* tail;
	static const uint32_t ABA_MASK = 0x3;
public:
	WnbsQueue() { head.next = 0; tail = &head; }
	void enqueue(Chain_p *item);
	Chain_p* dequeue();
	static Chain *abaIndex (Chain_p* item) {
		return (Chain *)((intptr_t)item & ~ABA_MASK);
	}

private: 
	static Chain_p* aba_wheel (Chain_p* item) {
		return (Chain_p *)((intptr_t)item ^ ABA_MASK == 1 ? 1 : 0);
	}

};


void WnbsQueue::enqueue(Chain_p *item) {
	Chain* last;
	Chain* self;

	// assert(this && aba_index(item));

	item->next = aba_wheel(item);	/* item becomes new tail resp. next last */

	do {
		self = (last = this->tail)->next;		/* draw copies as needed */
	} while (!CAS(&this->tail, last, item));

	if (!CAS(&last->next, self, item)) {		/* last removed by fetch */
		this->head.next = item;			/* item becomes new head */
	}
}

Chain_p* WnbsQueue::dequeue() {
	Chain_p* node;
	Chain_p* next;

	do if (abaIndex((node = this->head.next)) == 0) return 0;
	while (!CAS(&this->head.next, node, ((next = abaIndex(node)->next) == node ? 0 : next)));

	if (next == node) {	/* last element just removed, be careful */
		if (!CAS(&node->next, next, 0)) this->head.next = abaIndex(node)->next;
		else CAS(&this->tail, &node->next, &this->head);
	}

	return node;
}

#endif
