
#include <iostream>

#include "test_round.h"
#include "simplequeue.h"
#include "Chain.h"
#include "msqueue.h"


using namespace std;

int main(){
	
	cout << "test" << endl;
	//queues erstellen
	MSQueue *q1 = new MSQueue();
	MSQueue *q2 = new MSQueue();

	//test_round erstellen
	Test_round t1(q1,q2,0,20,4,200);

	//starten
	t1.starttest();

}
