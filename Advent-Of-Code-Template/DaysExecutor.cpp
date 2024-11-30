#include "DaysExecutor.h"
#include <fstream>

StartParams DaysExecutor::getParamsFromUser()
{
	StartParams params;
	char ans;
	int day;
	cout << "Which day would you like to do? [1-25] ";
	cin >> day;

	if (day < 1 || day > 26)
	{
		cout << "Wrong number!\n";
		throw -1;
	}

	cout << "Should the calculations use test values? [Y/N] ";
	cin >> ans;

	params.day = day;
	params.useTestValues = (ans == 'y' || ans == 'Y');

	return params;
}

DaysExecutor::DaysExecutor(StartParams params)
{
	this->day = params.day;
	this->doAll = params.doAllDays;
	this->useTestVal = params.useTestValues;
}

void DaysExecutor::execute()
{
	if (doAll)
	{
		for (int i = 1; i <= 25; i++)
		{
			doDay(i);
		}
	}
	else
	{
		doDay(day);
	}

}


stringstream DaysExecutor::readInput(int dayNumber)
{
	stringstream ss;
	string filePath = "Inputs/Day";
	filePath += to_string(dayNumber);
	if (this->useTestVal)
		filePath += "Test";
	filePath += ".txt";

	ifstream file(filePath);

	if (!file.good())
	{
		throw - 3;
	}

	if (file.is_open())
	{
		ss << file.rdbuf();
		file.close();
	}
	else
		throw - 3;

	return ss;
}

void DaysExecutor::doDay(int dayNumber)
{
	stringstream input = readInput(dayNumber);

	switch (dayNumber)
	{
	case 1:
		Day1(input);
		break;
	case 2:
		Day2(input);
		break;
	case 3:
		Day3(input);
		break;
	case 4:
		Day4(input);
		break;
	case 5:
		Day5(input);
		break;
	case 6:
		Day6(input);
		break;
	case 7:
		Day7(input);
		break;
	case 8:
		Day8(input);
		break;
	case 9:
		Day9(input);
		break;
	case 10:
		Day10(input);
		break;
	case 11:
		Day11(input);
		break;
	case 12:
		Day12(input);
		break;
	case 13:
		Day13(input);
		break;
	case 14:
		Day14(input);
		break;
	case 15:
		Day15(input);
		break;
	case 16:
		Day16(input);
		break;
	case 17:
		Day17(input);
		break;
	case 18:
		Day18(input);
		break;
	case 19:
		Day19(input);
		break;
	case 20:
		Day20(input);
		break;
	case 21:
		Day21(input);
		break;
	case 22:
		Day22(input);
		break;
	case 23:
		Day23(input);
		break;
	case 24:
		Day24(input);
		break;
	case 25:
		Day25(input);
		break;

	default:
		break;
	}
}
