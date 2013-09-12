
#include <iostream>

#include "test_round.h"
#include "test_mpmc.h"
#include "Chain.h"
#include "simplequeue.h"
#include "WnbsQueue.h"
#include "MPSCQueue.h"
#include "msqueue.h"
#include "spinqueue.h"


#define NUMBA 1<<20

using namespace std;

int main(){
	
	long time;

//test_mpmc erstellen


//blocking queue


	Spinqueue *spin1 = new Spinqueue();
	Test_mpmc c1(spin1, 5, NUMBA);
	cout << "test msmc mit spinqueue beginnt" << endl;
	time = c1.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;


//nonblocking queues
	


	MSQueue *msq1 = new MSQueue();
	Test_mpmc c2(msq1, 5, NUMBA);
	cout << "test msmc mit msqueue beginnt" << endl;
	time = c2.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
  
/*
	WnbsQueue *wq1 = new WnbsQueue();
	Test_mpmc c3(wq1, 5, NUMBA);
	cout << "test msmc mit woschqueue beginnt" << endl;
	time = c3.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
*/

	MPSCQueue *mpq1 = new MPSCQueue();
	Test_mpmc c4(mpq1, 5, NUMBA);
	cout << "test msmc mit mpscqueue beginnt" << endl;
	time = c4.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;



//test_round erstellen


//blocking queue


	Spinqueue *spin2 = new Spinqueue();
	Test_round t1(spin2,20,5,NUMBA);
	cout << "test round mit spinqueue beginnt" << endl;
	time = t1.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;


//nonblocking queues
  


	MSQueue *msq2 = new MSQueue();
	Test_round t2(msq2,20, 5, NUMBA);
	cout << "test round mit msqueue beginnt" << endl;
	time = t2.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
  

/*
	WnbsQueue *wq2 = new WnbsQueue();
	Test_round t3(wq2,20, 5, NUMBA);
	cout << "test round mit woschqueue beginnt" << endl;
	time = t3.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
*/


}
