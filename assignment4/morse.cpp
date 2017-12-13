/*********************************************************************
 ** Program Filename: morse.cpp
 ** Author: Tsewei Peng
 ** Date: 02/28/2016
 ** Description: Morse translator or decoder
 ** Input: letters space or . and -
 ** Output: letters, space or . and -
 *********************************************************************/
#include <iostream>

using namespace std;
void translator(char letter[],char morse[][5], bool &quit);
void letterInput(char letter[], char morse[][5]);
void letter_error(char user_letter[]);
void lowercase(char user_letter[]);
void letter_to_morse(char letter[], char morse[][5], char user_letter[]);
void morseInput(char letter[], char morse[][5]);
void morse_error(char user_morse[]);
void morse_to_letter(char letter[], char morse[][5], char user_letter[]);
void set_temp(char letter[], char morse[][5], char user_morse[], int &countletter, int i);
void decode(char morse[][5], char letter[], char temp[]);
/************** 	*******************************************************
 ** Function: strlen
 ** Description: get the length or c string
 ** Parameters: c string word[]
 ** Pre-Conditions: the input must be a c string
 ** Post-Conditions: return the length of the c string
 *********************************************************************/
int strlen(char word[]){
	int count = 0;
	for(int i = 0; word[i] != '\0'; i++){
		count++;
	}
	return count;
}

/*********************************************************************
 ** Function: main()
 ** Description: where everything is executed
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: code translated
 *********************************************************************/
int main(){
	// All the arrays
	char letter[27] = "abcdefghijklmnopqrstuvwxyz";
	char morse[26][5] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "-.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
/* A .-    B -...   C -.-.   D -..
   E .     F ..-.   G -.     H ....
   I ..    J .---   K -.-    L .-..
   M --    N -.     O ---    P .--.
   Q --.-  R .-.    S ...    T -
   U ..-   V ...-   W .--    X -..-
   Y -.--  Z --..   */
	bool quit = false;
	// quit must equal to false, and will be changed when user decide to quit
	while(quit == false){
		translator(letter, morse, quit);
	}
}

/*********************************************************************
 ** Function: translator()
 ** Description: translate the code
 ** Parameters: morse code array, letter array, quit boolean
 ** Pre-Conditions: morse code must be legit, letter must be from a to z
 ** Post-Conditions: the letter or codes translated after function each round
 *********************************************************************/
void translator(char letter[],char morse[][5], bool &quit){
	int choice;
	cout << "Do you want to \n\t(1) translate text to Morse code \n\t(2) translate Morse code to text \n\t(0) quit the program? \n";
	cin >> choice;
	if(choice == 1){
		letterInput(letter, morse);
	}else if(choice == 2){
		morseInput(letter, morse);
	}else{
		// when user choose 0, quit the program
		quit = true;
	}
}

/*********************************************************************
 ** Function: letterInput()
 ** Description: Get the letters from user
 ** Parameters: letter array, morse code array
 ** Pre-Conditions: arrays must be legit
 ** Post-Conditions: letter translated to code
 *********************************************************************/
void letterInput(char letter[], char morse[][5]){
	// input the letters
	char *user_letter;
	user_letter = new char[256];
	cout << "Enter Text Message: ";
	cin.ignore();
	cin.get(user_letter, 256, '\n');
	// error handle
	letter_error(user_letter);
	// lower case the user_letter
	lowercase(user_letter);
	// translation
	letter_to_morse(letter, morse, user_letter);
	// free memory
	delete [] user_letter;
}

/*********************************************************************
 ** Function: letter_error()
 ** Description: error handle the letter
 ** Parameters: user_letter[]
 ** Pre-Conditions: none
 ** Post-Conditions: return correct input for letter
 *********************************************************************/
void letter_error(char user_letter[]){
	// while reprompt until the user enter message with only space, a-z, A-Z
	do{
		bool reprompt = false;
		for(int i = 0; i < strlen(user_letter); i++){
			if(!((user_letter[i] >= 'A' && user_letter[i] <= 'Z') || (user_letter[i] >= 'a' && user_letter[i] <= 'z') || user_letter[i] == ' ')){
				reprompt = true;
				cout << "Please enter message with letters and spaces only !" << endl;
				break;
			}
		}
		if(reprompt == false){
			// if reprompt is false, quit the function
			return;
		}
		cout << "Enter Text Message: ";
		cin.ignore();
		cin.get(user_letter, 256, '\n');
	}while(1);
}

/*********************************************************************
 ** Function: lowercase()
 ** Description: change the user_letter into lower case
 ** Parameters: user_letter[]
 ** Pre-Conditions: user_letter must be between a to z, A to Z
 ** Post-Conditions: the c string is converted to lower case
 *********************************************************************/
void lowercase(char user_letter[]){
	for(int i = 0; i < strlen(user_letter); i++){
		if(user_letter[i] >= 'A' && user_letter[i] <= 'Z'){
			// switch the uper case to lower case
			user_letter[i]+=32;
		}
	}
}

