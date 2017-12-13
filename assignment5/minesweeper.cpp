/*********************************************************************
 ** Program Filename: minesweeper.cpp
 ** Author: Tsewei Peng
 ** Date: 03/13 2016
 ** Description: This is a game of minesweeper, the user enter the number of rows, columns, mines and play minesweeper !
 ** IMPORTANT NOTE: char *game_board[] is the board displayed to player
 **					char *board[] is the board generated behind the display
 **					bool *rec_board[] is used for the recursion to prevent
 **					recursion won't go back to previous blocks
 ** Input: '-r', number of rounds, '-c', number of columns, '-m', number of mines
 ** Output: The grid of the minesweeper and result from every move by the user
 *********************************************************************/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

bool check_command(int argc, char *argv[], int &row, int &column, int &mines);
bool check_arg(char prog[], char par[], char par_num[], int i, int &row_count, int &column_count, int &mine_count, int &row, int &column, int &mines);
void check_avail(char prog[], int &count, int &par_var, char par[], char num[]);
bool check_arg_num(char prog[], char par[], int &par_var, char num[]);
void new_option(int &row, int &column, int &mines);
bool prompt_row_column(int &row, int &column);
bool prompt_mines(int &mines, int row, int column);
void extract_options(char *input, char row_char[], char column_char[], int space_pos);
void minesweeper(int row, int column, int mines);
char **create_board(int row, int column);
char **create_board(int row, int column);
bool **create_rec_board(int row, int column);
void delete_array(char *board[], char *game_board[], bool *rec_board[], int row, int column);
void generate_mines(char *board[], int row, int column, int mines);
void generate_num(char *board[], int row, int column);
void play(char *board[], char *game_board[], bool *rec_board[], int row, int column, int mines, bool &game_end);
void flag(char *game_board[], int row, int column);
bool open(char *board[], char *game_board[], bool *rec_board[], int row, int column);
void open_num(char *game_board[], char *board[], int urow, int ucolumn, int row);
bool win(char *game_board[], char *board[], int row, int column);
void rec_open(char *board[], char *game_board[], bool *rec_board[], int row, int column, int x, int y);
char *get_input();
void get_coor(char *input, int &urow, int &ucolumn, int row, int column);
bool num_error(char str[]);
bool mine_num_error(char str[], int row, int column);
bool num_space_error(char str[]);
void print_board(char *board[], int row, int column);
void print_main(char *board[], int row, int column);
void print_x_coor(int row, int column);

/*********************************************************************
 ** Function: main
 ** Description: this is where the program is initiated
 ** Parameters: integer argc, arrays of c-string *argv[]
 ** Pre-Conditions: valid command line
 ** Post-Conditions: The program ends normally
 *********************************************************************/
int main(int argc, char *argv[]){
	int row, column, mines, start = 0;
	char *restart;
	srand(time(NULL));
	// If not passing command line check, quit program
	if(check_command(argc, argv, row, column, mines) == false){
		return 0;
	}
	while(1){
		// Start minesweeper
		minesweeper(row, column, mines);
		while(1){
			// Error check if the user input is 1 or 2
			cout << "Do you want to play again (1-yes, 2-no): ";
			restart = get_input();
			if(num_error(restart) == false){
				if(atoi(restart) == 1){
					delete [] restart;
					break;
				}
				else{
					delete [] restart;
					return 0;
				}
			}else {
				delete [] restart;
			}
		}
		// If the user choose 1, re-prompt for the user input
		new_option(row, column, mines);
	}
}

/*********************************************************************
 ** Function: check_command
 ** Description: The root function for all the error handling for command line
 ** Parameters: integer argc, c-string array *argv[], numbers of rows, columns, mines
 ** Pre-Conditions: The number of argument argc must be 7
 ** Post-Conditions: The error handling is complete and numbers assigned to variables, return false if not valid, return true if valid
 *********************************************************************/
