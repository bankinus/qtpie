#ifndef QUEUE_H
#define QUEUE_H

#include "Chain.h"

class Queue{
	public:
	virtual void enqueue(Chain* chain) {}
	virtual Chain* dequeue(){}

};

#endif
