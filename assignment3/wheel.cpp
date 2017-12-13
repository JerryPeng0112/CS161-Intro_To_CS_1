/*********************************************************************
 ** Program Filename: wheel.cpp
 ** Author: Tsewei Peng
 ** Date: 02/18/16
 ** Description: WHEEL OF FORTUNE ULTIMATE 2016
 ** Input: lines of words, numbers, letters
 ** Output: Money, Money, Money, and the winner gets it all.
 *********************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void money_output(int player_num, int player1_money, int player2_money, int player3_money);
void option(int &player_num, int &round_num);
void round(int player_num, int &player1_money, int &player2_money, int &player3_money, int i);
void hide_secret_message();
void get_message(string &message);
void empty_message(string secret_message, string &game_message);
bool player_switch(string secret_message, int player_num, string &game_message, int &player1_money, int &player2_money, int &player3_money, int &player1_rmoney, int &player2_rmoney, int & player3_rmoney, int i);
bool player_turn(string player, string secret_message, string &game_message, bool &end_round, int &player_money, int &player_rmoney, int i);
void turn(string player,string secret_message,string &game_message, bool &end_round, int &player_rmoney);
bool player_choice(string player, string secret_message, string &game_message, bool &end_round, int &player_rmoney, int &vowel_chance);
void vowel_entry(int &vowel_chance, string secret_message, string &game_message, int &player_rmoney);
void spin(string secret_message, string &game_message, bool &end_turn, int &player_rmoney);
void nonvowel_entry(string secret_message, string &game_message, int &player_rmoney, bool &end_turn, int wheel);
int guess_nonvowel(string secret_message, string &game_message, int wheel, int &player_rmoney);
bool find_letter(char nonvowel, string game_message, int wheel, int &player_rmoney);
bool check_nonvowel(char nonvowel);
int count_correct(char nonvowel, string secret_message, string &game_message);
void reveal_message(int i, string &game_message, char nonvowel);
void solve(string secret_message, bool &end_turn, bool &end_round);
void buy_vowel(string secret_message, string &game_message, int &player_rmoney);

/*********************************************************************
 ** Function: main
 ** Description: the program starts here, initiate all the important values
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: finish the program without error
 *********************************************************************/
int main(){
	srand(time(NULL));
	// Declare money for player account for the WHOLE GAME
	int player_num, round_num, player1_money = 0, player2_money = 0, player3_money = 0;
	// Ask for numbers of rounds and players
	option(player_num, round_num);
	// Each loop means a round of game
	for(int i = 1; i <= round_num; i++){
		cout << "Round Number " << i << endl;
		round(player_num, player1_money, player2_money, player3_money, i);
		money_output(player_num, player1_money, player2_money, player3_money);
	}
}

/*********************************************************************
 ** Function: money_output
 ** Description: output the player's game money when game finished
 ** Parameters: player number, player 1 and 2 and 3's game money
 ** Pre-Conditions: The game must finish
 ** Post-Conditions: Ouput the right money amount
 *********************************************************************/
void money_output(int player_num, int player1_money, int player2_money, int player3_money){
	if(player_num == 1 || player_num == 2 || player_num == 3){
		cout << "Player 1 total: $" << player1_money << endl;
	}
	if(player_num == 2 || player_num == 3){
		cout << "Player 2 total: $" << player2_money << endl;
	}
	if(player_num == 3){
		cout << "Player 3 total: $" << player3_money << endl;
	}
}

/*********************************************************************
 ** Function: option
 ** Description: ask user for the number of rounds and player
 ** Parameters: player number and round number variables
 ** Pre-Conditions: none
 ** Post-Conditions: get the number of players and rounds
 *********************************************************************/
void option(int &player_num, int &round_num){
	// Ask for user to set up the game
	cout << "How many players do you have: ";
	cin >> player_num;
	cout << "How many numbers of rounds do you have: ";
	cin >> round_num;
}

/*********************************************************************
 ** Function: round
 ** Description: the function runs for every round of game
 ** Parameters: player number, player1, 2, 3 money amout and current round number
 ** Pre-Conditions: the user must input a valid player number, player 1, 2, 3 money initialized.
 ** Post-Conditions: finish the round
 *********************************************************************/
void round(int player_num, int &player1_money, int &player2_money, int &player3_money, int i){
	string secret_message, game_message;
	// Declare player money for the ROUND, only will be added to game money if the user guessed the message right
	int player1_rmoney = 0, player2_rmoney = 0, player3_rmoney = 0;
	/*
	 * string secret_message important, will be passed
	 * by functinos as a parameter
	 *
	 * string game_message important, will be pass around
	 * and use by functions, will be a reference
	 */

	// Input secret message
	get_message(secret_message);
	hide_secret_message();
	empty_message(secret_message, game_message);
	// Loop continues until one of the players get the secret message
	while(1) {
		if (!player_switch(secret_message, player_num, game_message, player1_money, player2_money, player3_money, player1_rmoney, player2_rmoney, player3_money, i)) break;
	}
}

