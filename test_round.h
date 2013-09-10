/* Test fuer eine oder mehrere Queues.
Jede Threadinstanz fuehr dequeue auf einer Queue aus,
und fuehrt daraufhin mit dem entnommenen Objekt eine
enqueue Operation auf der anderen Queue aus.
Die Queues koennen identisch sein.

dq muss zu beginn mit Daten gefuellt sein.
*/

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include "queue.h"	//selbst bauen, hier mus class Queue definiert sein
#include "Chain.h"



using namespace std;

class Test_round{

public:
	Queue* nq;	//Queue to enqueue
	Queue* dq;	//Queue to dequeue
	int threads;
	int ops;

	Test_round(Queue *nq, Queue *dq, int nq_inhalt, int dq_inhalt, int threads, int ops) : nq(nq), dq(dq), threads(threads), ops(ops) {	//zwei Queues
		//queues fuellen mit entprechender anzahl an elementen

		Chain* chains = new Chain[nq_inhalt+dq_inhalt]();
		
		for(int i=0; i<nq_inhalt; i++){
			chains[i]= Chain();
			(*nq).enqueue(&chains[i]);
		}

		for(int i=0; i<dq_inhalt; i++){
			chains[nq_inhalt+i]= Chain();
			(*dq).enqueue(&chains[nq_inhalt+i]);
		}
	}
/*
	Test_round(Queue<lib::adt::Chain> nq, Queue<lib::adt::Chain> dq, int dq_inhalt, int threads, int ops) {
		Test_round(nq,dq,0,dq_inhalt,threads,ops);
	}

	Test_round(Queue<lib::adt::Chain> q, int inhalt, int threads, int ops) {
		Test_round(q,q,0,inhalt,threads,ops);
	}			//eine Queue

*/
	static void go(int ops, Queue *nq, Queue *dq){
		//fuehre ops mal aus, je eine de- und enqueue op.
		for(int i=0; i<ops; i++){
			(*nq).enqueue((*dq).dequeue());
		}
	}



	long starttest(){
		//startet threads threads,
		//fuehre insgesamt ops en- und dequeue-Operationen durch.
		//liefert die benoetigte Zeit zurueck
		


		//calculate operations per thread
		int opt;
		int rest;	//anzahl an threads, die eine operation mehr machen

		opt = ops/threads;
		rest = ops%threads;

		//start treads
		thread* thrarray = new thread[threads]();
		int i;
		for (i=0; i<rest; i++){
			thrarray[i]= thread(go, opt+1, nq, dq);
		}
		for(;i<threads;i++){
			thrarray[i]= thread(go, opt, nq, dq);
		}

		//join threads
		for (i=0; i<threads; i++){
			thrarray[i].join();
		}


	}

	
};

	




