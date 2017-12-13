#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
void get_sentence(char []);
bool determine_palindrome(char []);
void get_search_replace_strings(char [], char []);
int search_replace(char [], char [], char []);

void get_sentence(char msg[]){
	cout << "Enter your string (Please enter '|' after you string): ";
	cin.ignore();
	cin.getline(msg, 256);
	cout << msg << endl;
}

bool determine_palindrome(char msg[]){
	int length = strlen(msg);
	for(int i = 0, j = length - 1; i < j; i++, j--){
		if(msg[i] != msg[j]){
			return false;
		}
	}
	return true;
}
void get_search_replace_strings(char oldstr[], char newstr[]){
	cout << "Please enter the string you want to replace: " << endl;
	cin >> oldstr;
	cout << "Please enter the string you want to replace with: " << endl;
	cin >> newstr;
}

int search_replace(char msg[], char oldstr[], char newstr[]){
	int length = strlen(msg), oldlength = strlen(oldstr), newlength = strlen(newstr), differ = newlength - oldlength, count = 0;
	do{
		char *pos = strstr (msg, oldstr);
		if(pos == NULL){
			break;
		}
		if(differ > 0){
			for(int i = strlen(msg) - 1; i > pos - msg + 1; i--){
				msg[i + differ] = msg[i];
			}
		}else{
			//for(int i = strlen(msg) - 1; i > pos - msg + 1; i--){
			for(int i = pos - msg + oldlength; i < length; i++){
				msg[i + differ] = msg[i];
			}
			for(int i = length - 1; i > length - 1 + differ; i--){
				msg[i] = 0;
			}
		}
		strncpy (pos, newstr, newlength);
		count++;
	}while(1);
	return count;
}

int main(){
	char msg[256];
	int n = 0;
	cout << "Enter your string (Please enter '|' after your string): ";
	cin.getline(msg, 256, '|');
	while(1){
		if(n > 0){
			get_sentence(msg);
		}
		n++;
		while(1){
			char oldstr[10], newstr[10];
			int option, count;
			cout << "Determine if palindrome (1), replace string (2), enter new string (3), or quit (0)? ";
			cin >> option;
			if(option == 1){
				if(determine_palindrome(msg) == true){
					cout << "You have entered a palindrome" << endl;
				}else{
					cout << "You have not entered a palidrome" << endl;
				}
			}else if(option == 2){
				get_search_replace_strings(oldstr, newstr);
				count = search_replace(msg, oldstr, newstr);
				cout << "You made " << count << " replacement, and your new string is " << msg << endl;
			}else if(option == 3){
				break;
			}else{
				exit(1);
			}
		}
	}
}