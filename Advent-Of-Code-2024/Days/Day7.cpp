#include "../general.h"


bool hasSolutionP1(const size_t result, vector<size_t> nums)
{
	size_t poss = pow(2, nums.size());

	for (size_t i = 0; i < poss; i++)
	{
		size_t tmp = i;
		size_t res = nums[0];

		for (size_t j = 1; j < nums.size(); j++)
		{
			if (tmp % 2 == 0)
				res += nums[j];
			else
				res *= nums[j];

			tmp >>= 1;
		}

		if (res == result)
			return true;
	}

	return false;
}


size_t Day7_Part1(stringstream& input)
{
	size_t sum = 0;

	while (!input.eof())
	{
		size_t result;
		input >> result;
		input.get();

		string sline;
		getline(input, sline);
		stringstream line(sline);

		vector<size_t> nums;
		size_t num;
		while (line >> num)
		{
			nums.push_back(num);
		}
		
		if (hasSolutionP1(result, nums))
			sum += result;
	}

	return sum;
}

bool hasSolutionP2(const size_t result, vector<size_t> nums)
{
	size_t poss = pow(3, nums.size());

	for (size_t i = 0; i < poss; i++)
	{
		size_t tmp = i;
		size_t res = nums[0];

		for (size_t j = 1; j < nums.size(); j++)
		{
			if (tmp % 3 == 0)
				res += nums[j];
			else if(tmp % 3 == 1)
				res *= nums[j];
			else
			{
				int numSize = floor(log10(nums[j])) + 1;
				res = res * pow(10, numSize) + nums[j] ;
			}

			if (res > result)
				break;

			tmp /= 3;
		}

		if (res == result)
			return true;
	}

	return false;
}

size_t Day7_Part2(stringstream& input)
{
	size_t sum = 0;

	while (!input.eof())
	{
		size_t result;
		input >> result;
		input.get();

		string sline;
		getline(input, sline);
		stringstream line(sline);

		vector<size_t> nums;
		size_t num;
		while (line >> num)
		{
			nums.push_back(num);
		}

		if (hasSolutionP2(result, nums))
			sum += result;
	}

	return sum;
}


void Day7(stringstream& input)
{
	cout << "Part 1 result is: " << Day7_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day7_Part2(input) << endl << endl;

	return;
}