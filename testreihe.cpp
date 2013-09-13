
#include <iostream>

#include "Chain.h"
#include "tests.h"
#include "queues.h"


//#define WOSCH
//#define HASWELL



using namespace std;

#define testround(Type, elements, threads, ops) { \
	long time;	\
	Type *queue = new Type();	\
	Test_round t(queue,elements,threads,ops);	\
	cout << "test round mit "<< #Type <<" beginnt. \tThreads: " << threads << "\tOperationen: " << ops << "\tElemente zu Beginn: " << elements << endl;	\
	time = t.starttest();	\
	cout << "Zeit benoetigt: " << time << "\tms" << endl;	\
	t.cleanup();	\
	delete queue;	\
}

#define testmpsc(Type, threads, ops) {	\
	long time;	\
	Type *queue = new Type();	\
	Test_mpmc t(queue,threads,ops);	\
	cout << "test mpsc mit\t"<< #Type <<" beginnt.\tProducers: " << threads << "\tOperationen: " << ops << endl;	\
	time = t.starttest();	\
	cout << "Zeit benoetigt: " << time << "ms" << endl;	\
	t.cleanup();	\
	delete queue;	\
}


int main(){
	


//test_round erstellen

//blocking queue

	long elements;
	int threads;
	long ops;
	

	elements = 4;
	threads= 2;
	ops = 1<<25;

	testround(SpinQueue, elements, threads, ops);
	testround(MutexQueue, elements, threads, ops);
	testround(TLMutexQueue, elements, threads, ops);
	testround(TLSpinQueue , elements, threads, ops);
	testround(MSQueue , elements, threads, ops);
#ifdef WOSCH
	testround(WnbsQueue , elements, threads, ops);
#endif
#ifdef HASWELL
	testround(TransQueue , elements, threads, ops);
	testround(TLTransQueue , elements, threads, ops);
#endif


	ops = 1<<20;

	testmpsc(SpinQueue, threads, ops);
	testmpsc(MutexQueue, threads, ops);
	testmpsc(TLMutexQueue, threads, ops);
	testmpsc(TLSpinQueue , threads, ops);
	testmpsc(MSQueue , threads, ops);
	testmpsc(MPSCQueue, threads, ops);
#ifdef WOSCH
	testmpsc(WnbsQueue,  threads, ops);
#endif
#ifdef HASWELL
	testmpsc(TransQueue, threads, ops);
	testmpsc(TLTransQueue , threads, ops);
#endif

}
