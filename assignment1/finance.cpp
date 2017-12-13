/**********************************************************************************
 ** Program Filename: finance.cpp
 ** Author: Tsewei Peng
 ** Date: 01/16/2016
 ** Description: A smart finance calculator that can calculate loan balance,
 ** continuously compounded interest, and future value, including comparison 
 ** user value.
 ** Input: selection for the type of calculator user wants to use, along with some 
 ** of the input for values for calculation
 ** Output: The result of the calculation along with the comparison between user's 
 ** goal and the actual result.
 **********************************************************************************/
#include <iostream>
#include <math.h>

#define e 2.71828182846                 /* Declare constant e */       
using namespace std;
int main(){
	cout << "Welcome to the Financial Calculator" << endl 
	<< "What would you like to calculate" << endl 
	<< "1 - Loan Balance" << endl 
	<< "2 - Continuously Compounded Interest" << endl 
	<< "3 - Future Value" << endl << "Selection: ";
	int selection;
	cin >> selection;
	if (selection == 1){
		double A,i,P,n,B,G;             
		/* Declare variable A,i,P,n,B,G for user input */
		cout << "You have chose to calculate Loan Balance" << endl << "What is the initial investment in dollars (eg.500): ";
		/* Prompt user for variable A,i,P,n,B,G for calculation */
		cin >> A;
		cout << "What is the interest rate per periods (as a decimal): ";
		cin >> i;
		cout << "What is the amount of each equal payment in dollars (eg.100): ";
		cin >> P;
		cout << "What is the number of periods at any given point: ";
		cin >> n;
		/* Calculate B based on the variables user provided */
		B = A * pow(1+i,n) - P/i*(pow(1+i,n)-1);
		/* Ask for user goal */
		cout << "What is your goal loan balance by the provided time: ";
		cin >> G;
		/* Out put result */
		cout << endl << "Your goal loan balance is $" << G << endl;
		cout << "The actual loan balance after " << P << " periods is $" << B << endl;
		/* Compare actual result and user goal */
		if(G>=B){
			cout << "You will meet your goal." << endl;
		}else{
			cout << "You will not meet your goal." << endl;
		}
	}else if (selection == 2){
		double P,r,t,A,G;
		/* Declare variable P,r,t,A,G for user input */
		cout << "You have chosen to calculate Continuously Compounded Interest." << endl << "What is the principal investment in dollars (eg. 500): ";
		/* Prompt user for variable P,r,t,A,G for calculation */
		cin >> P;
		cout << "What is the annual interest rate (as a decimal): ";
		cin >> r;
		cout << "How long in years will you be compounding: ";
		cin >> t;
		/* Calculate A based on the variables user provided */
		A = P * pow(e, r*t);
		/* Ask for user goal */
		cout << "What is your goal amount in dollars by the provided time: ";
		cin >> G;
		/* Compare actual result and user goal */
		cout << endl << "Your goal amount is $" << G << endl;
		cout << "The actual amount after " << t << " years is $" << A << endl;
		/* Compare actual result and user goal */
		if(G<=A){
			cout << "You will meet your goal." << endl;
		}else{
			cout << "You will not meet your goal." << endl;
		}

	}else{
		double C,r,n,F,G
	;		/* Declare variable C,r,n,F,G for user input */
		cout << "You have chosen to calculate Future Value." << "What is the starting cash flow in dollars (eg. 500): ";
		cin >> C;
		cout << "What is the rate of return (as a decimal): ";
		cin >> r;
		cout << "What is the number of periods: ";
		cin >> n;
		/* Calculate A based on the variables user provided */
		F = C * pow(1+r,n);
		/* Ask for user goal */
		cout << "What is your goal of future value in dollars by the provided time: ";
		cin >> G;
		/* Compare actual result and user goal */
		cout << endl << "Your goal future value is $" << G << endl;
		cout << "Tha actual future value after " << n << " periods is $" << F << endl;
		/* Compare actual result and user goal */
		if (G<=F){
			cout <<"You will meet your goal." << endl;
		}else{
			cout << "You will not meet your goal." << endl;
		}
	}
	return 0;
}
