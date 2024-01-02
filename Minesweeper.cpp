

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
void generateMines(char field[SIZE][SIZE], size_t size, unsigned mines)
{
	srand(time(0));
	for (int i = 1; i <= mines; i++) 
	{
		int randomRowNum = 0, randomCollNum = 0;
		generateValidCordinatesForMine(field,randomRowNum, randomCollNum, size);
	}

}
void getCountInCell(char field[SIZE][SIZE], size_t size, int x, int y)
{
	char count = '0';
	for (int i = x - 1; i <= x + 1; i++)
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
	field[x][y] = count;
}
void findCountOfMinesAround(char field[SIZE][SIZE], size_t size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (field[i][j] != '*')
				getCountInCell(field, size, i, j);
		}
	}
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
	generateMines(fieldWithMines, size, mines);
	findCountOfMinesAround(fieldWithMines, size);
	printField(fieldWithMines, size);
	printField(gameField, size);

}

