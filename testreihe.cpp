
#include <iostream>

#include "test_round.h"
#include "simplequeue.h"
#include "Chain.h"
#include "MPSCQueue.h"


using namespace std;

int main(){
	
	cout << "test" << endl;
	//queues erstellen
	SimpleQueue *q1 = new SimpleQueue();
	SimpleQueue *q2 = new SimpleQueue();

	//test_round erstellen
	Test_round t1(q1,q2,0,20,4,200);

	//starten
	t1.starttest();

}
