/*********************************************************************
 ** Program Filename: grid.cpp
 ** Author: Tsewei Peng
 ** Date: 01/31/2016
 ** Description: This program prints the steps the rover needs to 
 ** 	take to reach from starting coordinate to ending coordinate in a 
 ** 	4-by-4 coordinate system.
 ** Input: Starting x and y coordinates, ending x and y coordinates.
 ** Output: The complete steps of the rover from starting position 
 ** to ending position step by step.
 *********************************************************************/ 
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void print_line(int xStart, int i, int yStart, int j); // function prototype
void find_path(int xS, int xE, int yS, int yE); // function prototype

/*********************************************************************
 ** Function: main()
 ** Description: The main function declares all the variable, prompts
 ** 	user for inputs, calls other functions, and in the end ask the 
 ** 	user if they want to restart, including all the error handling.
 ** Parameters: None
 ** Pre-Conditions: None
 ** Post-Conditions: Check if user still wants to restart, and exits
 ** 	only if user input "No" or "no".
 *********************************************************************/ 
int main(){
	bool restart = true;
	while(restart == true){
		string xStartS, yStartS, xEndS, yEndS; //declare string for user input
		int xStart, yStart, xEnd, yEnd; //declare integer for string conversion
		string userRestart; // declare string for prompting user to restart 
		/*
		 * Below is code for prompting user for starting x, y coordinates, 
		 * ending x, y coordinates, and error handling.
		 * First part: check if the input consists of all numbers.
		 * Second: if so, convert it into integer number.
		 * Third: check if the integer is in range, if not, the process 
		 * restarts.
		 */
		cout << "Starting x coordinate (from 0 to 3): ";
		cin >> xStartS;
		do {
			for(int i = 0; i < xStartS.length(); i++){
				if(!(xStartS.at(i) >= '0' && xStartS.at(i) <= '9' && xStartS.length() == 1)){
					cout << "Please enter an integer between 0 to 3: ";
					cin >> xStartS;
					i = -1;
				}
			}
			xStart = atoi(xStartS.c_str());
			if(xStart > 3){
				cout << "Please enter an integer between 0 to 3: ";
				cin >> xStartS;
			}
			else{
				break;
			}
		}while(1);
		cout << "Starting y coordinate (from 0 to 3): ";
		cin >> yStartS;
		do {
			for(int i = 0; i < yStartS.length(); i++){
				if(!(yStartS.at(i) >= '0' && yStartS.at(i) <= '9' && yStartS.length() == 1)){
					cout << "Please enter an integer between 0 to 3: ";
					cin >> yStartS;
					i = -1;
				}
			}
			yStart = atoi(yStartS.c_str());
			if(yStart > 3){
				cout << "Please enter an integer between 0 to 3: ";
				cin >> yStartS;
			}
			else{
				break;
			}
		}while(1);
		cout << "Ending x coordinate (from 0 to 3): ";
		cin >> xEndS;
		do {
			for(int i = 0; i < xEndS.length(); i++){
				if(!(xEndS.at(i) >= '0' && xEndS.at(i) <= '9' && xEndS.length() == 1)){
					cout << "Please enter an integer between 0 to 3: ";
					cin >> xEndS;
					i = -1;
				}
			}
			xEnd = atoi(xEndS.c_str());
			if(xEnd > 3){
				cout << "Please enter an integer between 0 to 3: ";
				cin >> xEndS;
			}
			else{
				break;
			}
		}while(1);
		cout << "Ending y coordinate (from 0 to 3): ";
		cin >> yEndS;
		do {
			for(int i = 0; i < yEndS.length(); i++){
				if(!(yEndS.at(i) >= '0' && yEndS.at(i) <= '9' && yEndS.length() == 1)){
					cout << "Please enter an integer between 0 to 3: ";
					cin >> yEndS;
					i = -1;
				}
			}
			yEnd = atoi(yEndS.c_str());
			if(yEnd > 3){
				cout << "Please enter an integer between 0 to 3: ";
				cin >> yEndS;
			}
			else{
				break;
			}
		}while(1);
		find_path(xStart, xEnd, yStart, yEnd); // pass value to find_path() to print steps.

		/*
		 * The while loop below prompt user if they want to start again,
		 * only restart if user inputs "Yes" or "yes",
		 * only quit program if user inputs "No" or "no".
		 * Error handling included.
		 */
		bool choiceRestart = true;
		while(choiceRestart == true){
			cout << "Run again? (yes or no): ";
			cin >> userRestart;
			if(userRestart == "no" || userRestart == "No"){
				restart = false;
				choiceRestart = false;
				cout << restart;
				cout << choiceRestart;
			}
			else if(userRestart == "yes" || userRestart == "Yes"){
				restart = true;
				choiceRestart = false;
			}
			else{
				choiceRestart = true;
				cout << "Please enter yes or no ! " << endl;
			}
		}
	}
	return 0;
}

/*********************************************************************
 ** Function: find_path()
 ** Description: This function finds the steps of the path from 
 ** 	starting points to destination, it calls the print_line() to 
 ** 	print out the steps.
 ** Parameters: Integer xS: Starting x coordinates. 
 ** 	Interger xE: Ending x coordinates. 
 ** 	Integer yS: Starting y coordinates. 
 ** 	Integer yE: Ending y coordinates.
 ** Pre-Conditions: All the inputs in parameters must be integers 
 ** 	between 0 and 3.
 ** Post-Conditions: Prints out all the steps before it exits;
 *********************************************************************/ 
