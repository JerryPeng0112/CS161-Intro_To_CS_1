#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void get_sentence(string &);
bool determine_palindrome(string);
void get_search_replace_strings(string *, string *);
int search_replace(string &, string, string);
int main();

void get_sentence(string &sentence){
	cout << "Enter your string (Please enter '|' after you finish your message): ";
	cin.ignore();
	getline(cin, sentence, '|');
	cout << sentence << endl;
}

bool determine_palindrome(string sentence){
	int length;
	length = sentence.length();
	if(length % 2 == 0){
		for(int i = 0; i <= length/2 -1; i++){
			if(sentence.at(i) != sentence.at(length - 1 - i)){
				return false;
			}
		}
	}else{
		for(int i = 0; i < (length-1)/2; i++){
			if(sentence.at(i) != sentence.at(length -1 -i)){
				return false;
			}
		}
	}
	return true;
}

void get_search_replace_strings(string *old_string, string *new_string){
	cout << "Please enter the string you want to replace: " << endl;
	cin >> *old_string;
	cout << "Please enter the string you want to replace with: " << endl;
	cin >> *new_string;
}

int search_replace(string &sentence, string old_string, string new_string){
	int count = 0, pos;
	do{
		pos = sentence.find(old_string);
		if(pos == string::npos){
			break;
		}
		sentence.replace(pos,old_string.length(),new_string);
		count++;
	}while(1);
	cout << "You made " << count << " replacement, and your new string is " << sentence << endl;
}

int main(){
	string sentence, whatever;
	cout << "TYPE 'Y' TO PROCEED: ";
	cin >> whatever;
	do{
		sentence = "";
		get_sentence(sentence);
		do{
			int option, count; string old_string, new_string;
			cout << "Determine if palindrome (1), replace string (2), enter new string (3), or quit (0)? "; cin >> option;
			if(option == 1){
				if(determine_palindrome(sentence) == true){
					cout << "You have entered a palindrome" << endl;
				}else{
					cout << "You have not entered a palidrome" << endl;
				}
			}else if(option == 2){
				get_search_replace_strings(&old_string, &new_string);
				count = search_replace(sentence, old_string, new_string);
			}else if(option == 3){
				main();
			}else{
				exit(1);
			}
		}while(1);
	}while(1);
	return 0;
}