/*********************************************************************
 ** Function: get_message
 ** Description: get the message from user
 ** Parameters: smessage
 ** Pre-Conditions:none
 ** Post-Conditions: the user input
 *********************************************************************/
void get_message(string &message){
	while(1){
		cout << "(Lowercase letters and space only, and type a '|' when you are done)\nPlease enter the secret message:" << endl;
		cin.ignore();
		getline(cin, message, '|');
		int count = 0;
		for(int i = 0; i < message.length(); i++){
			if(!((message.at(i) <= 'z' && message.at(i) >= 'a') || message.at(i) == ' ')){
				count++;
			}
		}
		if(count == 0){
			return;
		}else{
			cout << "Please enter the message with lower case letters! ";
		}
	}
}
/*********************************************************************
 ** Function: hide_secret_message
 ** Description: hide the secret message from player
 ** Parameters: none
 ** Pre-Conditions: secret message is inputed
 ** Post-Conditions: the secret message disappear
 *********************************************************************/
void hide_secret_message(){
	for(int i = 0; i < 50; i++){
		cout << endl;
	}
}

/*********************************************************************
 ** Function: empty_message
 ** Description: takes the secret_message and create a game_message that is emptied
 ** Parameters: secret_message, game_message
 ** Pre-Conditions: The secret_message must be a valie message
 ** Post-Conditions: the game_message contains underlines for each characters, and space for each spaces in the secret message
 *********************************************************************/
void empty_message(string secret_message, string &game_message){
	cout << "The message is:";
	// Loop to convert all the characters from 'a' and 'z' to '_', and ' ' to ' '
	for(int i = 0; i < secret_message.length(); i++){
		game_message += " ";
		if(secret_message.at(i) >= 'a' && secret_message.at(i) <= 'z'){
			game_message += "_";
		}else{
			game_message += " ";
		}
	}
	cout << game_message << endl << endl;
}

/*********************************************************************
 ** Function: player_switch
 ** Description: It switch turns from player 1 to player 3 according to the numbers of players
 ** Parameters: secret_message, player_num, game_message, player1, 2, 3 money, player1, 2, 3, round money, current round number
 ** Pre-Conditions: player number must be between 1 and 3, secret message made
 ** Post-Conditions: if the user solve the message, the player will win the round
 *********************************************************************/
bool player_switch(string secret_message, int player_num, string &game_message, int &player1_money, int &player2_money, int &player3_money, int &player1_rmoney, int &player2_rmoney, int & player3_rmoney, int i){
	// Switch made so that the players turn will be enabled by the number of players
	// bool end_1_turn = false, end_2_turn = false, end_3_turn = false;
	bool end_round = false; int winner = 0;
	string player1 = "Player 1", player2 = "Player 2", player3 = "Player 3";
	if(player_num == 1 || player_num == 2 || player_num == 3){
		if(player_turn(player1, secret_message, game_message, end_round, player1_money, player1_rmoney, i) == false){return false;}
	}
	if(player_num == 2 || player_num == 3){
		if(player_turn(player2, secret_message, game_message, end_round, player2_money, player2_rmoney, i) == false){return false;}
	}
	if(player_num == 3){
		if(player_turn(player3, secret_message, game_message, end_round, player3_money, player3_rmoney, i) == false){return false;}
	}
	return true;
}

/*********************************************************************
 ** Function: player_turn
 ** Description: the function is the function that runs a turn for each player
 ** Parameters: player string, secret_message, game_message, end_round boolean, player money, player round money, and current round number
 ** Pre-Conditions: none
 ** Post-Conditions: the player's turn end, either the player wins or next player starts his turn.
 *********************************************************************/
bool player_turn(string player, string secret_message, string &game_message, bool &end_round, int &player_money, int &player_rmoney, int i){
	turn(player, secret_message, game_message, end_round, player_rmoney);
	if(end_round == true){
		player_money += player_rmoney;
		cout << "You are correct! " << player << " wins round " << i << endl;
		return false;
	}else{
		return true;
	}
}

/*********************************************************************
 ** Function: turn
 ** Description: runs the turn for each players
 ** Parameters: player string, secret_message, game_message, boolean end_round, player round money
 ** Pre-Conditions: runs the turn
 ** Post-Conditions: none
 *********************************************************************/
void turn(string player,string secret_message,string &game_message, bool &end_round, int &player_rmoney){
	int vowel_chance = 1;
	// Loop continues until one of the players is done with the turn
	cout << "--> " << player << ", it is your turn !" << endl;
	while(1) {
		if (!player_choice(player, secret_message,game_message, end_round, player_rmoney, vowel_chance)) {break;};
	};
}

