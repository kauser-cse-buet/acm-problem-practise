#include<iostream>
#include<sstream>
#include<list>

using namespace std;

#define NUMBER_OF_BIN 3
#define NUMBER_OF_COLOR 3
#define BROWN 0
#define GREEN 1
#define CLEAR 2
#define BIN_NO_1 0
#define BIN_NO_2 1
#define BIN_NO_3 2
#define COLOR_IS_NOT_SET NUMBER_OF_COLOR

int binArray[NUMBER_OF_BIN][NUMBER_OF_COLOR];
int binColorArray[NUMBER_OF_BIN];
int numberOfMoveForColorArray[NUMBER_OF_COLOR];

void SelectBinForMaxBottle()
{
	list<int>::iterator listIterator;
	int maxBottleNumber = 0;
	int colorForMaxBottle = -1;
	int binNoForMaxBottle = -1;

	for (int binNo = 0; binNo < NUMBER_OF_BIN; binNo++)
	{
		for (int color = 0; color < NUMBER_OF_COLOR; color++)
		{
			if (binArray[binNo][color] > maxBottleNumber)
			{
				maxBottleNumber = binArray[binNo][color];
				colorForMaxBottle = color;
				binNoForMaxBottle = binNo;
			}
		}
	}

	binColorArray[binNoForMaxBottle] = colorForMaxBottle;
	
	for (int i = 0; i < NUMBER_OF_COLOR; i++)
	{
		if (i != colorForMaxBottle)
		{
			numberOfMoveForColorArray[i] += binArray[binNoForMaxBottle][i];
			binArray[binNoForMaxBottle][i] = 0;
		}
	}
	binArray[binNoForMaxBottle][colorForMaxBottle] = 0;

	for (int i = 0; i < NUMBER_OF_BIN; i++)
	{
		numberOfMoveForColorArray[colorForMaxBottle] += binArray[i][colorForMaxBottle];
		binArray[i][colorForMaxBottle] = 0;
	}
}

void SetBinColorArray()
{	
	for (int i = 0; i < NUMBER_OF_COLOR; i++)
	{
		SelectBinForMaxBottle();
	}
}

void Init()
{
	for (int i = 0; i < NUMBER_OF_COLOR; i++)
	{
		numberOfMoveForColorArray[i] = 0;
	}
}

void output()
{
	int totalNumberOfSteps = 0;
	char colorName[3] = {'B', 'G', 'C'};

	for (int i = 0; i < NUMBER_OF_COLOR; i++)
	{
		totalNumberOfSteps += numberOfMoveForColorArray[i];
	}
	if (numberOfMoveForColorArray[0] < numberOfMoveForColorArray[1])
	{
		if (numberOfMoveForColorArray[0] < numberOfMoveForColorArray[2])
		{
			cout << colorName[0];
			if (numberOfMoveForColorArray[1] < numberOfMoveForColorArray[2])
			{
				cout << colorName[1] << colorName[2];
			}
			else
			{
				cout << colorName[2] << colorName[1];
			}
		}
		else
		{
			cout << colorName[2] << colorName[0] << colorName[1];
		}
	}
	else
	{
		if (numberOfMoveForColorArray[1] < numberOfMoveForColorArray[2])
		{
			cout << colorName[1];
			if (numberOfMoveForColorArray[2] < numberOfMoveForColorArray[0])
			{
				cout << colorName[2] << colorName[0];
			}
			else
			{
				cout << colorName[0] << colorName[2];
			}
		}
		else
		{
			cout << colorName[2] << colorName[1] << colorName[0];
		}
	}
	cout << " " << totalNumberOfSteps << endl;
}

void Run()
{
	while(cin >> binArray[BIN_NO_1][BROWN] >> binArray[BIN_NO_1][GREEN] >> binArray[BIN_NO_1][CLEAR]
		>> binArray[BIN_NO_2][BROWN] >> binArray[BIN_NO_2][GREEN] >> binArray[BIN_NO_2][CLEAR]
		>> binArray[BIN_NO_3][BROWN] >> binArray[BIN_NO_3][GREEN] >> binArray[BIN_NO_3][CLEAR])
	{
		Init();
		SetBinColorArray();
		output();
	}
}

int main()
{
	Run();
	return 0;
}