bool check_command(int argc, char *argv[], int &row, int &column, int &mines){
	// Make sure each command is only used once
	int row_count = 1, column_count = 1, mine_count = 1;
	// Make sure right number of arguments
	if(argc != 7){
		cout << "Usage: " << argv[0] << " [-r num] [-c num] [-m num] <order_not_matter>" << endl;
		return false;
	}

	// Check if the argument -r -c -m are vaild
	for(int i = 1; i < 6; i+=2){
		// If not valid, exit the program
		if(check_arg(argv[0], argv[i], argv[i+1], i, row_count, column_count, mine_count, row, column, mines) == false){
			return false;
		}
	}
	// Return error message if the mine is more than row times column
	if(mines >= row * column){
		cout << "Usage: " << argv[0] << " -m num too_big" << endl;
		return false;
	}
	return true;
}

/*********************************************************************
 ** Function: check_arg
 ** Description: This fnction checks if all the parameter appear more than once, also pass it into check_avail() for more error handling
 ** Parameters: c-string prog, c-string par, c-string, par_num, integer i, integer row_count, integer column_count, integer mine_count, numbers of rows, columns and mines
 ** Pre-Conditions: The parameter -r, -c, -m must only appear once
 ** Post-Conditions: return false if not valid, return true if valid
 *********************************************************************/
bool check_arg(char prog[], char par[], char par_num[], int i, int &row_count, int &column_count, int &mine_count, int &row, int &column, int &mines){
	// If the command line parameter is not -r or -c or -m
	if(!(strcmp(par, "-r") == 0 || strcmp(par, "-c") == 0 || strcmp(par, "-m") == 0 )){
		cout << "Usage: " << prog << " [-r num] [-c num] [-m num] <order_not_matter>" << endl;
		return false;
	}else if(strcmp(par, "-r") == 0){
		// If the comman line parameter is -r
		check_avail(prog, row_count, row, par, par_num);
	}else if(strcmp(par, "-c") == 0){
		// If the comman line parameter is -c
		check_avail(prog, column_count, column, par, par_num);
	}else{
		// If the comman line parameter is -m
		check_avail(prog, mine_count, mines, par, par_num);
	}
		// Quit if parameter used more than once
	if(5 - 2 * (row_count + column_count + mine_count) != i){
		return false;
	}
	return true;
}

/*********************************************************************
 ** Function: check_avail
 ** Description: if the count for the parameter is 1, then pass it to check_art_num
 ** Parameters: c-string prog, integer count, integer par_var, c-string par, c-string num
 ** Pre-Conditions: The count must be 1 for the command line parameter
 ** Post-Conditions: return error message if the count is not 1
 *********************************************************************/
void check_avail(char prog[], int &count, int &par_var, char par[], char num[]){
	if(count == 1){
		count--;
		// if it doesn't pass the number pass, quit program
		if(check_arg_num(prog, par, par_var, num) == false){
			count++;
			return;
		}
	// Convert the c-string to integer
	par_var = atoi(num);
	}else{
		//cout << "Please include only 1 argument of " << par << " !" << endl;
		cout << "Usage: " << prog << " " << par << " < one_argument_only>" << endl;
	}
}

/*********************************************************************
 ** Function: check_arg_num
 ** Description: check argv[2] argv[4] argv[6] if they are valid numbers
 ** Parameters: c-string prog, c-string par, integer par_var, c-string num
 ** Pre-Conditions: The c-string num must be valid numbers, and also the parameter must be -r, -c, or -m
 ** Post-Conditions: return false if the number is not valid, or row number is more than 20, column number is more than 25, mine number is more than 125, else return true
 *********************************************************************/
bool check_arg_num(char prog[], char par[], int &par_var, char num[]){
	// Check if all the characters are in number range
	for(int i = 0; i < strlen(num); i++){
		if(!(num[i] <= '9' && num[i] >= '0')){
			cout << "Usage: " << prog << " " << par << " num <num_not valid>" << endl;
			return false;
		}
	}
	// If the parameter is -r, the number cannot be over 20
	if(strcmp(par, "-r") == 0){
		if(atoi(num) > 20){
			cout << "Usage: " << prog << " " << par << " num <num <= 20>" << endl;
			return false;
		}
	}
	// If the parameter is -c, the number cannot be over 25
	if(strcmp(par, "-c") == 0){
		if(atoi(num) > 25){
			cout << "Usage: " << prog << " " << par << " num <num <= 25>" << endl;
			return false;
		}
	}
	// If the parameter is -m, the number cannot be over 125
	else{
		if(atoi(num) > 125){
			cout << "Usage: " << prog << " " << par << " num <num <= 125>" << endl;
		}
	}
	return true;
}

