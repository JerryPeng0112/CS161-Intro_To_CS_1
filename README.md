# CS161 - Intro to Computer Science 1
## Assignment 1 - Output Numbers & Finance Calculator
#### Output Numbers
**To Compile:** `g++ ./assign1.cpp -o assign1`  
**To Run:** `./assign1`  

This program outputs number results from calculations based on the requirements.
#### Finance Calculator
**To Compile:** `g++ ./finance.cpp -o finance`  
**To Run:** `./finance`  

This financial calculator program can calculate the following:
- Loan Balance
- Continuously Compounded Interest
- Future Value
For each choice, the program asks user for required numbers for calculations, and outputs results from the calculations.

## Assignment 2 - Rover Planetary Exploration
**To Compile:** `g++ ./grid.cpp -o grid`  
**To Run:** `./grid`  

The rover planetary exploration program is a program that shows the steps of rover path on a 4x4 grid.
First the program asks for the starting coordinate and the destination coordinate. Then, it outputs all the steps of the rover paths from starting position to destination.
The rover path starts by moving horizontally, then vertically.

## Assignment 3 - Wheel of Fortune
**To Compile:** `g++ ./wheel.cpp -o wheel`  
**To Run:** `./wheel`  

This is the wheel of fortune game. The goal of the game is to earn money by guessing the hidden phrase correctly. The game supports several players.
First, the program asks users for the number of players, and the number of rounds.
Each round, a user needs to enter a hidden message that is unknown to all players. Once the phrase is saved, every player in turn, can do certain actions. The round ends when a player guesses the hidden phrase correctly.

The following is the players' actions:
1. Spin the wheel & guess a non-vowel letter
2. Buy a vowel letter
3. Solve the puzzle

If the player chooses option 1, the player can spin the wheel, which outputs number ranging from 0 to 21.
If the wheel outputs 0, the player loses the round earning, and loses the turn.
If the wheel outputs 21, the player keeps the round earning, but loses the turn.
If the wheel outputs > 0 and < 21, the player can guess a non-vowel letter. If the non-vowel letter is in the phrase and is not yet revealed, the following amount of money is added to the user's round earning: wheel outputs * the number of letters revealed in the phrase. If the letter is not in the phrase, the player keeps the round earning, but loses the turn.

If the player chooses option 2, the player can spend 10 dollar from round earning and guess a vowel letter. The player does not lose the turn.

If the player chooses option 3: solve the puzzle, the player is prompted to guess the phrase. If the player guesses incorrectly, the player loses the turn and keeps the round earning. If the player guesses correctly, the player wins the turn and deposits the round earning to their game total earning.

After the rounds, the player with highest game total earning wins.

## Assignment 4 - Morse Code Translator
**To Compile:** `g++ ./morse.cpp -o morse`  
**To Run:** `./morse`  

This Morse code translator program can translate between alphabetical text and Morse code
The format for Morse code input is: 3 space between each letter code, and 7 spaces if there is a space character between 2 letter.
Example:
sos sos
...   ---   ...       ...   ---   ...

## Assignment 5 - Minesweeper
**To Compile:** `g++ ./minesweeper.cpp -o minesweeper`  
**To Run:** `./minesweeper [-r #] [-c #] [-m #]`  

This is a classic game of minesweeper.
To run the game, command line arguments are required. -r is the parameter for rows, -c is the parameter for columns, and -m is the parameter for mines. "#" is placeholder for numbers. The order of parameter does not matter.
For example, `./minesweeper -m 15 -c 10 -r 10` means start the game with a board of 10 rows, 10 columns that has 15 mines.
For input that includes 2 numbers, insert a space between 2 numbers.
For example: row, column? 3 5
