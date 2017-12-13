/*
THERE ARE BUGS IN THE FOLLOWING CODE.
*/
#include <iostream> //spelled iostream wrong

using namespace std; //forgot to put namespace

int main(){

	int x=3, y, num; // didnt declare integer num
	char myAnswer;
	bool again = true; //didnt declare boolean again
	y = x;
	cout << "y is set to: " << y << endl;

	cout << "Please input a number: ";
	cin >> y; // >> instead of <<
	again = true; // forgot semicolon
	while(again){
		if(x > y){
			cout << "X is greater than Y\n";
			cout << "would you like to input another number?" << endl; // forgot quotation mark for ouput string // << instead of >>
			cin >> again;
		} //forgot curly brace
		else{
			cout << "X is less than Y" << endl;
			cout << "would you like to input another number?" << endl; // << instead of >>
			cin >> again;
		}
	}
	for(x = 0; x < 10; x++) // x++ instead of x+1
		cout << x << endl;
	
	cout << "What number would you like to find the factorial for? " << endl;
	cin >> num; //forgot semicolon
	for(int x = num; x > 0; x--)
		x = x * x; 

	cout << "Are you enjoying cs161? (y or n) " << endl;
	cin >> myAnswer; // variable name wrong
	if(myAnswer == 'y') // variable name wrong, should be a char, == not =
		cout << "YAY" << endl;
	else
		cout << "YOU WILL SOON!" << endl;

	return 0;
} //forgot to close curly brace./