/*********************************************************************
 ** Function: new_option
 ** Description: Prompt user for number of rows, columns and mines for another new game
 ** Parameters: integer row, column, mines
 ** Pre-Conditions: none
 ** Post-Conditions: The new numbers of rows, columns and mines are assigned to variables
 *********************************************************************/
void new_option(int &row, int &column, int &mines){
	bool valid;
	// Keep prompting the rows and columns until valid
	while(1){
		valid = prompt_row_column(row, column);
		if(valid){
			break;
		}
	}
	// Keep prompting the number of mines until valid
	while(1){
		valid = prompt_mines(mines, row, column);
		if(valid){
			break;
		}
	}
}

/*********************************************************************
 ** Function: prompt_row_column
 ** Description: Prompt the user for number of row and columns
 ** Parameters: integer row, integer column
 ** Pre-Conditions: none
 ** Post-Conditions: The user input must be 2 valid numbers with 1 space in between, will return false if the numbers input is not valid, or return true if the numbers are valid
 *********************************************************************/
bool prompt_row_column(int &row, int &column){
	// Set up input strea, row char and column char
	char *input, row_char[5], column_char[5];
	// The position of the space
	int space_pos = 0;
	cout << "How many rows, columns? (Please enter a space between the 2 numbers)\n";
	// Get the input, and error handle
	input = get_input();
	if(num_space_error(input) == false){
		extract_options(input, row_char, column_char, space_pos);
		delete [] input;
		if(atoi(row_char) <= 20 && atoi(column_char) <= 25){
			// If valid, convert to integer and put it into row and column
			row = atoi(row_char);
			column = atoi(column_char);
			return true;
		}else{
			cout << "Max rows is 20, max column is 25 !" << endl;
			return false;
		}
	}else{
		delete [] input;
		return false;
	}
}

/*********************************************************************
 ** Function: prompt_mines
 ** Description: Prompt the user for number of mines
 ** Parameters: integer mines, integer row, integer column
 ** Pre-Conditions: The integer row and column must be valid
 ** Post-Conditions: The numbers of mine is assigned and return true, or the number of mines is not valid and return false
 *********************************************************************/
bool prompt_mines(int &mines, int row, int column){
	char *input;
	cout << "How many mines? ";
	input = get_input();
	if(mine_num_error(input, row, column) == false){
		mines = atoi(input);
		delete [] input;
		return true;
	}else{
		delete [] input;
		return false;
	}
}

/*********************************************************************
 ** Function: extract_options
 ** Description: This function extract 2 integers from the user input for row, column. For example, the function will extract a 3 and 5 for input 3 5.
 ** Parameters: c-string input, c-string row_char, c-string column_char, integer space_pos
 ** Pre-Conditions: none
 ** Post-Conditions: Extract 2 integers values from the c-string and put them into 2 seperate c-strings.
 *********************************************************************/
void extract_options(char *input, char row_char[], char column_char[], int space_pos){
	// Extract the row and column from the cstring
	for(int i = 0; i < strlen(input); i++){
		if(input[i] == ' '){
			break;
		}else{
			space_pos++;
		}
	}
	// Extract first number characters
	for(int i = 0; i < space_pos; i++){
		row_char[i] = input[i];
	}
	// Extract second number characters
	for(int i = space_pos + 1; i < strlen(input); i++){
		column_char[i - space_pos - 1] = input[i];
	}
	row_char[space_pos] = '\0';
	column_char[strlen(input) - space_pos - 1] = '\0';
}

/*********************************************************************
 ** Function: minesweeper
 ** Description: This function runs the main minesweeper program
 ** Parameters: integer row, integer column, integer mines
 ** Pre-Conditions: The number of rows columns and mines must be valid
 ** Post-Conditions: One small game ends, either the user wins or the user loses
 *********************************************************************/