/*********************************************************************
 ** Function: player_choice
 ** Description: player string
 ** Parameters: string player, secret_message, game_message, boolean end_round, player round money, and vowel chance (only 1)
 ** Pre-Conditions: vowel initialized, parameter passed.
 ** Post-Conditions: the player get round money or end turn
 *********************************************************************/
bool player_choice(string player, string secret_message, string &game_message, bool &end_round, int &player_rmoney, int &vowel_chance){
	int choice;
	bool end_turn = false;
	cout << "Do you want to \n\t(1) Spin (and guess a non-vowel)\n\t(2) Solve the puzzle\n\t(3) Buy a vowel\n";
	cin >> choice; cout << endl;
	// Switch for the choice player made
	if(choice == 1){
		spin(secret_message, game_message, end_turn, player_rmoney);
		if(end_turn == true){return false;}
	}else if(choice == 2){
		solve(secret_message, end_turn, end_round);
		if(end_turn == true){return false;}
	}else if(choice == 3 && player_rmoney >= 10){
		vowel_entry(vowel_chance, secret_message, game_message, player_rmoney);
	}else{
		cout << "Not enough money. Buying a vowel costs 10 dollars." << endl;
	}
	return true;
}

/*********************************************************************
 ** Function: vowel_entry
 ** Description: when user choose to buy vowel
 ** Parameters: vowel_chance, secret_message, game_message, player round money
 ** Pre-Conditions: vowel chance must be 1, and the player has to have at least 10 bucks
 ** Post-Conditions: reveal the character if found, and the player lose 10 bucks, also vowel chance becomes 0
 *********************************************************************/
void vowel_entry(int &vowel_chance, string secret_message, string &game_message, int &player_rmoney){
	if(vowel_chance == 1){
		buy_vowel(secret_message, game_message, player_rmoney);
		vowel_chance--;
	}else{
		cout << "You can only buy a vowel once in a round ! " << endl;
	}
}

/*********************************************************************
 ** Function: spin
 ** Description: when user choose to spin the wheel. will have different routes according to the number spun
 ** Parameters: secret_message, game_message, end_turn boolean, and player round money
 ** Pre-Conditions: the user choose option 2
 ** Post-Conditions: the user gets money base from the guesses he made and the whel he spun.
 *********************************************************************/
void spin(string secret_message, string &game_message, bool &end_turn, int &player_rmoney){
	// Random number generator from 0 to 21 for wheel
	int wheel = rand() % 22;
	cout << "Your wheel landed on " << wheel << endl;
	if(wheel == 21){
		// Stop the turn of the player while money stays
		end_turn = true;
		cout << "Total: $" << player_rmoney << endl << "The message is" << game_message << endl << endl;
		return;
	}else if(wheel == 0){
		end_turn = true;
		player_rmoney = 0;
		cout << "Total: $" << player_rmoney << endl << "The message is" << game_message << endl << endl;
		return;
		// Stop the turn of the player and empty his round money.
	}else{
		// Get the number of occurences, and multiply it by the number on the wheel, and return to user round account.
		nonvowel_entry(secret_message, game_message, player_rmoney, end_turn, wheel);
	}
}

/*********************************************************************
 ** Function: nonvowel_entry
 ** Description: when the user guess nonvowel letter
 ** Parameters: secret_message, game_message, player round money, boolean end_turn, the number spun
 ** Pre-Conditions: the number spun must be between 1 and 20
 ** Post-Conditions: get the number of guesses, end turn if guessed number is 0
 *********************************************************************/
void nonvowel_entry(string secret_message, string &game_message, int &player_rmoney, bool &end_turn, int wheel){
		int guess_num;
		guess_num = guess_nonvowel(secret_message, game_message, wheel, player_rmoney);
		cout << "Total: $" << player_rmoney << endl;
		cout << "The message is" << game_message << endl << endl;
		if(guess_num == 0){
			end_turn = true;
			return;
		}
}

/*********************************************************************
 ** Function: guess_nonvowel
 ** Description: ask for a non-vowel letter, and find them, reveal them, and then return numbers found.
 ** Parameters: secret_message, game_message
 ** Pre-Conditions: guess_number initialized
 ** Post-Conditions: reveal the message partially and return numbers of letters revealed
 *********************************************************************/
