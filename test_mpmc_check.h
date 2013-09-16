#ifndef TEST_MPSC_CKECK
#define TEST_MPSC_CHECK

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

class Test_mpmc_check{

public:
	Queue* q;		//Queue to enqueue
	Chain* beginchains;	//hieraus entnehmen producers ihre Daten
	Chain* endchains;	//hierhinein speichern consumer ihre Daten
	int prods;
	int cons;
	long ops;
	long indexprod;
	long indexcon;



	Test_mpmc_check(Queue *q, int producers, int consumers, long ops) : q(q), prods(producers), cons(consumers), ops(ops), indexprod(0), indexcon(0) {	
		//prodarray fuellen mit entprechender anzahl an elementen

		beginchains = new Chain[ops]();
		endchains = new Chain[ops]();
		
		for(uintptr_t i=0; i<ops; i++){
			beginchains[i]= Chain();
			beginchains[i].data = (void*)i;
//			cout << "constr:\t" << beginchains[i].data << "\ti: "<< i<< endl;
		}
			
	}

	Test_mpmc_check(Queue *q, int producers, long ops) : Test_mpmc_check(q, producers, 1, ops) {};


	void cleanup(){
		delete[] beginchains;
		delete[] endchains;
	}

	static void go_cons(long ops, long &index, Queue *q, Chain *chains){
		//entfernt daten aus q
		//consumer

		long i;
		Chain *c;
		while(index<ops){
			i = FAA(&index,1);
			
			if (i<ops){
				while (!(c = q->dequeue()));
				chains[i].data = c->data;	//Pointer??
//				cout << "cons:\t" << (uintptr_t) c[i].data << "\ti: "<< i<< endl;

			}
		}
	}

	static void go_prod(long ops, long &index, Queue *q, Chain *chains){
		//legt daten von chains in q
		//producer

		long i;
		while(index<ops){
			i = FAA(&index,1);
			if (i<ops)
//				cout << "prod:\t" << (uintptr_t) chains[i].data << "\ti: "<< i<< endl;
				q->enqueue(&chains[i]);

		}
	}

	int check(){
		int *checks = new int[ops];
		int errors = 0;
		for (int i=0; i< ops; i++){
			checks[i] = 0;
		}
		for (int i=0; i< ops; i++){
			if(!((uintptr_t) endchains[i].data > ops)){
				checks[(uintptr_t) endchains[i].data] += 1;
			}
		}
		for (int i=0; i< ops; i++){
			if (checks[i] != 1)
				++errors;
		}	
		return errors;
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
		for (i=0; i<cons; i++){
			thrarraycons[i]= thread(go_cons, ops, std::ref(indexcon), q, endchains);
		}

		//start producing threads
		for (i=0; i<prods; i++){
			thrarrayprods[i]= thread(go_prod, ops, std::ref(indexprod), q, beginchains);
		}

		//join threads
		for (i=0; i<prods; i++){
			thrarrayprods[i].join();
		}

		for (i=0; i<cons; i++){
			thrarraycons[i].join();
		}
		delete[] thrarraycons;
		delete[] thrarrayprods;
		return check();

	}
};

#endif	




