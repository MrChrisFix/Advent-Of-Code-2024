#include "../general.h"
#include <map>

int Day1_Part1(stringstream& input)
{
	vector<int> list1, list2;

	while (!input.eof())
	{
		int num1=0, num2=0;
		input >> num1 >> num2;

		list1.push_back(num1);
		list2.push_back(num2);
	}

	ranges::sort(list1);
	ranges::sort(list2);

	int sum = 0;
	for (int i = 0; i < list1.size(); i++)
	{
		sum += abs(list1[i] - list2[i]);
	}

	return sum;
}

int Day1_Part2(stringstream& input)
{
	vector<int> list;
	map<int, int> repeats;

	while (!input.eof())
	{
		int num1 = 0, num2 = 0;
		input >> num1 >> num2;

		list.push_back(num1);
		repeats[num2]++;
	}

	int score = 0;
	for (int i = 0; i < list.size(); i++)
	{
		score += list[i] * repeats[list[i]];
	}

	return score;
}


void Day1(stringstream& input)
{
	cout<<"Part 1 result is: " << Day1_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day1_Part2(input)<<endl<<endl;

	return;
}