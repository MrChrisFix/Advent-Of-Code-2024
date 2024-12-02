#include "../general.h"
#include <set>


int sign(int x)
{
	if (x < 0)
		return -1;
	else if (x > 0)
		return 1;
	return x;
}

bool isSafe(vector<int> nums)
{
	for (int i = 1; i < nums.size(); i++)
	{
		if (abs(nums[i] - nums[i - 1]) > 3 ||
			nums[i] == nums[i - 1] ||
			(i != nums.size() - 1 && sign(nums[i - 1] - nums[i]) != sign(nums[i] - nums[i + 1]))
			)
			return false;
	}

	return true;
}

int Day2_Part1(stringstream& input)
{
	int safe = 0;
	while (!input.eof())
	{
		string sline;
		getline(input, sline);
		stringstream line(sline);

		vector<int> nums;
		while (!line.eof())
		{
			int num;
			line >> num;
			nums.push_back(num);
		}

		if (isSafe(nums))
			safe++;
	}


	return safe;
}

int Day2_Part2(stringstream& input)
{
	int safe = 0;
	while (!input.eof())
	{
		string sline;
		getline(input, sline);
		stringstream line(sline);

		vector<int> nums;
		while (!line.eof())
		{
			int num;
			line >> num;
			nums.push_back(num);
		}

		if (isSafe(nums))
		{
			safe++;
			continue;
		}

		for (int i = 0; i < nums.size(); i++)
		{
			vector<int> numsCopy = nums;
			numsCopy.erase(numsCopy.begin() + i);
			if (isSafe(numsCopy))
			{
				safe++;
				break;
			}
		}
	}

	return safe;
}


void Day2(stringstream& input)
{
	cout << "Part 1 result is: " << Day2_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day2_Part2(input) << endl << endl;

	return;
}