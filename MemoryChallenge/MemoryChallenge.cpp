#include "MemoryChallenge.h"

//Jean Toole, 28147790 - FIT1048 Assignment 1, Part 2


//TO DO: output to file for running leaderboard, add comments


int main()
{
	//main method variables
	bool testMode, gameOver = false;
	char gameBoard[36] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R' };
	char visBoard[36];
	char choice;

	srand(time(NULL));

	//loops main menu following a win or [R]eturn to main menu:
	while (!gameOver)
	{
		random_shuffle(&gameBoard[0], &gameBoard[35]);		//random_shuffle swaps memory addresses of array elements

		for (int i = 0; i < 36; i++)						//loop to populate incrementing indexes of visBoard array with '~'
		{
			visBoard[i] = '~';
		}

		testMode = false;									//resets testMode boolean to false at commencement of while loop
		system("cls");
		cout << "Welcome to\n";
		cout << " ___  ___                                  _____ _           _ _                         ___________\n";
		cout << " |  \\/  |                                 /  __ \\ |         | | |                       |____ |  _  \\\n";
		cout << " | .  . | ___ _ __ ___   ___  _ __ _   _  | /  \\/ |__   __ _| | | ___ _ __   __ _  ___      / / | | |\n";
		cout << " | |\\/| |/ _ \\ '_ ` _ \\ / _ \\| '__| | | | | |   | '_ \\ / _` | | |/ _ \\ '_ \\ / _` |/ _ \\     \\ \\ | | |\n";
		cout << " | |  | |  __/ | | | | | (_) | |  | |_| | | \\__/\\ | | | (_| | | |  __/ | | | (_| |  __/ .___/ / |/ / \n";
		cout << " \\_|  |_/\\___|_| |_| |_|\\___/|_|   \\__, |  \\____/_| |_|\\__,_|_|_|\\___|_| |_|\\__, |\\___| \\____/|___/  \n";
		cout << "                                    __/ |                                    __/ |                   \n";
		cout << "                                   |___/                                    |___/                    \n\nNow with Improved Graphics!!!\n\n[N]ew game, [T]est mode, or [Q]uit: ";
		cin >> choice;
		choice = tolower(choice);							//converts char to lowercase, in case different case chars are entered.

		if (choice == 'n')
		{
			playGame(testMode, visBoard, gameBoard);		//calls playgame function, parsing required variables
			system("pause");
		}
		else if (choice == 't')
		{
			testMode = true;								//enables test mode, revealing gameBoard above visBoard
			playGame(testMode, visBoard, gameBoard);		//calls playgame function, parsing required variables
			system("pause");
		}
		else if (choice == 'q')
		{
			return 0;										//ends program with no errors
		}
		else                                                //message in case any other char is entered
		{
			cout << "You entered something else...\n\n";
			system("pause");
		}
	}
}
//playGame function definition:
void playGame(bool testMode, char visBoard[], char gameBoard[])
{
	//local function variables
	string player1, player2, winner, scoreName1, scoreName2;
	int p1score = 0, p2score = 0;
	int playerTurn;
	int pairsFound = 0;
	bool isPair = false;
	bool win = false;
	

	cout << "\nPlayer 1 name: ";
	cin >> player1;
	scoreName1 = player1;						//assigns player's name to scoreboard

	cout << "\nPlayer 2 name: ";
	cin >> player2;
	scoreName2 = player2;						//assigns player's name to scoreboard

	system("cls");

	cout << "Why hello, players. Here are the Game Rules:\n" << endl; 
	cout << "1. The 'Game Master' randomly decides who starts first\n\n";
	cout << "2. Players take turns revealing 2 cards each,\n   by entering coordinates of the Game Board separated by a space for each card.\n";
	cout << "   Choose the row coordinate first, then the column coordinate like this: 2 3  \n\n";
	cout << "3. If a player scores a matching pair during their turn, they are awarded 1 point, and get to choose again.\n\n";
	cout << "4. Whoever gets the highest score after 18 pairs have been revealed is the Winner.\n\n";

	system("pause");

	playerTurn = rand() % 2 + 1;			//picks number between 0 and 1, + 1 (to make it 1 or 2) to decide who starts first
	
	//win and matching pair conditions loop	
	while (!win)
	{
		system("cls");

		if (pairsFound > 17)				//ends !win loop
		{
			(win = true);					
		}
		else if (playerTurn == 1)			//alternates player to player1
		{
			isPair = playerRunTurn(testMode, player1, scoreName1, scoreName2, visBoard, gameBoard, p1score, p2score);
			if (isPair)						//checks if matching pair boolean is returned from playerRunTurn function
			{
				p1score++;					//increments player1's score
				pairsFound++;				//increments the matching pairs counter
			}
			else
			{
				playerTurn++;				//increments the turn counter to switch players
			}
			
		}
		else if (playerTurn == 2)			//alternates player to player2
		{
			isPair = playerRunTurn(testMode, player2, scoreName1, scoreName2, visBoard, gameBoard, p1score, p2score);
			if (isPair)						//checks if matching pair boolean is returned from playerRunTurn function
			{
				p2score++;					//increments player2's score
				pairsFound++;				//increments the matching pairs counter
			}
			else
			{
				playerTurn--;				//decrements the turn counter to switch players if no matching pair was found
			}
		}
				
	}
	
	system("cls");

	if (p1score > p2score)					//loop to determine which player won
	{
		winner = player1;
	}
	else if (p1score == p2score)			//in case there is a draw between players
	{
		winner = "TIE";
		cout << "\n\n\OMG!!! CONGRATULATIONS " << player1 << " & " << player2 << " YOU TIED!!!\n\n\n";
	}
	else
	{
		winner = player2;					//alternative scenario
	}

	if (winner != "TIE")					//when not a draw
	{
		cout << "\n\nOMG!!! CONGRATULATIONS " << winner << " YOU WIN!!!\n\n\n";
	}
}
//drawGameBoard function definition:
void drawGameBoard(bool testMode, char visBoard[], char gameBoard[])
{
	if (testMode == true)					//test mode scenario
	{
		cout << "TEST MODE ACTIVE\n\n";
		
		//this loop cuts the array into chunks of 6 and prints them in a grid
		cout << "    0 1 2 3 4 5" << endl;

		for (int i = 0; i < 6; i++)						//outer loop that prints the coordinates left of the board
		{
			cout << "  " << i << " ";					//prints number, then adds space for formatting
			for (int j = 0; j < 6; j++)					//loops through block of 6 indexes of array
			{
				cout << gameBoard[j + (6 * i)] << " ";	//adds 6 * i to index, to increment block of 6 elements in array
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	
	//this loop cuts the array into chunks of 6 and prints them in a grid
	cout << "    0 1 2 3 4 5" << endl;
	
	for (int i = 0; i < 6; i++)							//outer loop that prints the coordinates left of the board
	{
		cout << "  " << i << " ";						//prints number, then adds space for formatting
		for (int j = 0; j < 6; j++)						//loops through block of 6 indexes of array
		{
			cout << visBoard[j + (6 * i)] << " ";		//adds 6 * i to index, to increment block of 6 elements in array
		}
		cout << endl;
	}
}
//playerRunTurn function definition:
bool playerRunTurn(bool testMode, string name, string scoreName1, string scoreName2, char visBoard[], char gameBoard[], int p1score, int p2score)
{
	int coord1, coord2, coord3, coord4;					//local variables for guesses

	cout << "Player 1 Score: " << p1score << " (" << scoreName1 << ") \t\t\tPlayer 2 Score: " << p2score << " (" << scoreName2 << ")\n\n\n";
	
	drawGameBoard(testMode, visBoard, gameBoard);	//calls drawGameBoard function
	
	bool validGuess = false;						//sets validguess boolean

	cout << "\n" << name << ", pick your first card (coordinates separated by a space): ";

	while (!validGuess)								//loops while not a valid guess, for input validation
	{
		cin >> coord1 >> coord2;
		if (cin.fail())								//scenario when input doesn't match data type
		{
			cin.clear();							// resets fail flag
			cin.ignore();							// flushes cin buffer
			cout << "\nYou've entered an invalid character, must be numeric. Choose again: ";
		}
		else
		{
			if (visBoard[(coord1 * 6) + coord2] != '~')		//scenario when used coords are selected
			{
				cout << "\nThese coordinates have already been guessed. Choose again: ";
			}
			else if ((coord1 < 0) || (coord2 < 0) || (coord1 > 5) || (coord2 > 5))		//scenario when coords are out of bounds
			{
				cout << "\nThese coordinates are out of bounds. Choose again: ";
			}
			else
			{
				validGuess = true;							//determines guess to be valid
			}
		}
	}
	system("cls");

	visBoard[(coord1 * 6) + coord2] = gameBoard[(coord1 * 6) + coord2];			//reveals characters at matching indexes

	cout << "Player 1 Score: " << p1score << " (" << scoreName1 << ") \t\t\tPlayer 2 Score: " << p2score << " (" << scoreName2 << ")\n\n\n";

	drawGameBoard(testMode, visBoard, gameBoard);		//calls drawGameBoard function

	validGuess = false;									//resets validguess boolean

	cout << "\n" << name << ", pick your Second card (coordinates separated by a space): ";

	while (!validGuess)									//loops while not a valid guess, for input validation
	{
		cin >> coord3 >> coord4;
		if (cin.fail())									//scenario when input doesn't match data type
		{
			cin.clear();
			cin.ignore();
			cout << "\nYou've entered an invalid character, must be numeric. Choose again: ";
		}
		else
		{
			if (visBoard[(coord3 * 6) + coord4] != '~')		//scenario when used coords are selected
			{
				cout << "\nThese coordinates have already been guessed. Choose again: ";
			}
			else if ((coord3 < 0) || (coord4 < 0) || (coord3 > 5) || (coord4 > 5))	//scenario when coords are out of bounds
			{
				cout << "\nThese coordinates are out of bounds. Choose again: ";
			}
			else
			{
				validGuess = true;							//determines guess to be valid
			}
		}
	}
	system("cls");

	visBoard[(coord3 * 6) + coord4] = gameBoard[(coord3 * 6) + coord4];	//reveals characters at matching indexes

	cout << "Player 1 Score: " << p1score << " (" << scoreName1 << ") \t\t\tPlayer 2 Score: " << p2score << " (" << scoreName2 << ")\n\n\n"; //\t inserts a tab

	drawGameBoard(testMode, visBoard, gameBoard);			//calls drawGameBoard function

	if (visBoard[(coord1 * 6) + coord2] == visBoard[(coord3 * 6) + coord4])		//comparison to determine matching chars
	{
		visBoard[(coord1 * 6) + coord2] = ' ';				//sets matched pairs to blank
		visBoard[(coord3 * 6) + coord4] = ' ';				//sets matched pairs to blank
		cout << "\nERMAGERD!!! " << name << " YOU FOUND A MATCH! I CAN'T BELIEVE IT!\n";
		system("pause");
		return true;
	}
	else
	{
		cout << "\nSorry " << name << ", the cards didn't match.\n";
		visBoard[(coord1 * 6) + coord2] = '~';				//resets coords to ~ if not a match
		visBoard[(coord3 * 6) + coord4] = '~';				//resets coords to ~ if not a match
		system("pause");
		return false;
	}

}


