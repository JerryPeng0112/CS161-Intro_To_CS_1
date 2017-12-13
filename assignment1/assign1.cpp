#include <iostream>
using namespace std;
#include <math.h>       /* cos */
#include <limits.h>

#define PI 3.14159265

int main (){
	double res1, res2, res3, res4, res5, res6, res7;
	res1 = cos(2*PI/3);
	res2 = 2*sin(2*PI/3);
	res3 = tan(-3*PI/4);
	res4 = log10 (55);
	res5 = log (60);
	res6 = log (15)/log(2);
	res7 = log (40)/log(4);
	cout << "cosine of two pi over 3 is: " << res1 << endl;
	cout << "2 times sine of two pi over 3 is: " << res2 << endl;
	cout << "tangend of negative 3 pi over 4 is: " << res3 << endl;
	cout << "log 55 base 10 is: " << res4 << endl;
	cout << "natural log of 60 is: " << res5 << endl;
	cout << "log 15 base 2 is: " << res6 << endl;
	cout << "log 40 base 4 is: " << res7 << endl;
	double x1,x2,x3;
	x1 = 1;
	x2 = 10;
	x3 = 100;
	cout << "3 to the power of sin(x) when x is 1: "<< pow(3,sin(x1)) << endl;
	cout << "3 to the power of sin(x) when x is 10: "<< pow(3,sin(x2)) << endl;
	cout << "3 to the power of sin(x) when x is 100: "<< pow(3,sin(x3)) << endl;
	cout << "log of x square plus 1 with base 2 when x is 1: "<< log(pow(x1,2)+1)/log(2) << endl;
	cout << "log of x square plus 1 with base 2 when x is 10: "<< log(pow(x2,2)+1)/log(2) << endl;
	cout << "log of x square plus 1 with base 2 when x is 100: "<< log(pow(x3,2)+1)/log(2) << endl;
	cout << "USHRT_MAX: " << USHRT_MAX << endl;
	cout << "SHRT_MAX: " << SHRT_MAX << endl;
	cout << "SHRT_MIN: " << SHRT_MIN << endl;
	cout << "UINT_MAX: " << UINT_MAX << endl;
	cout << "INT_MAX: " << INT_MAX << endl;
	cout << "INT_MIN: " << INT_MIN << endl;
	cout << "ULONG_MAX: " << ULONG_MAX << endl;
	cout << "LONG_MAX: " << LONG_MAX << endl;
	cout << "LONG_MIN: " << LONG_MIN << endl;
	
	int intbit, shortbit, longbit;
	intbit = sizeof(int);
	shortbit = sizeof(short);
	longbit = sizeof(long);
	cout << "Maximum unsigned short integer: " << pow(2,shortbit*8)-1 << endl;
	cout << "Maximum signed short integer: " << pow(2,shortbit*8-1)-1 << endl;
	cout << "Minimum signed short integer: " << -pow(2,shortbit*8-1) << endl;
	cout << "Maximum unsigned integer: " << pow(2,intbit*8)-1 << endl;
	cout << "Maximum signed integer: " << pow(2,intbit*8-1)-1 << endl;
	cout << "Minimum signed integer: " << -pow(2,intbit*8-1) << endl;
	cout << "Maximum unsigned long integer: " << pow(2,longbit*8)-1 << endl;
	cout << "Maximum signed long integer: " << pow(2,longbit*8-1)-1 << endl;
	cout << "Minimum signed long integer: " << -pow(2,longbit*8-1) << endl;
}