void minesweeper(int row, int column, int mines){
	char **board, **game_board;
	bool **rec_board, game_end = false;
	// Add two row and two column for safe spot during recursion
	row += 2;
	column += 2;
	// Create mineboard, gameboard (displayed), rec_board (for recursion, bool board)
	cout << endl;
	board = create_board(row, column);
	game_board = create_board(row, column);
	rec_board = create_rec_board(row, column);
	print_board(game_board, row, column);
	// Generate mines, and place numbers on board;
	generate_mines(board, row, column, mines);
	generate_num(board, row, column);
	// Start the minesweeper game
	while(game_end == false){
		play(board, game_board, rec_board, row, column, mines, game_end);
	}
	delete_array(board, game_board, rec_board, row, column);
}

/*********************************************************************
 ** Function: **create_board
 ** Description: This function create a 2-d dynamic array of characters for the minesweeper board
 ** Parameters: integer row, integer column
 ** Pre-Conditions: The integer row and column must be valid
 ** Post-Conditions: return the 2-d array based on the input of numbers of rows and columns
 *********************************************************************/
char **create_board(int row, int column){
	char **board;
	// Create board of space
	board = new char*[row];
	for(int i = 0; i < row; i++){
		board[i] = new char [column];
	}
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			board[i][j] = ' ';
		}
	}
	return board;
}

/*********************************************************************
 ** Function: **create_rec_board
 ** Description: This function create a 2-d dynamic array of booleans for the recursion
 ** Parameters: integer row, integer column
 ** Pre-Conditions: The integer row and column must be valid
 ** Post-Conditions: Return the 2-d array based on the input of numbers of rows and columns
 *********************************************************************/
bool **create_rec_board(int row, int column){
	bool **board;
	// Create board of false for recursion
	board = new bool*[row];
	for(int i = 0; i < row; i++){
		board[i] = new bool [column];
	}
	for(int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			board[i][j] = false;
		}
	}
	return board;
}

/*********************************************************************
 ** Function: delete_array
 ** Description: For freeing the 2-d array
 ** Parameters: 2-d array *board[], 2-d array *game_board[], 2-d array *rec_board[], integer row, integer column
 ** Pre-Conditions: All the 2-d arrays must be valid, and numbers of rows and columns must be valid too
 ** Post-Conditions: All the dynamic arrays used in one small game of minesweeper are all freed
 *********************************************************************/
void delete_array(char *board[], char *game_board[], bool *rec_board[], int row, int column){
	for(int i = 0; i < row; i++){
		delete [] board[i];
	}
	delete [] board;
	for(int i = 0; i < row; i++){
		delete [] game_board[i];
	}
	delete [] game_board;
	for(int i = 0; i < row; i++){
		delete [] rec_board[i];
	}
	delete [] rec_board;
}

/*********************************************************************
 ** Function: generate_mines
 ** Description: generate mines on the 2-d array board
 ** Parameters: integer row, integer column, integer mines
 ** Pre-Conditions: The parameters must be valid
 ** Post-Conditions: The board 2-d array must be filled with mines with numbers of mines same as user input
 *********************************************************************/
void generate_mines(char *board[], int row, int column, int mines){
	row -= 2;
	column -= 2;
	int spot = row * column;
	int mine_spot, mine_row, mine_column;
	// Generate number for the spot on the board
	for(int i = 0; i < mines; i++){
		mine_spot = rand() % spot + 1;
		mine_column = mine_spot % column;
		if(mine_column == 0){
			mine_column = column;
		}
		mine_row = (mine_spot - mine_column)/column + 1;
		if(board[mine_row][mine_column] != '*'){
			board[mine_row][mine_column] = '*';
		}else{
			i--;
		}
	}
}

/*********************************************************************
 ** Function: generate_num
 ** Description: generate numbers on the 2-d rray board wherever there is no mine
 ** Parameters: 2-d array board, integer row, integer column
 ** Pre-Conditions: The parameters must be valid and the mines must be setup
 ** Post-Conditions: The board is finally set up with mines and numbers
 *********************************************************************/
void generate_num(char *board[], int row, int column){
	int count;
	for(int i = 1; i < row - 1; i++){
		for(int j = 1; j < column - 1; j++){
			// For every spot check the 3*3 box around it
			if(board[i][j] != '*'){
				count = 0;
				for(int k = i - 1; k <= i + 1; k++){
					for(int l = j - 1; l <= j + 1; l++){
						if(board[k][l] == '*'){
							count++;
						}
					}
				}
				board[i][j] = '0' + count;
			}
		}
	}
}

