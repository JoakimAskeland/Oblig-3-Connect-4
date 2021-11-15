#include "Connect4.h"

int main()
{
	numberOfPlayers();

	auto start = chrono::system_clock::now();

	if (AIor2Players == 1)
	{
		gameplayAI();
	}

	if (AIor2Players == 2)
	{
		gameplay2players();
	}

	auto finish = chrono::system_clock::now();

	cout << "Writing statistics...";
	streampos begin, end;
	ofstream Statistics("./Statistics.txt", ios::app);

	time_t finish_time = chrono::system_clock::to_time_t(finish);
	chrono::duration<double> elapsed_minutes = finish - start;
	elapsed_minutes = elapsed_minutes / 60;

	Statistics << ctime(&finish_time) << "Game duration: " << elapsed_minutes.count() << " minutes" << endl << endl;
	Statistics << p1.name << " won " << p1.wins << " times" << endl;
	Statistics << p2.name << " won " << p2.wins << " times" << endl;
	Statistics << endl << endl << endl;

	Statistics.close();
	
	return 0;
}

void numberOfPlayers()
{
	cout << "You vs AI (1) or 1 vs 1 (2)?" << endl;

	do
	{
		cin >> oneOrTwoPlayers;
		cout << endl << endl;

		switch (oneOrTwoPlayers)
		{
		case 1:
			cout << "What is your name?" << endl;
			cin >> p1.name;
			cout << endl << endl;
			p2.name = "AI";
			AIor2Players = 1;
			break;

		case 2:
			cout << "Player 1, what is your name?" << endl;
			cin >> p1.name;
			cout << endl << endl;
			if (p1.name == "AI" || p1.name == "ai")
			{
				p2.name = "AI";
				cout << "AI goes second, what is your name?" << endl;
				cin >> p1.name;
				cout << endl << endl;
				AIor2Players = 1;
				break;
			}

			cout << "Player 2, what is your name?" << endl;
			cin >> p2.name;
			if (p2.name == "AI" || p2.name == "ai")
			{
				p2.name = "AI";
				AIor2Players = 1;
				break;
			}
			cout << endl << endl;
			AIor2Players = 2;
			break;

		default:
			cout << "Please enter 1 or 2: ";
		}

	} while (AIor2Players != 1 && AIor2Players != 2);
}

void gameplay2players()
{
	int dropChoice;
	p1.mark = 'X';
	p2.mark = 'O';
	int win = 0;
	int playAgain = 0;

	board();

	do
	{
		dropChoice = playerDrop(table, p1);
		checkBellow(table, p1, dropChoice);
		board();
		p1.turns = p1.turns + 1;
		win = calculateWinner(table, p1);
		if (win == 1)
		{
			cout << "You win " << p1.name << "!!" << endl;
			cout << "You won in " << p1.turns << " turns" << endl << endl;
			p1.wins = p1.wins + 1;
			playAgain = restart(table);
			if (playAgain == 2)
			{
				break;
			}

		}

		system("cls");
		board();

		dropChoice = playerDrop(table, p2);
		checkBellow(table, p2, dropChoice);
		system("cls");
		board();
		p2.turns = p2.turns + 1;
		win = calculateWinner(table, p2);
		if (win == 1)
		{
			cout << "You win " << p2.name << "!!" << endl;
			cout << "You won in " << p2.turns << " turns" << endl << endl;
			p2.wins = p2.wins + 1;
			playAgain = restart(table);
			if (playAgain == 2)
			{
				break;
			}
		}

		if (win == 2)
		{
			cout << "It is a tie" << endl;
			playAgain = restart(table);
			if (playAgain == 2)
			{
				break;
			}
		}

	} while (playAgain != 2);
}

void gameplayAI()
{
	//Well, there are 4 531 985 219 092 different board configurations in Connect 4, so calculating a perfect AI by doing if statements for every single outcome would have me crying for days on end

	int dropChoice;
	p1.mark = 'X';
	p2.mark = 'O';
	p1.turns = 0;   
	p2.turns = 0;
	int win = 0;
	int playAgain = 0;

	board();
	do
	{
		dropChoice = playerDrop(table, p1);
		checkBellow(table, p1, dropChoice);
		system("cls");
		board();
		p1.turns = p1.turns + 1;
		win = calculateWinner(table, p1);
		if (win == 1)
		{
			cout << "You win " << p1.name << "!!" << endl;
			cout << "You won in " << p1.turns << " turns!" << endl << endl;
			p1.wins = p1.wins + 1;
			playAgain = restart(table);
			if (playAgain == 2)
			{
				break;
			}

		}
		
		dropChoice = aiDrop(table);
		checkBellow(table, p2, dropChoice);
		system("cls");
		board();
		p2.turns = p2.turns + 1;
		win = calculateWinner(table, p2);
		if (win == 1)
		{
			cout << "You lost in " << p1. turns << " turns, " << p2.name << " wins!!" << endl << endl;
			p2.wins = p2.wins + 1;
			playAgain = restart(table);
			if (playAgain == 2)
			{
				break;
			}
		}

		if (win == 2)
		{
			cout << "It is a tie" << endl;
			playAgain = restart(table);
			if (playAgain == 2)
			{
				break;
			}
		}

	} while (playAgain != 2);
}

