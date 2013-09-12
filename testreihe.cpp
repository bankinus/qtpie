
#include <iostream>

#include "Chain.h"
#include "tests.h"
#include "queues.h"


#define NUMBA 1<<20

using namespace std;

int main(){
	
	long time;

//test_mpmc erstellen


//blocking queue


	SpinQueue *spin1 = new SpinQueue();
	Test_mpmc c1(spin1, 5, NUMBA);
	cout << "test msmc mit spinqueue beginnt" << endl;
	time = c1.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

	MutexQueue *mut1 = new MutexQueue();
	Test_mpmc c6(mut1, 5, NUMBA);
	cout << "test msmc mit mutexqueue beginnt" << endl;
	time = c6.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

	TLMutexQueue *tlm1 = new TLMutexQueue();
	Test_mpmc c7(tlm1, 5, NUMBA);
	cout << "test msmc mit tlmqueue beginnt" << endl;
	time = c7.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

	TLSpinQueue *tls1 = new TLSpinQueue();
	Test_mpmc c8(tls1, 5, NUMBA);
	cout << "test msmc mit tlsqueue beginnt" << endl;
	time = c8.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;


//nonblocking queues


	MSQueue *msq1 = new MSQueue();
	Test_mpmc c2(msq1, 5, NUMBA);
	cout << "test msmc mit msqueue beginnt" << endl;
	time = c2.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
 
/*
	WnbsQueue *wq1 = new WnbsQueue();
	Test_mpmc c3(wq1, 1, NUMBA);
	cout << "test msmc mit woschqueue beginnt" << endl;
	time = c3.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
*/

	MPSCQueue *mpq1 = new MPSCQueue();
	Test_mpmc c4(mpq1, 5, NUMBA);
	cout << "test msmc mit mpscqueue beginnt" << endl;
	time = c4.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

/*
	//transaction queue

	TransQueue *trans1 = new TransQueue();
	Test_mpmc c5(trans1, 5, NUMBA);
	cout << "test msmc mit transqueue beginnt" << endl;
	time = c5.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;


	TLTransQueue *tlt1 = new TLTransQueue();
	Test_mpmc c9(tlt1, 5, NUMBA);
	cout << "test msmc mit tltqueue beginnt" << endl;
	time = c9.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
*/


//test_round erstellen

//blocking queue


	SpinQueue *spin2 = new SpinQueue();
	Test_round t1(spin2,20,5,NUMBA);
	cout << "test round mit spinqueue beginnt" << endl;
	time = t1.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

	MutexQueue *mut2 = new MutexQueue();
	Test_round t6(mut2,20,5,NUMBA);
	cout << "test round mit mutexqueue beginnt" << endl;
	time = t6.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

	TLMutexQueue *tlm2 = new TLMutexQueue();
	Test_round t7(tlm2,20, 5, NUMBA);
	cout << "test round mit tlmqueue beginnt" << endl;
	time = t7.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

	TLSpinQueue *tls2 = new TLSpinQueue();
	Test_round t8(tls2,20,5, NUMBA);
	cout << "test round mit tlsqueue beginnt" << endl;
	time = t8.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

//nonblocking queues

	MSQueue *msq2 = new MSQueue();
	Test_round t2(msq2,20, 5, NUMBA);
	cout << "test round mit msqueue beginnt" << endl;
	time = t2.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

/*
	WnbsQueue *wq2 = new WnbsQueue();
	Test_round t3(wq2,20, 1, NUMBA);
	cout << "test round mit woschqueue beginnt" << endl;
	time = t3.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
*/

/*
	//transaction queue

	TransQueue *trans2 = new TransQueue();
	Test_round t5(trans1,20, 5, NUMBA);
	cout << "test round mit transqueue beginnt" << endl;
	time = t5.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;

	TLTransQueue *tlt2 = new TLTransQueue();
	Test_round t9(tlt2, 20, 5, NUMBA);
	cout << "test round mit tltqueue beginnt" << endl;
	time = t9.starttest();
	cout << "Zeit benoetigt: " << time << "ms" << endl;
*/


}