int guess_nonvowel(string secret_message, string &game_message, int wheel, int &player_rmoney){
	// For user to spin the wheel and guess message, going to RETURN the value of chars found
	char nonvowel; bool nonvowel_pass = true, add_money; int correct_guess;
	while(nonvowel_pass == true){
		cout << "Guess a non-vowel letter: ";
		cin >> nonvowel;
		if (nonvowel <= 'z' && nonvowel >= 'a' && check_nonvowel(nonvowel) == true){
			nonvowel_pass = false;
		}else{
			cout << "Please enter a non-vowel letter!" << endl;
		}
	}
	add_money = find_letter(nonvowel, game_message, wheel, player_rmoney);
	// After getting the right input, get the number of occurences
	correct_guess = count_correct(nonvowel, secret_message, game_message);
	if(add_money == true){
		player_rmoney = player_rmoney + wheel * correct_guess;
	}
	cout << correct_guess << " found. ";
	return correct_guess;
}

/*********************************************************************
 ** Function: find_letter
 ** Description: find_the_letter
 ** Parameters:  nonvowel game_message, wheel, player_rmoney
 ** Pre-Conditions: none
 ** Post-Conditions: return true or false according to letter found
 *********************************************************************/
bool find_letter(char nonvowel, string game_message, int wheel, int &player_rmoney){
	int count = 0;
	for(int i = 0; i < game_message.length(); i++){
		if(game_message.at(i) == nonvowel){
			count++;
		}
	}
	if(count == 0){
		return true;
	}else{
		return false;
	}
}

/*********************************************************************
 ** Function: check_nonvowel
 ** Description: check if the input is a vowel or not
 ** Parameters: character nonvowel
 ** Pre-Conditions: must enter a valid nonvowel
 ** Post-Conditions: output true or false according to input
 *********************************************************************/
bool check_nonvowel(char nonvowel){
	// Parameter input is a char, return false if it is nonvowel, return true if it is vowel.
	if (nonvowel == 'a' || nonvowel == 'e' || nonvowel == 'i' || nonvowel == 'o' || nonvowel == 'u'){
		return false;
	}else{
		return true;
	}
}

/*********************************************************************
 ** Function: count_correct
 ** Description: count the correct numbers of characters revealed
 ** Parameters: character nonvowel, secret_message, game_message
 ** Pre-Conditions: the nonvowel must be a non-vowel letter
 ** Post-Conditions: count the numbers of characters guessed and reveal game_message
 *********************************************************************/
int count_correct(char nonvowel, string secret_message, string &game_message){
	int count = 0;
	// Loop: for every character, if it equals to user input, it reveal the letter from the underlines
	for(int i = 0; i < secret_message.length(); i++){
		if(secret_message.at(i) == nonvowel){
			count++;
			reveal_message(i, game_message, nonvowel);
		}
	}
	return count;
}

/*********************************************************************
 ** Function: reveal_message
 ** Description: replace the underline with character guessed right
 ** Parameters: the position of the string, game_message, nonvowel character
 ** Pre-Conditions: the user must guessed at least a character right
 ** Post-Conditions: replace the
 *********************************************************************/
void reveal_message(int i, string &game_message, char nonvowel){
	// Replace the underline to the character according to input
	game_message.replace(2 * i + 1, 1, string (1, nonvowel));
}

/*********************************************************************
 ** Function: solve
 ** Description: if the user guess the right message, he gets the money
 ** Parameters: secret_message, boolean end_turn, boolean end_round
 ** Pre-Conditions: the user choose to solve the puzzle
 ** Post-Conditions: if the user guessed it right, end round he gets money, if he guessed it wrong, end round he sucks
 *********************************************************************/
void solve(string secret_message, bool &end_turn, bool &end_round){
	string player_message;
	get_message(player_message);
	if(player_message.compare(secret_message) == 0){
		end_round = true;
		end_turn = true;
	}else{
		end_turn = true;
		cout << "You are WRONG !" << endl;
	}
}

/*********************************************************************
 ** Function: buy_vowel
 ** Description: ask user for a vowel and return how many characters revealed
 ** Parameters: secret_message, game_message, player round money
 ** Pre-Conditions: the user must have at least 10 bucks
 ** Post-Conditions: the message revealed, the money taken, and return how many found
 *********************************************************************/
void buy_vowel(string secret_message, string &game_message, int &player_rmoney){
	// For user to spend 10 dollars to guess a vowel and return the amount characters revealed
	char vowel; bool vowel_pass = true; int vowel_found;
	while(vowel_pass == true){
		cout << "Guess a vowel letter: ";
		cin >> vowel;
		if (check_nonvowel(vowel) == false){
			vowel_pass = false;
		}else{
			cout << "Please enter a vowel letter!" << endl;
		}
	}
	// After getting the fight user input, get the number of occurences and return
	vowel_found = count_correct(vowel, secret_message, game_message);
	player_rmoney -= 10;
	cout << vowel_found << " found. Total: $" << player_rmoney << endl;
	cout << "The message is" << game_message << endl << endl;
}