/*********************************************************************
 ** Function: play
 ** Description: This is the main playing function of the program
 ** Parameters: 2-d array board, 2-d array game_board, 2-d array rec_board, integer row, integer column, integer mines, boolean game_end
 ** Pre-Conditions: The boards must be setup and parameters valid
 ** Post-Conditions: The user wins or loses
 *********************************************************************/
void play(char *board[], char *game_board[], bool *rec_board[], int row, int column, int mines, bool &game_end){
	char *choice;
	// Keep prompting for user choices
	while(1){
		while(1){
			// Error handle for 1 and 2
			cout << "Do you want to [1. Flag or unflag] or [2. Open]: ";
			choice = get_input();
			if(num_error(choice) == false){
				break;
			} else {
				delete [] choice;
			}
		}
		if(choice[0] == '1'){
			flag(game_board, row, column);
			delete [] choice;
			break;
		}else if(choice[0] = '2'){
			if(open(board, game_board, rec_board, row, column) == true){
				game_end = true;
			}
			delete [] choice;
			break;
		}else{
			delete [] choice;
			cout << "Please enter '1' or '2' !" << endl;
		}
	}
}

/*********************************************************************
 ** Function: flag
 ** Description: This function flags or unflags user inputed coordinates
 ** Parameters: 2-d array game_board, integer row, integer column
 ** Pre-Conditions: The board setup
 ** Post-Conditions: flags the coordinate if not flagged, or unflag if flagged
 *********************************************************************/
void flag(char *game_board[], int row, int column){
	int urow, ucolumn;
	char *input;
	get_coor(input, urow, ucolumn, row, column);
	row -= 2;
	column -= 2;
	// Flag
	if(game_board[row - urow + 1][ucolumn] == ' '){
		game_board[row - urow + 1][ucolumn] = '!';
	}
	// Unflag
	else if(game_board[row - urow + 1][ucolumn] == '!'){
		game_board[row - urow + 1][ucolumn] = ' ';
	}else{
		cout << "Cannot flag an opened coordinate !" << endl;
	}
	cout << endl;
	print_board(game_board, row + 2, column + 2);
}

/*********************************************************************
 ** Function: open
 ** Description: This function open the user inputed coordinate
 ** Parameters: 2-d array board, 2-d array game_board, 2-d array rec-Board, integer row, integer column
 ** Pre-Conditions: All the boards setup and parameters valid
 ** Post-Conditions: Either the spot is open if it is a number on board, or is recursively opened if it is a 0, or return the function and the user lose if the spot is a mine
 *********************************************************************/
bool open(char *board[], char *game_board[], bool *rec_board[], int row, int column){
	int urow, ucolumn;
	char *input;
	get_coor(input, urow, ucolumn, row, column);
	cout << endl;
	if(board[row - urow - 1][ucolumn] == '*'){
		cout << "You Lost!!!" << endl;
		print_board(board, row, column);
		return true;
	}
	else if(board[row - urow - 1][ucolumn] == '0' && game_board[row - urow - 1][ucolumn] == ' '){
		urow = row - urow - 1;
		rec_open(board, game_board, rec_board, row, column, urow, ucolumn);
	}else{
		open_num(game_board, board, urow, ucolumn, row);
	}
	if(win(game_board, board, row, column) == true){
		// If the player unlock all the numbers on the board, it quit the function
		return true;
	}
	print_board(game_board, row, column);
	return false;
}

/*********************************************************************
 ** Function: open_num
 ** Description: open the coordinate if it is not 0 or a mine
 ** Parameters: 2-d array game_board, 2-d array board, integer urow, integer ucolumn, integer row
 ** Pre-Conditions: All the boards setup and parameters valid
 ** Post-Conditions: Open the board if it is a number other than 0, if the spot is already opened or flagged, return message
 *********************************************************************/
void open_num(char *game_board[], char *board[], int urow, int ucolumn, int row){
	if(game_board[row - urow - 1][ucolumn] == ' '){
		game_board[row - urow - 1][ucolumn] = board[row - urow - 1][ucolumn];
	}else if(game_board[row - urow - 1][ucolumn] >= '0' && game_board[row - urow - 1][ucolumn] <= '9'){
		cout << "This coordinate is opened, please try again !" << endl;
	}else{
		cout << "This coordinate is flagged, please unflag before you open !" << endl;
	}
}