/*********************************************************************
 ** Function: letter_to_morse()
 ** Description: translate letter to morse code
 ** Parameters: letter[] morse array, user_letter[]
 ** Pre-Conditions: arrays legic, user_letter all letters lowercase
 ** Post-Conditions: letter translated
 *********************************************************************/
void letter_to_morse(char letter[], char morse[][5], char user_letter[]){
	// going through every letters
	for(int i = 0; i < strlen(user_letter); i++){
		for(int j = 0; j < 26; j++){
			// if it is letter, then output the morse code
			if(user_letter[i] == letter[j]){
				cout << morse[j];
				break;
			}
			// if it is space, then output a space
			else if(user_letter[i] == ' '){
				cout << " ";
				break;
			}
		}
		cout << "   "
;	}
	cout << endl << endl;
}

/*********************************************************************
 ** Function: morseInput()
 ** Description: input the morse code from user
 ** Parameters: letter and morse arrays
 ** Pre-Conditions: legit arrays
 ** Post-Conditions: code translated
 *********************************************************************/
void morseInput(char letter[], char morse[][5]){
	// input morse code
	char *user_morse;
	user_morse = new char[256];
	cout << "Enter Morse Code: (3 spaces between each morse code)\n";
	cin.ignore();
	cin.get(user_morse, 256, '\n');
	// error handle morse code error
	morse_error(user_morse);
	// translation
	morse_to_letter(letter, morse, user_morse);
	delete [] user_morse;
	// free memory
}

/*********************************************************************
 ** Function:morse_error
 ** Description: error handle the user input morse code
 ** Parameters: user_morse[]
 ** Pre-Conditions: none
 ** Post-Conditions: the input code is correct to handle
 *********************************************************************/
void morse_error(char user_morse[]){
	// will reprompt untill the input only has - and . and space
	do{
		bool reprompt = false;
		for(int i = 0; i < strlen(user_morse); i++){
			if(!(user_morse[i] == ' ' || user_morse[i] == '.' || user_morse[i] == '-')){
				reprompt = true;
				cout << "Please enter morse code with only space, '.' and '-' !" << endl;
				break;
			}
		}
		if(reprompt == false){
			// will quit function if reprompt is false
			return;
		}
		cout << "Enter Morse Code: ";
		cin.ignore();
		cin.get(user_morse, 256, '\n');
	}while(1);
}

/*********************************************************************
 ** Function: morse_to_letter()
 ** Description: change the morse code to letter
 ** Parameters: letter morse arrays, user_morse[]
 ** Pre-Conditions: user_morse must have only space . and -
 ** Post-Conditions: The post condition is code translated
 *********************************************************************/
void morse_to_letter(char letter[], char morse[][5], char user_morse[]){
	// count the morse code before space and put it in temp[]
	int countletter = 0;
	for(int i = 0; i <= strlen(user_morse); i++){
		if(user_morse[i] == '-' || user_morse[i] == '.'){
			// add one whenever not space
			countletter++;
		}else if(user_morse[i] == ' '){
			if(user_morse[i+3] != ' '){
				// the 3 space scenario
				set_temp(letter, morse, user_morse, countletter, i);
				i += 2;
			}else{
				set_temp(letter, morse, user_morse, countletter, i);
				// the 7 space scenario
				cout << " ";
				i += 6;
			}
			// reset the countletter
			countletter = 0;
		}else{
			// for the last code
			set_temp(letter, morse, user_morse, countletter, i);
		}
	}
	cout << endl;
}

/*********************************************************************
 ** Function: set_temp
 ** Description: transcript the code into a temperary array
 ** Parameters: letter morse array, user_morse[], countletter, i
 ** Pre-Conditions: countletter and i must be legit, user_morse only . -
 ** Post-Conditions: decode the temperary morse code
 *********************************************************************/
void set_temp(char letter[], char morse[][5], char user_morse[], int &countletter, int i){
	// set up the temp
	char *temp;
	temp = new char[5];
	for(int j = 0; j < countletter; j++){
		temp[j] = user_morse[i-countletter+j];
	}
	temp[countletter] = '\0';
	for(int j = countletter + 1; j < 5; j++){
		temp[j] = 0;
	}
	decode(morse, letter, temp);
	// temp freed
	delete [] temp;
}

/*********************************************************************
 ** Function: decode()
 ** Description: find the morse code that match and translate
 ** Parameters: letter morse array, temp[]
 ** Pre-Conditions: temp must be legit
 ** Post-Conditions: code translated and outputed
 *********************************************************************/
void decode(char morse[][5], char letter[], char temp[]){
	for(int j = 0; j < 26; j++){
		bool decode = true;
		for(int k = 0; k < 5; k++){
			if(temp[k] != morse[j][k]){
				decode = false;
				break;
			}
		}
		// decode the morse code to letter
		if(decode == true){
			cout << letter[j];
			return;
		}
	}
}