int aiDrop(char table[][8])
{
	int dropChoice;
	int blockPlayer = 0;
	int AIplayz = 0;


	if (blockPlayer != 1)
	{
		for (int row = 5; row >= 0; row--)
		{
			for (int column = 7; column >= 0; column--)
			{
				if (table[row][column] == 'O' && table[row - 1][column - 1] == 'O' && table[row - 2][column - 2] == 'O')
				{
					if (table[row - 3][column - 3] == '*' && table[row - 2][column - 3] != '*')
					{
						dropChoice = column - 3;
						AIplayz = 1;
						break;
					}

					if (table[row - 3][column - 3] != '*' && table[row + 1][column + 1] == '*' && table[row + 2][column + 1] != '*')
					{
						dropChoice = column + 1;
						AIplayz = 1;
						break;
					}
				}

				if (table[row][column] == 'O' && table[row - 1][column] == 'O' && table[row - 2][column] == 'O')
				{
					if (table[row - 3][column] == '*')
					{
						dropChoice = column;
						AIplayz = 1;
						break;
					}
				}

				if (table[row][column] == 'O' && table[row - 1][column + 1] == 'O' && table[row - 2][column + 2] == 'O')
				{
					if (table[row - 3][column + 3] == '*' && table[row - 2][column + 3] != '*')
					{
						dropChoice = column + 3;
						AIplayz = 1;
						break;
					}

					if (table[row - 3][column + 3] != '*' && table[row + 1][column - 1] == '*' && table[row + 2][column - 1] != '*')
					{
						dropChoice = column - 1;
						AIplayz = 1;
						break;
					}
				}

				if (table[row][column] == 'O' && table[row][column - 1] == 'O' && table[row][column - 2] == 'O')
				{
					if (table[row][column - 3] == '*')
					{
						dropChoice = column - 3;
						AIplayz = 1;
						break;
					}

					if (table[row][column - 3] != '*' && table[row][column + 1] == '*' && table[row + 1][column + 1])
					{
						dropChoice = column + 1;
						AIplayz = 1;
						break;
					}
				}

				if (table[row][column] == 'O' && table[row][column + 1] == 'O' && table[row][column + 2] == 'O')
				{
					if (table[row][column + 3] == '*')
					{
						dropChoice = column + 3;
						AIplayz = 1;
						break;
					}

					if (table[row][column + 3] != '*' && table[row][column - 1] == '*' && table[row + 1][column - 1] != '*')
					{
						dropChoice = column - 1;
						AIplayz = 1;
						break;
					}
				} //Up until this point it checks if AI has got 3 in a row, if it does it tries to make it 4 in a row.
			}
		}
	}

	//Checks to see if it can block the player
	for (int row = 5; row >= 0; row--)  
	{
		for (int column = 7; column >= 0; column--)   
		{
			if (table[row][column] == 'X' && table[row - 1][column - 1] == 'X' && table[row - 2][column - 2] == 'X')
			{
				if (table[row - 3][column - 3] == '*' && table[row - 2][column - 3] != '*')
				{
					dropChoice = column - 3;
					blockPlayer = 1;
					break; 
				}

				if (table[row + 1][column + 1] == '*' && table[row + 2][column + 1] != '*')
				{
					dropChoice = column + 1;
					blockPlayer = 1;
					break;
				}

				if (table[row - 3][column - 3] == '*' && table[row - 2][column - 3] == '*')
				{
					break;
				}
			}

			if (table[row][column] == 'X' && table[row - 1][column] == 'X' && table[row - 2][column] == 'X') 
			{
				if (table[row - 3][column] == '*')
				{
					dropChoice = column;
					blockPlayer = 1;
					break; 
				}
			}

			if (table[row][column] == 'X' && table[row - 1][column + 1] == 'X' && table[row - 2][column + 2] == 'X')
			{
				if (table[row - 3][column + 3] == '*' && table[row - 2][column + 3] != '*')
				{
					dropChoice = column + 3;
					blockPlayer = 1;
					break;
				}

				if (table[row - 3][column + 3] != '*' && table[row + 1][column - 1] == '*')
				{
					dropChoice = column - 1;
					blockPlayer = 1;
					break;
				}

				if (table[row - 3][column + 3] == '*' && table[row - 2][column + 3] == '*')
				{
					break;
				}
			}

			if (table[row][column] == 'X' && table[row][column - 1] == 'X' && table[row][column - 2] == 'X')
			{
				if (table[row][column - 3] == '*' && table[row + 1][column - 3] != '*')
				{
					dropChoice = column - 3;
					blockPlayer = 1;
					break;
				}

				if (table[row][column - 3] != '*' && table[row][column + 1] == '*' && table[row + 1][column + 1] != '*')
				{
					dropChoice = column + 1;
					blockPlayer = 1;
					break;
				}

				if (table[row + 1][column + 1] == '*' && table[row + 1][column - 3] == '*')
				{
					break;
				}
			}

			if (table[row][column] == 'X' && table[row][column + 1] == 'X' && table[row][column + 2] == 'X')
			{
				if (table[row][column + 3] == '*')
				{
					dropChoice = column + 3;
					blockPlayer = 1;
					break;
				}

				if (table[row][column + 3] != '*' && table[row][column - 1] == '*' && table[row + 1][column - 1] != '*')
				{
					dropChoice = column - 1;
					blockPlayer = 1;
					break;
				}

				if (table[row + 1][column + 3] == '*' && table[row + 1][column - 1] == '*')
				{
					break;
				}
			} //Up until this point AI checks if the player has got 3 in a row. If they do, the AI will try to block it

			//If the AI can not find any 3 in a row to block, then it moves on to 2 in a row
			if (table[row][column] == 'X' && table[row - 1][column - 1] == 'X')
			{
				if (table[row - 2][column - 2] == '*' && table[row - 1][column - 2] != '*')
				{
					dropChoice = column - 2;
					blockPlayer = 1;
					break;
				}

				if (table[row + 1][column + 1] == '*' && table[row + 2][column + 1] != '*')
				{
					dropChoice = column + 1;
					blockPlayer = 1;
					break;
				}
			}

			if (table[row][column] == 'X' && table[row - 1][column] == 'X')
			{
				if (table[row - 2][column] == '*')
				{
					dropChoice = column;
					blockPlayer = 1;
					break;
				}
			}

			if (table[row][column] == 'X' && table[row - 1][column + 1] == 'X') 
			{
				if (table[row - 2][column + 2] == '*' && table[row - 1][column + 2] != '*') 
				{
					dropChoice = column + 2;
					blockPlayer = 1;
					break;
				}

				if (table[row - 2][column + 2] != '*' && table[row + 1][column - 1] == '*')
				{
					dropChoice = column - 1;
					blockPlayer = 1;
					break;
				}
			}

			if (table[row][column] == 'X' && table[row][column - 1] == 'X') 
			{
				if (table[row][column - 2] == '*')
				{
					dropChoice = column - 2;
					blockPlayer = 1;
					break;
				}

				if (table[row][column - 2] != '*' && table[row][column + 1] == '*')
				{
					dropChoice = column + 1;
					blockPlayer = 1;
					break;
				}
			}

			if (table[row][column] == 'X' && table[row][column + 1] == 'X') 
			{
				if (table[row][column + 2] == '*')
				{
					dropChoice = column + 2;
					blockPlayer = 1;
					break;
				}

				if (table[row][column + 2] != '*' && table[row][column - 1] == '*')
				{
					dropChoice = column - 1;
					blockPlayer = 1;
					break;
				}
			} 
		}
	}

	if (blockPlayer != 1 && AIplayz != 1)
	{
		srand(time(0));

		dropChoice = rand() % 7 + 1;

		if (table[0][dropChoice] != '*')
		{
			dropChoice = rand() % 7 + 1;
		}
	}

	return dropChoice;
}