/*********************************************************************
 ** Function: win
 ** Description: Calculate if the user wins the game
 ** Parameters: 2-d array game_board, 2-d array board, integer row, integer column
 ** Pre-Conditions: boards set up, and parameters valid, and also the user just opened a spot
 ** Post-Conditions: return true if the player wins, or false if not won yet
 *********************************************************************/
bool win(char *game_board[], char *board[], int row, int column){
	int game_board_count = 0;
	int board_count = 0;
	for(int i = 1; i < row - 1; i++){
		for(int j = 1; j < column - 1; j++){
			// Get the numbers on the game_board
			if(game_board[i][j] >= '0' && game_board[i][j] <= '9'){
				game_board_count++;
			}
			// Get the numbers on the board
			if(board[i][j] >= '0' && board[i][j] <= '9'){
				board_count++;
			}
		}
	}
	// If they match, the player wins
	if(game_board_count == board_count){
		cout << "Congratulations !!! You win !!!" << endl;
		print_board(board, row, column);
		return true;
	}
	return false;
}

/*********************************************************************
 ** Function: rec_open
 ** Description: recursively spread and open the spots if the spot is a 0
 ** Parameters: 2-d array board, 2-d array game_board, 2-d array rec_board, integer row, integer column, integer x, integer y
 ** Pre-Conditions: The user input a coordinate to open and the spot is a 0
 ** Post-Conditions: The function stops if it already checked the spot, or if the spot is not 0, or if it reach the boundary. Else it will check the 3*3 box around it and spreads.
 *********************************************************************/
void rec_open(char *board[], char *game_board[], bool *rec_board[], int row, int column, int x, int y){
	// Copy the value from game_board to board
	game_board[x][y] = board[x][y];
	if(board[x][y] != '0' || rec_board[x][y] == true || x == 0 || y == 0 || x == row - 1 || y == column - 1){
		return;
	}
	// Set the rec_board to true so it will not be run again
	rec_board[x][y] = true;
	// Run
	for(int i = x - 1; i <= x + 1; i++){
		for(int j = y - 1; j <= y + 1; j++){
			rec_open(board, game_board, rec_board, row, column, i, j);
		}
	}
}

/*********************************************************************
 ** Function: get_input
 ** Description: Get the user input, dynamic array grow 1 by 1
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: return the c-string
 *********************************************************************/
char *get_input(){
	// Create dynamic array that grow
	char c;
	int n = 1;
	char *arr = new char [n];
	char *temp;
	do{
		c = cin.get();
		arr[n-1] = c;
		temp = new char [n+1];
		for(int i = 0; i < n; i++){
			temp[i] = arr[i];
		}
		delete [] arr;
		arr = temp;
		n++;
	}while(c != '\n');
	arr[n-2] = '\0';
	return arr;
}

/*********************************************************************
 ** Function: get_coor
 ** Description: Get the coordinate of the board
 ** Parameters: c-string input, integer urow, integer ucolumn, integer row, integer column
 ** Pre-Conditions: none
 ** Post-Conditions: The user input is put into variables for the coordinate
 *********************************************************************/
void get_coor(char *input, int &urow, int &ucolumn, int row, int column){
	int space_pos = 0;
	char row_char[5], column_char[5];
	while(1){
		cout << "Enter the coordinate:  (Please enter a space between the 2 numbers)" << endl << "row, column: ";
		input = get_input();
		if(num_space_error(input) == false){
			extract_options(input, row_char, column_char, space_pos);
			delete [] input;
			if(atoi(row_char) <= row - 2 && atoi(row_char) > 0 && atoi(column_char) <= column - 2 && atoi(column_char) > 0){
				urow = atoi(row_char);
				ucolumn = atoi(column_char);
				break;
			}
			else{
				cout << "Please enter valid numbers for row and column, with a space in between !" << endl;
			}
		}
		else {
			delete [] input;
		}
	}
}

/*********************************************************************
 ** Function: num_error
 ** Description: error handle the numbers 1 and
 ** Parameters: c-string str
 ** Pre-Conditions: user input a number
 ** Post-Conditions: return false if it is 1 or 2, else return true
 *********************************************************************/
