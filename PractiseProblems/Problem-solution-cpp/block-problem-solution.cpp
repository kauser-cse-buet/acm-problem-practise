/*
#include<iostream>
#include<sstream>

using namespace std;


#define MAX_BLOCK_NUMBER 25
#define END_OF_ARRAY 100

int blockArray[MAX_BLOCK_NUMBER + 1][MAX_BLOCK_NUMBER + 1];
int n;
int blockPosition[MAX_BLOCK_NUMBER][2];

void MoveBlockToInitialPosition(int blockNo);

void MoveBlockToPosition(int blockNo, int position)
{
	if (blockNo > 0 && blockNo < MAX_BLOCK_NUMBER)
	{
		int currentPositionX = blockPosition[blockNo][0];
		int currentPositionY = blockPosition[blockNo][1];
		if (blockArray[currentPositionX][currentPositionY] == blockNo)
		{
			if (blockArray[currentPositionX][currentPositionY + 1] == END_OF_ARRAY)
			{
				blockArray[currentPositionX][currentPositionY] = END_OF_ARRAY;
				int j = 0;
				while (blockArray[position][j++] == END_OF_ARRAY);
				blockArray[position][j] = blockNo;
				blockPosition[blockNo][0] = position;
				blockPosition[blockNo][1] = j;
				blockArray[position][j + 1] = END_OF_ARRAY;
			}
			else
			{
				MoveBlockToInitialPosition(blockArray[currentPositionX][currentPositionY + 1]);
			}

		}
	}
}

void MoveBlockToPositionO(int blockNo, int positionX)
{
	int y = 0;
	while(blockArray[blockNo][y] != END_OF_ARRAY)
		y++;
	blockArray[blockNo][y] = blockNo;
	blockArray[blockNo][y + 1] = END_OF_ARRAY;
	blockPosition[blockNo][0] = blockNo;
	blockPosition[blockNo][1] = y;
}

void MoveBlockToInitialPosition(int blockNo)
{
	int y = 0;
	while(blockArray[blockNo][y] != END_OF_ARRAY)
		y++;
	blockArray[blockNo][y] = blockNo;
	blockArray[blockNo][y + 1] = END_OF_ARRAY;
	blockPosition[blockNo][0] = blockNo;
	blockPosition[blockNo][1] = y;
}

void TransferPileOverToOriginalPosition(int blockNumber)
{
	int fromPositionX = blockPosition[blockNumber][0];
	int fromPositionY = blockPosition[blockNumber][1];

	int currentPositionY = fromPositionY + 1;
	while(blockArray[fromPositionX][currentPositionY] != END_OF_ARRAY)
	{
		MoveBlockToInitialPosition(blockArray[fromPositionX][currentPositionY]);
		blockArray[fromPositionX][currentPositionY] = END_OF_ARRAY;
		currentPositionY++;
	}
}

void TransferPileOverToPosition(int fromBlockNumber, int toBlockNumber)
{
	int fromPositionX = blockPosition[fromBlockNumber][0];
	int fromPositionY = blockPosition[fromBlockNumber][1];

	int toPositionX = blockPosition[toBlockNumber][0];
	int toPositionY = blockPosition[toBlockNumber][1];

	while (blockArray[toPositionX][toPositionY] != END_OF_ARRAY)
	{
		toPositionY++;
	}

	int currentPositionY = fromPositionY;
	while (blockArray[fromPositionX][currentPositionY] != END_OF_ARRAY)
	{
		int block = blockArray[fromPositionX][currentPositionY];
		blockArray[toPositionX][toPositionY] = block;
		blockPosition[block][0] = toPositionX;
		blockPosition[block][1] = toPositionY;
		blockArray[fromPositionX][currentPositionY] = END_OF_ARRAY;
		currentPositionY++;
		toPositionY++;
	}
	blockArray[toPositionX][toPositionY] = END_OF_ARRAY;
}

void MoveOnto(int fromBlockNumber, int toBlockNumber)
{
	int fromPositionX = blockPosition[fromBlockNumber][0];
	int fromPositionY = blockPosition[fromBlockNumber][1];

	int toPositionX = blockPosition[toBlockNumber][0];
	int toPositionY = blockPosition[toBlockNumber][1];

	TransferPileOverToOriginalPosition(fromBlockNumber);
	TransferPileOverToOriginalPosition(toBlockNumber);

	blockArray[toPositionX][toPositionY + 1] = blockArray[fromPositionX][fromPositionY];
	blockArray[fromPositionX][fromPositionY] = END_OF_ARRAY;
	blockArray[toPositionX][toPositionY + 1 + 1] = END_OF_ARRAY;

	// update from block position.
	blockPosition[fromBlockNumber][0] = toPositionX;
	blockPosition[fromBlockNumber][1] = toPositionY + 1;
}

void MoveOver(int fromBlockNumber, int toBlockNumber)
{
	int fromPositionX = blockPosition[fromBlockNumber][0];
	int fromPositionY = blockPosition[fromBlockNumber][1];

	int toPositionX = blockPosition[toBlockNumber][0];
	int toPositionY = blockPosition[toBlockNumber][1];

	TransferPileOverToOriginalPosition(fromBlockNumber);

	int count = 0;
	while (blockArray[toPositionX][count] != END_OF_ARRAY)
	{
		count++;
	}
	blockArray[toPositionX][count] = blockArray[fromPositionX][fromPositionY];
	blockArray[fromPositionX][fromPositionY] = END_OF_ARRAY;
	blockArray[toPositionX][count + 1] = END_OF_ARRAY;

	// update from block position.
	blockPosition[fromBlockNumber][0] = toPositionX;
	blockPosition[fromBlockNumber][1] = count;
}

void PileOnto(int fromBlockNumber, int toBlockNumber)
{
	TransferPileOverToOriginalPosition(toBlockNumber);
	TransferPileOverToPosition(fromBlockNumber, toBlockNumber);
}

void PileOver(int fromBlockNumber, int toBlockNumber)
{
	TransferPileOverToPosition(fromBlockNumber, toBlockNumber);
}

void GenerateBlockArray()
{
	for (int i = 0; i < n; i++)
	{
		blockArray[i][0] = i;
		blockArray[i][1] = END_OF_ARRAY;
		blockPosition[i][0] = i;
		blockPosition[i][1] = 0;
	}
}

void ShowBlockArray()
{
	for (int i = 0; i < n; i++)
	{
		cout << i << ":";
		for (int j = 0; j < MAX_BLOCK_NUMBER; j++)
		{
			if (blockArray[i][j] == END_OF_ARRAY)
			{
				break;
			}
			else
			{
				cout << " " << blockArray[i][j];
			}
		}
		cout << endl;
	}
}

bool IsOnSameStack(int fromBlockNumber, int toBlockNumber)
{
	int fromPositionX = blockPosition[fromBlockNumber][0];
	int toPositionX = blockPosition[toBlockNumber][0];

	if (fromPositionX == toPositionX)
		return true;
	else
		return false;
	
}

void input()
{
	string command[25];
	string numCommandStr  = "";
	getline(cin, numCommandStr);
	n = stoi(numCommandStr);
	if (n > 0 && n < MAX_BLOCK_NUMBER)
	{
		GenerateBlockArray();
		string command;
		string majorCommand, minorCommand;
		int fromBlockNumber, toBlockNumber;

		while (1)
		{
			getline(cin, command);
			if (command == "quit")
			{
				break;
			}
			else
			{
				stringstream(command) >> majorCommand >> fromBlockNumber >> minorCommand >> toBlockNumber;
				if (fromBlockNumber < n && toBlockNumber < n && fromBlockNumber >= 0 && toBlockNumber >= 0 && fromBlockNumber != toBlockNumber && !IsOnSameStack(fromBlockNumber, toBlockNumber))
				{
					if (majorCommand == "move")
					{
						if (minorCommand == "over")
						{
							MoveOver(fromBlockNumber, toBlockNumber);
						}

						if (minorCommand == "onto")
						{
							MoveOnto(fromBlockNumber, toBlockNumber);
						}
					}

					if (majorCommand == "pile")
					{
						if (minorCommand == "over")
						{
							PileOver(fromBlockNumber, toBlockNumber);
						}

						if (minorCommand == "onto")
						{
							PileOnto(fromBlockNumber, toBlockNumber);
						}
					}
				}
			}
		}
	}
}

void output()
{
	ShowBlockArray();
}

int main()
{
	input();
	output();
	return 0;
}

*/