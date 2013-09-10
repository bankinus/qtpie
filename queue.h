#ifndef QUEUE_H
#define QUEUE_H

#include "Chain.h"
#include <iostream>

class Queue{
	public:
	virtual void enqueue(Chain* chain) {}
	virtual Chain* dequeue(){}

};

#endif
