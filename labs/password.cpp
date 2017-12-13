#include <iostream>	
#include <stdlib.h>
#include <string>
using namespace std;

int main(){
	srand(time(NULL));
	cout << "Welcome to Password Creator!"<< endl;
	bool replay = true;
	while(replay == true){
		string lengthS, upperS, lowerS, numS, specialS, letterCS, upperCS, lowerCS, numCS, specialCS;
		int length, upper_length, lower_length, num_length, special_length, letterc, upperc, lowerc, numc, specialc, restartI;
		string restart;
		do{
			cout << "How long do you want the password to be? (max 2000 characters): ";
			cin >> lengthS;
			do{
				for(int i = 0; i < lengthS.length(); i++){
					if(!(lengthS.at(i) >= '0' && lengthS.at(i) <= '9' && lengthS.length() <= 4)){
						cout << "Please enter positive integer that is lower than 2000: ";
						cin >> lengthS;
					}
				}
				length = atoi(lengthS.c_str());
				if(length > 2000){
					cout << "Please enter positive integer that is lower than 2000: ";
					cin >> lengthS;
				}else{
					break;
				}
			}while(1);
			cout << "Do you want letters (0-no, 1-yes)? ";
			cin >> letterCS;
			do{
				for(int i = 0; i < letterCS.length(); i++){
					if(!(letterCS.at(i) >= '0' && letterCS.at(i) <= '9' && letterCS.length() == 1)){
						cout << "Please enter 1 for yes and 0 for no: ";
						cin >> letterCS;
						break;
					}
				}
				letterc = atoi(letterCS.c_str());
				if(letterc > 1){
					cout << "Please enter 1 for yes and 0 for no: ";
					cin >> letterCS;
				}else{
					break;
				}
			}while(1);
			if (letterc == 1){
				cout << "Do you want uppercase letters (0-no, 1-yes)? ";
				cin >> upperCS;
				do{
					for(int i = 0; i < upperCS.length(); i++){
						if(!(upperCS.at(i) >= '0' && upperCS.at(i) <= '9' && upperCS.length() == 1)){
							cout << "Please enter 1 for yes and 0 for no: ";
							cin >> upperCS;
						}
					}
					upperc = atoi(upperCS.c_str());
					if(upperc > 1){
						cout << "Please enter 1 for yes and 0 for no: ";
						cin >> upperCS;
					}else{
						break;
					}
				}while(1);
				if (upperc == 1){
					cout << "How many uppercase letters do you want? ";
					cin >> upperS;
					do{
						for(int i = 0; i < upperS.length(); i++){
							if(!(upperS.at(i) >= '0' && upperS.at(i) <= '9' && upperS.length() <= 4)){
								cout << "Please enter positive integer that is lower than 2000: ";
								cin >> upperS;
							}
						}
						upper_length = atoi(upperS.c_str());
						if(length > 2000){
							cout << "Please enter positive integer that is lower than 2000: ";
						}else{
							break;
						}
					}while(1);
				}else{
					upper_length = 0;
				}
				cout <<"Do you want lowercase letters (0-no, 1-yes)? ";
				cin >> lowerCS;
				do{
					for(int i = 0; i < lowerCS.length(); i++){
						if(!(lowerCS.at(i) >= '0' && lowerCS.at(i) <= '9' && lowerCS.length() == 1)){
							cout << "Please enter 1 for yes and 0 for no: ";
							cin >> lowerCS;
						}
					}
					lowerc = atoi(lowerCS.c_str());
					if(upperc > 1){
						cout << "Please enter 1 for yes and 0 for no: ";
						cin >> lowerCS;
					}else{
						break;
					}
				}while(1);
				if (lowerc == 1){
					cout << "How many lowercase letters do you want? ";
					cin >> lowerS;
					do{
						for(int i = 0; i < lowerS.length(); i++){
							if(!(lowerS.at(i) >= '0' && lowerS.at(i) <= '9' && lowerS.length() <= 4)){
								cout << "Please enter positive integer that is lower than 2000: ";
								cin >> lowerS;
							}
						}
						lower_length = atoi(lowerS.c_str());
						if(length > 2000){
							cout << "Please enter positive integer that is lower than 2000: ";
						}else{
							break;
						}
					}while(1);
				}else{
					lower_length = 0;
				}	
			}
			cout << "Do you want numbers (0-no, 1-yes)? ";
			cin >> numCS;
			do{
				for(int i = 0; i < numCS.length(); i++){
					if(!(numCS.at(i) >= '0' && numCS.at(i) <= '9' && numCS.length() == 1)){
						cout << "Please enter 1 for yes and 0 for no: ";
						cin >> numCS;
					}
				}
				numc = atoi(numCS.c_str());
				if(upperc > 1){
					cout << "Please enter 1 for yes and 0 for no: ";
					cin >> numCS;
				}else{
					break;
				}
			}while(1);
			if (numc == 1){
				cout << "How many numbers do you want? ";
				cin >> numS;
				do{
					for(int i = 0; i < numS.length(); i++){
						if(!(numS.at(i) >= '0' && numS.at(i) <= '9' && numS.length() <= 4)){
							cout << "Please enter positive integer that is lower than 2000: ";
							cin >> numS;
						}
					}
					num_length = atoi(numS.c_str());
					if(length > 2000){
						cout << "Please enter positive integer that is lower than 2000: ";
					}else{
						break;
					}
				}while(1);
			}else{
				num_length = 0;
			}
			cout << "Do you want special characters (0-no, 1-yes)? ";
			cin >> specialCS;
			do{
				for(int i = 0; i < specialCS.length(); i++){
					if(!(specialCS.at(i) >= '0' && specialCS.at(i) <= '9' && specialCS.length() == 1)){
						cout << "Please enter 1 for yes and 0 for no: ";
						cin >> specialCS;
					}
				}
				specialc = atoi(specialCS.c_str());
				if(upperc > 1){
					cout << "Please enter 1 for yes and 0 for no: ";
					cin >> specialCS;
				}else{
					break;
				}
			}while(1);
			if (specialc == 1){
				cout << "How many special characters do you want? ";
				cin >> specialS;
				do{
					for(int i = 0; i < specialS.length(); i++){
						if(!(specialS.at(i) >= '0' && specialS.at(i) <= '9' && specialS.length() <= 4)){
							cout << "Please enter positive integer that is lower than 2000: ";
							cin >> specialS;
						}
					}
					special_length = atoi(specialS.c_str());
					if(length > 2000){
						cout << "Please enter positive integer that is lower than 2000: ";
					}else{
						break;
					}
				}while(1);
			}else{
				special_length = 0;
			}
			if(length == upper_length + lower_length + num_length + special_length){
				break;
			}else{
				cout << "Your total number of characters do not correspond your password length, Please re-input your value ! " << endl;
			}
		}while(1);
		int ranpath, ran1, ran2, ran3, ran4;
		int total_length = length;
		string password = "";
		while (total_length > 0){
			ranpath = rand() % 4 + 1;
			if(ranpath == 1){
				if(upper_length > 0){
					ran1 = rand() % 26 + 75;
					char upperString = (char) ran1;
					password += upperString;
					upper_length--;
				}
			}
			else if(ranpath == 2){
				if(lower_length > 0){
					ran2 = rand() % 26 + 97;
					char lowerString = (char) ran2;
					password += lowerString;
					lower_length--;
				}
			}
			else if(ranpath == 3){
				if(num_length > 0){
					ran3 = rand() % 10 + 48;
					char numString = (char) ran3;
					password += numString;
					num_length--;
				}
			}else{
				if(special_length > 0){
					ran4 = rand() % 32;
					if(ran4 <= 14){
						ran4 += 33;
					}else if(ran4 <= 21){
						ran4 += 43;
					}else if(ran4 <= 27){
						ran4 += 69;
					}else{
						ran4 += 95;
					}
					char specialString = (char) ran4;
					password += specialString;
					special_length--;
				}
			}
			total_length = upper_length + lower_length + num_length + special_length;
		}
		cout << "The password generated is: " << password << endl;
		cout << "Would you like to create another password (0-no, 1-yes)? ";
		cin >> restart;
		do{
			for(int i = 0; i < restart.length(); i++){
				if(!(restart.at(i) >= '0' && restart.at(i) <= '9' && restart.length() == 1)){
					cout << "HAHA";
					cout << "Please enter 1 for yes and 0 for no: ";
					cin >> restart;
				}
			}
			restartI = atoi(restart.c_str());
			if(letterc > 1){
				cout << "HAHA";
				cout << "Please enter 1 for yes and 0 for no: ";
				cin >> restart;
			}else{
				break;
			}
		}while(1);
		if (restartI == 1){
			replay = true;
		}else{
			replay = false;
		}
	}
	return 0;
}

