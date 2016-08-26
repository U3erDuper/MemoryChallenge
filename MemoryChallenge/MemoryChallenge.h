#ifndef MEM_H
#define MEM_H

#include <iostream>
#include <algorithm>					//required for random_shuffle function
#include <string>
#include <ctime>						//required to initialise srand function


using namespace std;

//custom function declarations, and required data types:

void playGame(bool, char[], char[]);

void drawGameBoard(bool, char[], char[]);

bool playerRunTurn(bool, string, string, string, char[], char[], int, int);


#endif