int playerDrop(char table[][8], Players activePlayer)
{
	int dropChoice;

	do
	{
		cout << activePlayer.name << "'s turn" << endl;
		cout << "Enter a number between 1 and 7: ";
		cin >> dropChoice;

		while (table[0][dropChoice] == 'X' || table[0][dropChoice] == 'O')
		{
			cout << "That row is full, please choose another row: ";
			cin >> dropChoice;
		}

	} while (dropChoice < 1 || dropChoice > 7);

	return dropChoice;
}

void checkBellow(char table[][8], Players activePlayer, int dropChoice) 
{
	int turn = 0;

	for (int length = 5; length >= 0; length--)
	{
		if (table[length][dropChoice] != 'X' && table[length][dropChoice] != 'O')
		{
			table[length][dropChoice] = activePlayer.mark;
			turn = 1;
			break; //Or else the whole column [dropChoice] gets marked
		}
	}while (turn != 1);
}


int calculateWinner(char table[][8], Players activePlayer)
{
	char XO;
	int win;
	p1.mark = 'X';
	p2.mark = 'O';

	XO = activePlayer.mark;
	win = 0;

	for (int row = 6; row >= 0; row--)
	{
		for (int column = 7; column >= 0; column--)
		{
			if (table[row][column] == XO && table[row - 1][column - 1] == XO && table[row - 2][column - 2] == XO && table[row - 3][column - 3] == XO)
			{
				win = 1;
			}

			if (table[row][column] == XO && table[row - 1][column] == XO && table[row - 2][column] == XO && table[row - 3][column] == XO)
			{
				win = 1;
			}

			if (table[row][column] == XO && table[row - 1][column + 1] == XO && table[row - 2][column + 2] == XO && table[row - 3][column + 3] == XO)
			{
				win = 1;
			}

			if (table[row][column] == XO && table[row][column - 1] == XO && table[row][column - 2] == XO && table[row][column - 3] == XO)
			{
				win = 1;
			}

			if (table[row][column] == XO && table[row][column + 1] == XO && table[row][column + 2] == XO && table[row][column + 3] == XO)
			{
				win = 1;
			}
		}
	}

	if (table[0][1] != '*' && table[0][2] != '*' && table[0][3] != '*' && table[0][4] != '*' && table[0][5] != '*' && table[0][6] != '*' && table[0][7] != '*')
	{
		win = 2; //Tie
	}

	return win;
}

