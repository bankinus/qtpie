#ifndef __CHAIN_H__
#define __CHAIN_H__



class Chain {
public:
	Chain() {} 
	Chain(Chain* next) : next(next) { } 
	Chain* volatile next;
};
#endif
