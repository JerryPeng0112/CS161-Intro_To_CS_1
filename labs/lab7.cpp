#include <sys/time.h>
#include <cstdlib>
#include <iostream>
using namespace std;
void timing_it(int iteration);
void fabonacci_it(int iteration);
void timing_re(int iteration);
int fabonacci_re(int iteration);
int main() {
	timing_it(1);
	timing_it(5);
	timing_it(15);
	timing_it(25);
	timing_it(45);
	timing_re(1);
	timing_re(5);
	timing_re(15);
	timing_re(25);
	timing_re(45);
	return 0;
}
void timing_it(int iteration){
	typedef struct timeval time;
	time stop, start;
	gettimeofday(&start, NULL);
	fabonacci_it(iteration);
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;
}
void fabonacci_it(int iteration){
	if(iteration == 1){
		cout << "0 " << endl;
	}
	else if(iteration == 2){
		cout << "0 1 " << endl;
	}else{
		long a = 0, b = 1, c;
		cout << a << " " << b << " ";
		for(int i = 3; i <= iteration; i++){
			c = a + b;
			cout << c << " ";
			a = b; b = c;
		}
		cout << endl;
	}
}
void timing_re(int iteration){
	typedef struct timeval time;
	time stop, start;
	gettimeofday(&start, NULL);
	cout << fabonacci_re(iteration);
	cout << endl;
	gettimeofday(&stop, NULL);
	if(stop.tv_sec > start.tv_sec)
		cout << "Seconds: " << stop.tv_sec-start.tv_sec << endl;
	else
		cout << "Micro: " << stop.tv_usec-start.tv_usec << endl;
}
int fabonacci_re(int iteration){
	long value;
	if(iteration == 1){
		value = 0;
		return value;
	}
	else if(iteration == 2){
		value = 1;
		return value;
	}
	else{
		value = fabonacci_re(iteration-1)+fabonacci_re(iteration-2);
		return value;
	}
}
/* Recursion takes way longer than iteration when number goes bigger */