void find_path(int xS, int xE, int yS, int yE){
	int moveX, moveY; // declare integer moveX, moveY
	moveX = xE - xS; // calculate x movemene
	moveY = yE-yS; // calculate y movement

	// move right or stay
	if(moveX >= 0){
		for(int i = 0; i <= moveX; i++){
			int j = 0;
			print_line(xS,i,yS,j);
			cout << "---------" << endl << endl;
		}
	}
	// move left
	else{
		for(int i = -1; i >= moveX - 1; i--){
			int j = 0;
			print_line(xS,i,yS,j);
			cout << "---------" << endl << endl;
		}
	}
	// move up or stay
	if(moveY >= 0){
		for(int j = 1; j <= moveY; j++){
			int i = moveX;
			print_line(xS,i,yS,j);
			cout << "---------" << endl << endl;
		}
	}
	// move down
	else{
		for(int j = -1; j >= moveY; j--){
			int i = moveX;
			print_line(xS,i,yS,j);
			cout << "---------" << endl << endl;
		}
	}
}

/*********************************************************************
 ** Function: print_line()
 ** Description: This function prints the steps for the rover 
 ** 	according to the value inputs by find_path function.
 ** Parameters: Integer xStart: Starting x coordinate. 
 ** 	Integer i: The x displacement. 
 ** 	Integer y Start: Starting y coordinate. 
 ** 	Integer j: The y displacement.
 ** Pre-Conditions: Starting x coordinate and y coordinate are 
 ** 	between 0 and 3. x and y displacement must be inside the 
 ** 	4-by-4 coordinate system.
 ** Post-Conditions: Prints out complete step according to the 
 ** 	input of find_path function.
 *********************************************************************/ 
void print_line(int xStart, int i, int yStart, int j){
	// prints the step when in x movement
	if(j == 0){
		// print the line
		for(int line = 3; line >= 0; line--){
			cout << "---------" << endl;
			// if line number is the same as starting y coordinate
			if(line == yStart){
				int count = 0;
				// if the rover is moving right or staying
				if(i >= 0){
					switch(xStart){
						case 1: 
							cout << "| ";
							count++;
							break;
						case 2:
							cout << "| | ";
							count = count + 2;
							break;
						case 3:
							cout << "| | | ";
							count = count + 3;
							break;
					}
					int column = 1;
					while(column <= i +1){
						cout << "|X";
						column++;
						count++;
					}
					while(count < 4){
						cout << "| ";
						count++;
					}
				}
				// if the rover is moving left
				else{
					int start = xStart + i + 1;
					switch(start){
						case 1:
							cout << "| ";
							count++;
							break;
						case 2:
							cout << "| | ";
							count = count + 2;
							break;
						case 3:
							cout << "| | | ";
							count = count + 3;
							break;
					}
					int column = -1;
					while(column >= i){
						cout << "|x";
						column--;
						count++;
					}
					while(count < 4){
						cout << "| ";
						count++;
					}
				}
				cout << "|" << endl;
			}
			else{
				cout << "| | | | |" << endl;
			}
		}
	}
	// print steps when in y movement
	else{
		// print each line
		for(int line = 3; line >= 0; line--){
			cout << "---------" << endl;
			// if the rover is moving up or staying
			if(j >= 0){
				// if the line is not on the path of rover in current step
				if(line > (j+yStart) || line < yStart){
					cout << "| | | | |" << endl;
				}
				// if the line is on the path of rover in current step
				else if(line <= (j + yStart) && line > yStart){
					int countY = 0;
					switch(xStart + i){
						case 1:
							cout << "| ";
							countY++;
							break;
						case 2:
							cout << "| | ";
							countY = countY + 2;
							break;
						case 3:
							cout << "| | | ";
							countY = countY + 3;
							break;
					}
					cout << "|X";
					countY++;
					while(countY < 4){
						cout << "| ";
						countY++;
					}
					cout << "|" << endl;
				}
			}
			// if the rover is moving down
			else{
				// if the rover is not on the path of rover in current step
				if(line > yStart || line < (yStart + j)){
					cout << "| | | | |" << endl;
				}
				// if the rover is on the path of rover in current step
				else if(line < yStart && line >= (yStart + j)){
					int countY = 0;
					switch(xStart + i){
						case 1:
							cout << "| ";
							countY++;
							break;
						case 2:
							cout << "| | ";
							countY = countY + 2;
							break;
						case 3:
							cout << "| | | ";
							countY = countY + 3;
							break;
					}
					cout << "|X";
					countY++;
					while(countY < 4){
						cout << "| ";
						countY++;
					}
					cout << "|" << endl;
				}
			}
			// if the line is on the path when rover is on x movement
			if(line == yStart){
				int count = 0;
				// if the rover is moving right or staying during x movement
				if(i >= 0){
					switch(xStart){
						case 1: 
							cout << "| ";
							count++;
							break;
						case 2:
							cout << "| | ";
							count = count + 2;
							break;
						case 3:
							cout << "| | | ";
							count = count + 3;
							break;
					}
					int column = 1;
					while(column <= i +1){
						cout << "|X";
						column++;
						count++;
					}
					while(count < 4){
						cout << "| ";
						count++;
					}
				}
				// if the rover is moving left during x movement
				else{
					int start = xStart + i;
					switch(start){
						case 1:
							cout << "| ";
							count++;
							break;
						case 2:
							cout << "| | ";
							count = count + 2;
							break;
						case 3:
							cout << "| | | ";
							count = count + 3;
							break;
					}
					int column = 0;
					while(column >= i){
						cout << "|x";
						column--;
						count++;
					}
					while(count < 4){
						cout << "| ";
						count++;
					}
				}
				cout << "|" << endl;
			}
		}
	}
}