bool num_error(char *str){
	// Check if all characters are numbers
	if(strlen(str) != 1){
		cout << "Please enter '1' or '2' !" << endl;
		return true;
	}
	if(str[0] != '1' && str[0] != '2'){
		cout << "Please enter '1' or '2' !" << endl;
		return true;
	}
	return false;
}

/*********************************************************************
 ** Function: mine_num_error
 ** Description: error handle the number of mines
 ** Parameters: c-string str, integer row, integer column
 ** Pre-Conditions: user input a number of number of mines
 ** Post-Conditions: return false if it is smaller than 125 and must be less than row*column, else return true
 *********************************************************************/
bool mine_num_error(char str[], int row, int column){
	// Check if the mine satisfy the criteria
	if(strlen(str) > 3){
		cout << "Please enter no more than 3 characters !" << endl;
		return true;
	}
	if(strlen(str) == 0) {
		cout << "Please enter the number of mine !" << endl;
		return true;
	}
	for(int i = 0; i < strlen(str); i++){
		if(!(str[i] >= '0' && str[i] <= '9')){
			cout << "Please enter a number !" << endl;
			return true;
		}
	}
	if(atoi(str) >= row * column){
		cout << "Number of mines cannot be more than row times column !" << endl;
		return true;
	}
	return false;
}

/*********************************************************************
 ** Function: num_space_error
 ** Description: Error handle the input with a space in middle
 ** Parameters: c-string str
 ** Pre-Conditions: the user input
 ** Post-Conditions: Return true if the number is not valid, or if the space is in the first position or last, else return false
 *********************************************************************/
bool num_space_error(char str[]){
	// Check if all characters are numbers or spaces
	int space_count = 0;
	if(strlen(str) > 5){
		cout << "Please enter less characters !" << endl;
	}
	for(int i = 0; i < strlen(str); i++){
		if(!(str[i] <= '9' && str[i] >= '0' || str[i] == ' ')){
			cout << "Please include one space and numbers !" << endl;
			return true;
		}else if(str[i] == ' '){
			space_count++;
		}
	}
	if(space_count != 1){
		cout << "Please include one space in between two numbers !" << endl;
		return true;
	}
	if(str[0] == ' ' || str[strlen(str) - 1] == ' '){
		cout << "Please include one space in between two numbers !" << endl;
		return true;
	}
	return false;
}

/********************************************************************
 ** Function: print_board
 ** Description: print the board
 ** Parameters: 2-d array board, integer row, integer column
 ** Pre-Conditions: none
 ** Post-Conditions: print the board
 *********************************************************************/
void print_board(char *board[], int row, int column){
	// Print the board with coordinates
	cout << " -";
	for(int i = 1; i < column - 1; i++){
		cout << "--";
	}
	cout << "-" << endl;
	print_main(board, row, column);
	cout << "  |";
	print_x_coor(row, column);
	cout << endl << endl;
}

/*********************************************************************
 ** Function: print_main
 ** Description: print the main structure of the board
 ** Parameters: 2-d array board, integer row, integer column
 ** Pre-Conditions: none
 ** Post-Conditions: print main structure of the board
 *********************************************************************/
void print_main(char *board[], int row, int column){
	for(int i = 1; i < row - 1; i++){
		if(row - 1 - i < 10){
			cout << " " << row - i - 1;
		}
		else{
			cout << row - i - 1;
		}
		for(int j = 1; j < column - 1; j++){
			cout << "|" << board[i][j];
		}
		cout << "|" << endl;
		if(i == row - 2){
			cout << " -";
		}else{
			cout << "  ";
		}
		for(int j = 1; j < column - 1; j++){
			cout << "--";
		}
		cout << "-" << endl;
	}
}

/*********************************************************************
 ** Function: print_x_coor
 ** Description: print the bottom x coordinate
 ** Parameters: integer row, integer column
 ** Pre-Conditions: none
 ** Post-Conditions: print the bottom x coordinate
 *********************************************************************/
void print_x_coor(int row, int column){
	for(int i = 1; i < column - 1; i++){
		cout << i;
		if(i != column - 2){
			if(i < 9){
				cout << " ";
			}
		}else{
			cout << "|";
		}
	}
}
