#include "MemoryChallenge.h"

// Jean Toole 280147790 Assignment 1


//TO DO: code an end condition, data validation, can't reuse coordinates, output to file for running leaderboard, add comments


int main()
{
	
	char gameBoard[36] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R' };
	char visBoard[36];
	char choice;
	bool testMode;
	bool gameOver = false;

	srand(time(NULL));

	//loops main menu following a win or [R]eturn to main menu
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
		choice = tolower(choice);

		if (choice == 'n')
		{
			playGame(testMode, visBoard, gameBoard);
			system("pause");
		}

		else if (choice == 't')
		{
			testMode = true;
			playGame(testMode, visBoard, gameBoard);
			system("pause");
		}
		else if (choice == 'q')
		{
			return 0;
		}
		else
		{
			cout << "You entered something else...\n\n";
			system("pause");
		}
	}
}

void playGame(bool testMode, char visBoard[], char gameBoard[])
{
	string player1, player2;
	int p1score = 0, p2score = 0;
	
	int playerTurn;
	int pairsFound = 0;
	bool isPair = false;
	bool win = false;
	

	cout << "\nPlayer 1 name: ";
	cin >> player1;

	cout << "\nPlayer 2 name: ";
	cin >> player2;

	system("cls");

	cout << "Why hello, players. Here are the Game Rules:\n" << endl; 
	cout << "1. The 'Game Master' randomly decides who starts first\n\n";
	cout << "2. Players take turns revealing 2 cards each,\n   by entering coordinates of the Game Board separated by a space for each card.\n";
	cout << "   Choose the row coordinate first, then the column coordinate like this: 2 3  \n\n";
	cout << "3. If a player scores a matching pair during their turn, they are awarded 1 point.\n\n";
	cout << "4. Whoever gets the highest score after 18 pairs have been revealed is the Winner.\n\n";

	system("pause");

	playerTurn = rand() % 2 + 1;			//picks number between 0 and 1, + 1 (to make it 1 or 2)
	
		
	while (!win)
	{
		system("cls");

		if (playerTurn == 1)
		{
			isPair = player1Turn(testMode, player1, visBoard, gameBoard, p1score, p2score);
			if (isPair)
			{
				p1score++;
				pairsFound++;
				
			}

			else
			{
				playerTurn++;
			}
			
		}
		else if (playerTurn == 2)
		{
			isPair = player2Turn(testMode, player2, visBoard, gameBoard, p1score, p2score);
			if (isPair)
			{
				p2score++;
				pairsFound++;
				
			}
			
			else
			{
				playerTurn--;
			}
		}
				
	}
	
}
void drawGameBoard(bool testMode, char visBoard[], char gameBoard[])
{
	if (testMode == true)
	{
		cout << "TEST MODE ACTIVE\n\n";
		
		//this function cuts the array into chunks of 6 and prints them in a grid
		cout << "    0 1 2 3 4 5" << endl;

		for (int i = 0; i < 6; i++)						//outer loop that prints the coordinates left of the board
		{
			cout << "  " << i << " ";					//prints number, then adds space for formatting
			for (int j = 0; j < 6; j++)					//loops through block of 6 indexes of array
			{
				cout << gameBoard[j + (6 * i)] << " ";	//adds 6*i to index, to increment block of 6 elements in array
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	
	//this function cuts the array into chunks of 6 and prints them in a grid
	cout << "    0 1 2 3 4 5" << endl;
	
	for (int i = 0; i < 6; i++)							//outer loop that prints the coordinates left of the board
	{
		cout << "  " << i << " ";						//prints number, then adds space for formatting
		for (int j = 0; j < 6; j++)						//loops through block of 6 indexes of array
		{
			cout << visBoard[j + (6 * i)] << " ";		//adds 6*i to index, to increment block of 6 elements in array
		}
		cout << endl;
	}
}

bool player1Turn(bool testMode, string player1, char visBoard[], char gameBoard[], int p1score, int p2score)
{
	int coord1, coord2, coord3, coord4;

	cout << "Player 1 Score: " << p1score << "\t\t\t\tPlayer 2 Score: " << p2score << endl << endl;
	if (testMode)
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}
	else
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}

	
	cout << "\n" << player1 << ", pick your first card: ";

	cin >> coord1 >> coord2;
	system("cls");

	visBoard[(coord1 * 6) + coord2] = gameBoard[(coord1 * 6) + coord2];

	cout << "Player 1 Score: " << p1score << "\t\t\t\tPlayer 2 Score: " << p2score << endl << endl;

	if (testMode)
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}
	else
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}

	cout << "\n" << player1 << ", pick your second card: ";

	cin >> coord3 >> coord4;
	system("cls");

	visBoard[(coord3 * 6) + coord4] = gameBoard[(coord3 * 6) + coord4];

	cout << "Player 1 Score: " << p1score << "\t\t\t\tPlayer 2 Score: " << p2score << endl << endl; //\t inserts a tab

	if (testMode)
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}
	else
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}

	if (visBoard[(coord1 * 6) + coord2] == visBoard[(coord3 * 6) + coord4])
	{
		visBoard[(coord1 * 6) + coord2] = ' ';
		visBoard[(coord3 * 6) + coord4] = ' ';
		cout << "\nERMAGERD... " << player1 << " YOU FOUND A MATCH! I CAN'T BELIEVE IT!\nThe computer will shut down now, it has had too much excitement for one day.\n";
		system("pause");
		return true;
	}

	else
	{
		cout << "\nSorry " << player1 << ", the cards didn't match.\n";
		visBoard[(coord1 * 6) + coord2] = '~';
		visBoard[(coord3 * 6) + coord4] = '~';
		system("pause");
		return false;

	}


	
}

bool player2Turn(bool testMode, string player2, char visBoard[], char gameBoard[], int p1score, int p2score)
{
	int coord1, coord2, coord3, coord4;

	cout << "Player 1 Score: " << p1score << "\t\t\t\tPlayer 2 Score: " << p2score << endl << endl;

	if (testMode)
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}
	else
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}


	cout << "\n" << player2 << ", pick your first card: ";

	cin >> coord1 >> coord2;
	system("cls");

	visBoard[(coord1 * 6) + coord2] = gameBoard[(coord1 * 6) + coord2];

	cout << "Player 1 Score: " << p1score << "\t\t\t\tPlayer 2 Score: " << p2score << endl << endl;

	if (testMode)
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}
	else
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}

	cout << "\n" << player2 << ", pick your second card: ";

	cin >> coord3 >> coord4;
	system("cls");

	visBoard[(coord3 * 6) + coord4] = gameBoard[(coord3 * 6) + coord4];

	cout << "Player 1 Score: " << p1score << "\t\t\t\tPlayer 2 Score: " << p2score << endl << endl;

	if (testMode)
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}
	else
	{
		drawGameBoard(testMode, visBoard, gameBoard);
	}

	if (visBoard[(coord1 * 6) + coord2] == visBoard[(coord3 * 6) + coord4])
	{
		visBoard[(coord1 * 6) + coord2] = ' ';
		visBoard[(coord3 * 6) + coord4] = ' ';
		cout << "ERMAGERD.. " << player2 << " YOU FOUND A MATCH! I CAN'T BELIEVE IT!\nThe computer will shut down now, it has had too much excitement for one day.\n";
		system("pause");
		return true;
	}

	else
	{
		cout << "\nSorry " << player2 << ", the cards didn't match.\n";
		visBoard[(coord1 * 6) + coord2] = '~';
		visBoard[(coord3 * 6) + coord4] = '~';
		system("pause");
		return false;

	}
}
