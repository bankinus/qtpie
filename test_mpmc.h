#ifndef TEST_MPSC
#define TEST_MPSC

/* Test fuer eine Queue.
Jede Threadinstanz fuehr enqueue auf der Queue aus,
ein einzelner thread entnimmt die Objekte wieder.
*/

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <ctime>
#include "queue.h"	//selbst bauen, hier mus class Queue definiert sein
#include "Chain.h"

#define FAA(p,v) __sync_fetch_and_add(p,v)

using namespace std;

class Test_mpmc{

public:
	Queue* q;	//Queue to enqueue
	Chain* beginchains;	//hieraus entnehmen producers ihre Daten
	Chain* endchains;	//hierhinein speichern consumer ihre Daten
	int prods;
	int cons;
	long ops;
	long indexprod;
	long indexcon;
	bool nodata;

	Test_mpmc(Queue *q, int producers, int consumers, long ops) : q(q), prods(producers), cons(consumers), ops(ops), indexprod(0), indexcon(0), nodata(0) {	
		//prodarray fuellen mit entprechender anzahl an elementen

		beginchains = new Chain[ops]();
		endchains = new Chain[ops]();
		
		for(int i=0; i<ops; i++){
			beginchains[i]= Chain();
		}
			
	}

	Test_mpmc(Queue *q, int producers, long ops) : q(q), prods(producers), cons(1), ops(ops), indexprod(0), indexcon(0), nodata(1) {	//single consumer	
			//prodarray fuellen mit entprechender anzahl an elementen

		beginchains = new Chain[ops]();
		
		for(int i=0; i<ops; i++){
			beginchains[i]= Chain();
		}
	}	

	void cleanup(){
		delete[] beginchains;
		if (!nodata)
			delete[] endchains;
	}

	static void go_cons(long ops, long &index, Queue *q, Chain *chains){
		//entfernt daten aus q
		//consumer

		long i;
		Chain *c;
		while(index<ops){
			i = FAA(&index,1);
			
			if (i<ops)
			while (!(c = q->dequeue()));
			chains[i] = c;	//Pointer??
		}
	}

	static void go_cons_nodata(long ops, long &index, Queue *q){
		//entfernt daten aus q
		//consumer

		long i;
		Chain *c;
		while(index<ops){
			i = FAA(&index,1);
	//		cout << "consindex: " << i <<endl;
			if (i<ops)
			while (!(c = q->dequeue())){
//				cout << "still trying" << endl;
			}
		}
	}

	static void go_prod(long ops, long &index, Queue *q, Chain *chains){
		//legt daten von chains in q
		//producer

		long i;
		while(index<ops){
			i = FAA(&index,1);
	//		cout << "prodindex: " << i <<endl;
			if (i<ops)
				q->enqueue(&chains[i]);
		}
	}



	long starttest(){
		//startet threads,
		//fuehre insgesamt ops enqueue-Operationen durch.
		//liefert die benoetigte Zeit zurueck

		//start treads
		thread* thrarraycons = new thread[cons]();
		thread* thrarrayprods = new thread[prods]();
		long i;

		//start consumer threads
		if (nodata){
			for (i=0; i<cons; i++){
				thrarraycons[i]= thread(go_cons_nodata, ops, std::ref(indexcon), q);
			}
		} else {
			for (i=0; i<cons; i++){
				thrarraycons[i]= thread(go_cons, ops, std::ref(indexcon), q, endchains);
			}
		}
		struct timespec begin;
		struct timespec end;
		clock_gettime(CLOCK_MONOTONIC, &begin);

		//start producing threads
		for (i=0; i<prods; i++){
			thrarrayprods[i]= thread(go_prod, ops, std::ref(indexprod), q, beginchains);
		}

		//join threads
		for (i=0; i<prods; i++){
			thrarrayprods[i].join();
//			i--; //endlosscheife
		}

		for (i=0; i<cons; i++){
			thrarraycons[i].join();
//			i--; //endlosscheife
		}

		clock_gettime(CLOCK_MONOTONIC, &end);
		time_t sec;
		long nsec;
		sec = end.tv_sec - begin.tv_sec;
		nsec = end.tv_nsec - begin.tv_nsec;
		nsec /= 1000000;
		sec *= 1000;

		delete[] thrarraycons;
		delete[] thrarrayprods;
		return sec+nsec;

	}
};

#endif	




