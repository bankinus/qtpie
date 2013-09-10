#ifndef __CHAIN_H__
#define __CHAIN_H__
#include "cpointer.h"


class Chain {
public:
	Chain() {} 
	Chain(Chain* next) : next(next) { }
	union
	{
		Chain* volatile next;
		CPointer<Chain> cnext;
	};
};
#endif
