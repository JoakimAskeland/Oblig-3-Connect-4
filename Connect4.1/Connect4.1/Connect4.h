#define _CRT_SECURE_NO_WARNINGS  //Added this to get the time stamp in the txt file, since VS did not like me using the ctime function
#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h> //to be able to use srand, rand
#include <time.h>   //to be able to use time
#include <fstream>  //to be able to use ofstream
#include <chrono>   //to be able to use timestamps in the txt file
#include <ctime>    //to be able to use timestamps in the txt file
#pragma once

using namespace std;

void board();
void numberOfPlayers();
void gameplay2players();
void gameplayAI(); 

char table[6][8] = { {'*', '*', '*', '*', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*', '*', '*', '*'}, {'*', '*', '*', '*', '*', '*', '*', '*'} };

class Players
{
public:
	string name;
	char mark;
	unsigned int turns = 0;
	unsigned int wins = 0;
};
Players p1, p2;


int oneOrTwoPlayers{};
int AIor2Players{};
void checkBellow(char table[][8], Players activePlayer, int dropChoice);
int aiDrop(char table[][8]);
int playerDrop(char table[][8], Players activePlayer);
int calculateWinner(char table[][8], Players activePlayer);
//int win{};
int restart(char table[][8]);
int randomAI;
int blockPlayer{};
int AIplayz{};

void print(Players p1, Players p2);
ofstream Statistics("./Statistics.txt", ios::app); 
streampos begin, end;