

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
void createValidGame(size_t& size,unsigned int& numOfMines)
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
void init(char field [SIZE][SIZE], char symbol)
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
void printField(const char field[SIZE][SIZE], size_t size)
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
}
void generateCordinates(int& row, int& coll, size_t size)
{
	do
	{
		row = rand() % 10;
	} while (row >= size);
	do
	{
		coll = rand() % 10;
	} while (coll >= size);
	
}
bool isMarked(char symbol)
{
	return symbol == '*';
}
void generateValidCordinatesForMine(char field[SIZE][SIZE], int& row, int& coll, size_t size)
{
		while(isMarked(field[row][coll]))
		{
			generateCordinates(row, coll, size);
		}
		field[row][coll] = '*';
}
void placeMines(char field[SIZE][SIZE], size_t size, unsigned mines)
{
	srand(time(0));
	for (int i = 1; i <= mines; i++) 
	{
		int randomRowNum = 0, randomCollNum = 0;
		generateValidCordinatesForMine(field,randomRowNum, randomCollNum, size);
	}

}
int getCountInCell(char field[SIZE][SIZE], size_t size, int x, int y)
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
void findCountOfMinesAround(char field[SIZE][SIZE], size_t size)
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
bool isValidCommand(char* currentCommand)
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
void openAllZeroes(char gameField[SIZE][SIZE], char minesField[SIZE][SIZE], 
					int currentRow, int currentColl, size_t size, unsigned mines)
{

}
void playMark(char gameField[SIZE][SIZE], char minesField[SIZE][SIZE], 
				unsigned mines, int currentRow, int currentColl )
{
	if (gameField[currentRow][currentColl] == '#') 
	{
		cout << "This cell is already marked!" << endl;
	}
	else  if(gameField[currentRow][currentColl] == ' ')
	{
		gameField[currentRow][currentColl] = '#';
	}
	else
	{
		cout << "This cell is opened! " << endl;
	}
}
void playUnmark(char gameField[SIZE][SIZE], char minesField[SIZE][SIZE], 
					unsigned mines, int currentRow, int currentColl)
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
void playOpen(char gameField[SIZE][SIZE], char minesField[SIZE][SIZE], 
			  size_t size, unsigned mines, int currentRow, int currentColl, bool& game)
{
	if (minesField[currentRow][currentColl] == '*') {
		printField(minesField, size);
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
	}
	else if(minesField[currentRow][currentColl] == '0')
	{
		openAllZeroes(gameField, minesField, currentRow, currentColl, size, mines);
	}
}
void playCommand(char* currentCommand, char gameField[SIZE][SIZE],
				 char minesField[SIZE][SIZE], size_t size, unsigned mines,
				 int currentRow, int currentColl, bool& game)
{
	if (myStrcmp(currentCommand, "open") == 0)
	{
		playOpen(gameField, minesField, size, mines, currentRow, currentColl, game);
	}
	else if (myStrcmp(currentCommand, "mark") == 0)
	{
		playMark(gameField, minesField,  mines, currentRow, currentColl);
	}
	else if (myStrcmp(currentCommand, "unmark") == 0)
	{
		playUnmark(gameField, minesField,  mines, currentRow, currentColl);
	}
}

void play(char gameField[SIZE][SIZE], char minesField[SIZE][SIZE], size_t size, unsigned mines)
{
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
			playCommand(currentCommand, gameField, minesField, size, mines,currentRow,currentColl,game);
			if (game == 0)
			{
				break;
			}
			printField(gameField, size);
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
	unsigned mines;
	createValidGame(size, mines);
	char gameField[SIZE][SIZE];
	char fieldWithMines[SIZE][SIZE];
	init(gameField, ' ');
	init(fieldWithMines, ' ');
	placeMines(fieldWithMines, size, mines);
	findCountOfMinesAround(fieldWithMines, size);
	printField(fieldWithMines, size);
	printField(gameField, size);
	play(gameField, fieldWithMines,size, mines);
	return 0;
	

}

