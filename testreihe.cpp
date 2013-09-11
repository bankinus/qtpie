
#include <iostream>

#include "test_round.h"
#include "Chain.h"
<<<<<<< HEAD
#include "simplequeue.h"
#include "WnbsQueue.h"
#include "MPSCQueue.h"
=======
#include "msqueue.h"
>>>>>>> a04a12390e04d89340b72d9b22dbf0930855f67c

using namespace std;

int main(){
	
	cout << "test beginnt" << endl;
	//queues erstellen
	SimpleQueue *sq1 = new SimpleQueue();
	SimpleQueue *sq2 = new SimpleQueue();
	
	WnbsQueue *wq1 = new WnbsQueue();
	WnbsQueue *wq2 = new WnbsQueue();

	MPSCQueue *mpq1 = new MPSCQueue();
	MPSCQueue *mpq2 = new MPSCQueue();

	MSQueue *msq1 = new MSQueue();
	MSQueue *msq2 = new MSQueue();

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
