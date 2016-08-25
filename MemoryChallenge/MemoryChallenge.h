#ifndef MEM_H
#define MEM_H

#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

void playGame(bool, char[], char[]);

void drawGameBoard(bool, char[], char[]);

bool player1Turn(bool, string, char[], char[], int, int);

bool player2Turn(bool, string, char[], char[], int, int);


#endif
