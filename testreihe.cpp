
#include <iostream>

#include "test_round.h"
#include "Chain.h"
#include "simplequeue.h"
#include "WnbsQueue.h"
#include "MPSCQueue.h"

using namespace std;

int main(){
	
	cout << "test beginnt" << endl;
	//queues erstellen
	SimpleQueue *q1 = new SimpleQueue();
	SimpleQueue *q2 = new SimpleQueue();
	
	WnbsQueue *q3 = new WnbsQueue();
	WnbsQueue *q4 = new WnbsQueue();

	MPSCQueue *q5 = new MPSCQueue();
	MPSCQueue *q6 = new MPSCQueue();

	//test_round erstellen
//	Test_round t1(q1,q1,0,20,5,200);
	Test_round t2(q3,q3,0,20,5,16000);
//	Test_round t3(q3,q4,0,20,6,200);
//	Test_round t4(q5,q5,0,20,5,200);

	//starten

	double time;

//	t2.starttest_oneway();
//	t3.starttest_twoways(3);
	time = t2.starttest_oneway();

	cout << "Zeit benoetigt: " << time << "sec" << endl;


}
