#include <iostream>
#include <string>

using namespace std;

string get_sentence(){
	string name;
	getline(cin, name);
	return name;
}// mark 1

void get_sentence_mark2(string &s){
	getline(cin, s);
}// mark 2

int main(){
	string sentence, sentence2;
	//mark1
	sentence = get_sentence();
	cout << sentence << endl;
	//mark2
	get_sentence_mark2(sentence2);
	cout << sentence2 << endl;

	return 0;
}