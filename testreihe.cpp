
#include <iostream>

#include "test_round.h"
#include "Chain.h"
#include "simplequeue.h"
#include "WnbsQueue.h"
#include "MPSCQueue.h"
#include "msqueue.h"

#define NUMBA 1<<30

using namespace std;

int main(){
	

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
	long time;
//	Test_round t1(q1,q1,0,20,5,200);

	Test_round t2(msq1,20,1,NUMBA);

	Test_round t3(wq1,20,1, NUMBA);

//	Test_round t4(q5,q5,0,20,5,200);

	//starten



//	t2.starttest_oneway();
//	t3.starttest_twoways(3);
	cout << "test msqueue beginnt" << endl;
	time = t2.starttest_oneway();


	cout << "Zeit benoetigt: " << time << "ms" << endl;
	cout << "test wosch beginnt" << endl;

	time = t3.starttest_oneway();
	cout << "Zeit benoetigt: " << time << "ms" << endl;


}
