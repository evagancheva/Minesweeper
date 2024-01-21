/**
*
* Solution to course project # 5
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Eva Gancheva
* @idnumber 6MI0600300
* @compiler VC
*
* 
*
*/


#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
constexpr unsigned SIZE = 10;

bool isValidSize(size_t size)
{
	return size >= 3 && size <= 10;
}
bool isValidInputForMines(unsigned numOfMines, size_t size)
{
	return numOfMines >= 1 && numOfMines <= 3 * size;
}
void createValidGame(size_t& size, int& numOfMines)
{
	cout << "Enter size of game(from 3 to 10): ";
	cin >> size;
	while (!isValidSize(size))
	{
		cout << endl << "Incorrect input. Please enter correct size: ";
		cin >> size;
	}
	cout << endl << "Enter number of mines from 1 to " << size * 3 <<" : ";
	cin >> numOfMines;
	while (!isValidInputForMines(numOfMines, size))
	{
			cout << endl << "Incorrect input. Please enter correct count of mines: ";
			cin >> numOfMines;
	}
	cout << endl;

}
void init(char field [][SIZE], char symbol)
{
	for (int i = 0; i < SIZE; i++)
	{
		for(int j=0; j<SIZE;j++)
			field[i][j] = symbol;
	}
}
void printNumbersOfColls(size_t size)
{
	cout << " ";
	for (int i = 0; i < size; i++)
	{
		cout << "  "<< i ;
	}
	cout << endl;
}
void printField(const char field[][SIZE], size_t size, int mines)
{
	printNumbersOfColls(size);
	for (int i = 0; i < size; i++)
	{
		cout << i<< " ";
		for (int j = 0; j < size; j++)
		{
			cout << "[" << field[i][j] << "]";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Remaning mines to mark: " << mines << endl;
}
bool isMarked(char symbol)
{
	return symbol == '*';
}
void generateValidCordinatesForMine(char field[][SIZE], int& row, int& coll, size_t size)
{
		row = rand() % size;
		coll = rand() % size;
		if(isMarked(field[row][coll]))
		{
			generateValidCordinatesForMine(field, row, coll, size);
		}
		field[row][coll] = '*';
}
void placeMines(char field[][SIZE], size_t size, int mines)
{
	srand(time(0));
	for (int i = 1; i <= mines; i++) 
	{
		int randomRowNum = 0, randomCollNum = 0;
		generateValidCordinatesForMine(field,randomRowNum, randomCollNum, size);
	}

}
int getCountInCell(char field[][SIZE], size_t size, int x, int y)
{
	char count = '0';
	if (x >= 0 && y >= 0 && x < size && y < size)
	{ 
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (i >= 0  && i < size )
		{ 
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i >= 0 && j >= 0 && i < size && j < size)
			{
				if (i == x && j == y)
					continue;
				if (field[i][j] == '*')
					count++;
			}
		}
		}
	}
	}
	return count;
}
void findCountOfMinesAround(char field[][SIZE], size_t size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (field[i][j] != '*')
				field[i][j]=getCountInCell(field, size, i, j);
		}
	}
}
int myStrcmp(const char* first, const char* second)
{
	if (!first  ||! second )
		return -1;
	while ((*first) && (*second) && ((*first) == (*second)))
	{
		first++;
		second++;
	}
	if (*first == '\0' && *second == '\0')
		return 0;
	return *first == '\0' ? -1 : 1;
}
bool isValidCommand(const char* currentCommand)
{
	return (myStrcmp(currentCommand, "open") == 0 ||
		myStrcmp(currentCommand, "mark") == 0 ||
		myStrcmp(currentCommand, "unmark") == 0);
	
	
}
bool isValidCoordinate(int number, size_t size)
{
	return number >= 0 && number <= (size - 1);
}
void getValidCordinates(int& rowCoordinate, int& collCordinate, size_t size)
{
	cout << "Please enter coordinates of cell: " << endl;
	cin >> rowCoordinate >> collCordinate;
	while (!isValidCoordinate(rowCoordinate, size)|| !isValidCoordinate(rowCoordinate, size))
	{
			cout << "Please, enter valid cordinates from 0 to " << (size - 1) << endl;
			cin >> rowCoordinate >> collCordinate;
	}
}
void openAllZeroes(char gameField[][SIZE], char minesField[][SIZE], 
					int currentRow, int currentColl, size_t size, int& counOfFreeCells)
{
	for (int i = currentRow - 1; i <= currentRow + 1; i++)
	{
		if (i >= 0 && i < size)
		{
			for (int j = currentColl - 1; j <= currentColl + 1; j++) 
			{
				if (j >= 0 && j < size)
				{
					if (i == currentRow && j == currentColl)
						continue;
					if (gameField[i][j] == ' ' && minesField[i][j] != '*') {
						gameField[i][j] = minesField[i][j];
						counOfFreeCells--;
						if (gameField[i][j] == '0') {
							openAllZeroes(gameField, minesField, i, j, size, counOfFreeCells);



						}
					}
				}
			}
		}
	}
}
void playMark(char gameField[][SIZE], char minesField[][SIZE], 
				 int currentRow, int currentColl,  int& mines)
{
	if (gameField[currentRow][currentColl] == '#') 
	{
		cout << "This cell is already marked!" << endl;
	}
	else  if(gameField[currentRow][currentColl] == ' ')
	{
		gameField[currentRow][currentColl] = '#';
		mines--;
	}
	else
	{
		cout << "This cell is opened! " << endl;
	}
}
void playUnmark(char gameField[][SIZE], char minesField[][SIZE], 
					 int currentRow, int currentColl)
{
	if (gameField[currentRow][currentColl] == '#') 
	{
		gameField[currentRow][currentColl] = ' ';
		cout << "This cell is not marked!" << endl;
	}
	else if(gameField[currentRow][currentColl] != '#')
	{
		cout << "This cell is not marked!" << endl;
	}
}
void playOpen(char gameField[][SIZE], char minesField[][SIZE], 
			  size_t size, int currentRow, int currentColl, bool& game, int& counOfFreeCells, int mines)
{
	if (minesField[currentRow][currentColl] == '*') {
		printField(minesField, size,mines);
		cout << "Game Over! You hit a mine."<<endl;
		game = false;
		
	}
	else if (gameField[currentRow][currentColl] == '#')
	{
		cout << "This cell is already marked. " << endl;
	}
	else if (gameField[currentRow][currentColl] != ' ')
	{
		cout << "Cell has already been opened! " << endl;
	}
	else if(minesField[currentRow][currentColl]!='0')
	{
		gameField[currentRow][currentColl] = minesField[currentRow][currentColl];
		counOfFreeCells--;
	}
	else if(minesField[currentRow][currentColl] == '0')
	{
		openAllZeroes(gameField, minesField, currentRow, currentColl, size, counOfFreeCells);
	}
}
void playCommand(const char* currentCommand, char gameField[][SIZE],
				 char minesField[][SIZE], size_t size, int& mines,
				 int currentRow, int currentColl, bool& game, int& counOfFreeCells)
{
	if (myStrcmp(currentCommand, "open") == 0)
	{
		playOpen(gameField, minesField, size,currentRow, currentColl, game,  counOfFreeCells, mines);
	}
	else if (myStrcmp(currentCommand, "mark") == 0)
	{
		playMark(gameField, minesField, currentRow, currentColl,  mines);
	}
	else if (myStrcmp(currentCommand, "unmark") == 0)
	{
		playUnmark(gameField, minesField,  currentRow, currentColl);
	}
}
bool isGameWon(int counOfFreeCells, int mines)
{
	return counOfFreeCells == 0&& mines==0;
}
void play(char gameField[][SIZE], char minesField[][SIZE], size_t size, int& mines)
{
	int counOfFreeCells = size * size - mines;
	bool game = 1;
	do
	{
		
		char currentCommand[7];
		cout << "Plese choose open, mark or unmark:" << endl;
		cin >> currentCommand;
		if (isValidCommand(currentCommand))
		{
			int currentRow, currentColl;
			getValidCordinates(currentRow, currentColl, size);
			playCommand(currentCommand, gameField, minesField, size, mines,currentRow,currentColl,game, counOfFreeCells);
			if (game == 0)
			{
				break;
			}
			if (isGameWon(counOfFreeCells,mines) == true)
			{
				printField(minesField, size, mines);
				cout << "Congratulation!You won!";
				break;
			}
			printField(gameField, size, mines);
		}
		else
		{
			cout << "Incorrect input! Try again." << endl;
		}
	} while (game);
	
	
}
int main()
{
	size_t size;
	int mines;
	createValidGame(size, mines);
	char gameField[SIZE][SIZE];
	char fieldWithMines[SIZE][SIZE];
	init(gameField, ' ');
	init(fieldWithMines, '0');
	placeMines(fieldWithMines, size, mines);
	findCountOfMinesAround(fieldWithMines, size);
	printField(gameField, size, mines);
	play(gameField, fieldWithMines,size, mines);
	return 0;
	

}