int restart(char table[][8])
{
	char playAgain;

	cout << "Would you like to play again?" << endl;
	cout << "Y/N: ";
	cin >> playAgain;

	if (playAgain == 'y' || playAgain == 'Y')
	{
		for (int row = 0; row <= 6; row++)
		{
			for (int column = 1; column <= 8; column++)
			{
				table[row][column] = '*';
			}
		}
		system("cls");
		board();
	}

	else
		playAgain = 2;

	return playAgain;
}

void print(Players p1, Players p2) 
{
	cout << "Writing statistics...";
	streampos begin, end;
	ofstream Statistics("./Statistics.txt", ios::app);

	auto finish = chrono::system_clock::now();

	time_t finish_time = chrono::system_clock::to_time_t(finish); 

	Statistics << ctime(&finish_time) << endl << endl;
	Statistics << p1.name << " won " << p1.wins << " times" << endl;
	Statistics << p2.name << " won " << p2.wins << " times" << endl;
	Statistics << endl << endl << endl;

	Statistics.close();
}


void board()
{
	cout << "  1  2  3  4  5  6  7  " << endl;
	cout << "| " << table[0][1] << "  " << table[0][2] << "  " << table[0][3] << "  " << table[0][4] << "  " << table[0][5] << "  " << table[0][6] << "  " << table[0][7] << " |" << endl;
	cout << "| " << table[1][1] << "  " << table[1][2] << "  " << table[1][3] << "  " << table[1][4] << "  " << table[1][5] << "  " << table[1][6] << "  " << table[1][7] << " |" << endl;
	cout << "| " << table[2][1] << "  " << table[2][2] << "  " << table[2][3] << "  " << table[2][4] << "  " << table[2][5] << "  " << table[2][6] << "  " << table[2][7] << " |" << endl;
	cout << "| " << table[3][1] << "  " << table[3][2] << "  " << table[3][3] << "  " << table[3][4] << "  " << table[3][5] << "  " << table[3][6] << "  " << table[3][7] << " |" << endl;
	cout << "| " << table[4][1] << "  " << table[4][2] << "  " << table[4][3] << "  " << table[4][4] << "  " << table[4][5] << "  " << table[4][6] << "  " << table[4][7] << " |" << endl;
	cout << "| " << table[5][1] << "  " << table[5][2] << "  " << table[5][3] << "  " << table[5][4] << "  " << table[5][5] << "  " << table[5][6] << "  " << table[5][7] << " |" << endl;
}