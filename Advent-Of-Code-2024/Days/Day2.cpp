#include "../general.h"
#include <set>

int Day2_Part1(stringstream& input)
{
	int safe = 0;
	while (!input.eof())
	{
		string sline;
		getline(input, sline);
		stringstream line(sline);

		int num1, num2;
		line >> num1 >> num2;

		if (abs(num1 - num2) > 3 || num1 == num2)
			continue;

		bool decr = num1 > num2;
		num1 = num2;

		bool good = true;
		while (!line.eof())
		{
			line >> num2;

			if ((decr && num1 < num2) || (!decr && num1 > num2))
			{
				good = false;
				break;
			}

			if (abs(num1 - num2) > 3 || num1 == num2)
			{
				good = false;
				break;
			}

			num1 = num2;
		}
		if (good)
			safe++;
	}


	return safe;
}

int sign(int x)
{
	if (x < 0)
		return -1;
	else if (x > 0)
		return 1;
	return x;
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

		bool onefail = false;
		bool good = true;
		vector<int> sortedNums = nums;
		ranges::sort(sortedNums);

		if (ranges::max(nums) == nums[0] || ranges::max(nums) == nums[1])
			ranges::reverse(nums);


		//1. Check for duplicates
		//2. Check fow many numbers were changed
		//3. Check diff in sotred between nums
		//4. Check if the difference between the changed numbers is less than 3

		set<int> duplicates;

		//Duplicates
		for (int i = 1; i < sortedNums.size() && good; i++)
		{
			if (sortedNums[i] == sortedNums[i - 1])
			{
				duplicates.insert(sortedNums[i]);
				if (onefail)
					good = false;
				onefail = true;
			}
		}

		//0 < diff < 3
		for (int i = 1; i < sortedNums.size() && good; i++)
		{
			if ((sortedNums[i] - sortedNums[i - 1]) > 3)
			{
				if ((i == sortedNums.size() - 1 && onefail == false) || i == 0)
				{
					onefail = true;
				}
				else
				{
					good = false;
					onefail = true;
				}
			}
		}

		//Difference
		for (int i = 0; i < sortedNums.size() && good; i++)
		{
			if (abs(sortedNums[i] - nums[i]) > 3)
			{
				if (sortedNums[i] == sortedNums[i - 1])
				{
					if (onefail)
						good = false;
					onefail = true;
				}
			}
		}

		for (int i = 1; i < nums.size() - 1 && good; i++)
		{
			if (sign(nums[i - 1] - nums[i]) != sign(nums[i] - nums[i + 1]) &&
				(!duplicates.contains(nums[i - 1]) || !duplicates.contains(nums[i]) || !duplicates.contains(nums[i + 1]))
				)
			{
				if (onefail)
				{
					good = false;
				}
				onefail = true;
			}
		}

		if (good) //25 23 25 28 29 32 35 -> currently classified as bad
			safe++;


		//for (int i = 1; i < nums.size() - 1; i++)
		//{
		//	if (
		//		sign(nums[i - 1] - nums[i]) != sign(nums[i] - nums[i + 1]) ||
		//		nums[i - 1] == nums[i] || nums[i] == nums[i + 1] ||
		//		abs(nums[i - 1] - nums[i]) > 3 || abs(nums[i] - nums[i + 1]) > 3
		//		)
		//	{
		//		if (onefail)
		//		{
		//			good = false;
		//			break;
		//		}
		//		onefail = true;
		//		if (i == 1 && abs(nums[i] - nums[i + 1]) <= 3)
		//			nums.erase(nums.begin());
		//		else if (abs(nums[i - 1] - nums[i + 1]) <= 3 && nums[i - 1] != nums[i + 1])
		//			nums.erase(nums.begin() + i);
		//		else if (i == nums.size() - 2 && abs(nums[i] - nums[i - 1]) <= 3)
		//			nums.erase(nums.begin() + i + 1);
		//		else
		//		{
		//			good = false;
		//			break;
		//		}
		//		i--;
		//	}
		//}
		//if (good)
		//	safe++;

		/*int num1, num2, num3;
		line >> num1 >> num2 >> num3;
		bool oneFail = false;

		if (abs(num1 - num2) > 3 || num1 == num2)
		{
			oneFail = true;

			if (abs(num1 - num3) > 3)
			{
				num1 = num2;
				num2 = num3;
			}
			else
			{
				num2 = num3;
			}

			if (num1 == num2 || abs(num1 - num2) > 3)
				continue;
		}

		bool decr = num1 > num2;

		bool good = true;
		while (!line.eof())
		{

			bool end = line.eof();


			if (
				(decr && num2 < num3) ||
				(!decr && num2 > num3) ||
				num2 == num3 ||
				abs(num2 - num3) > 3
				)
			{
				if (oneFail == false)
				{
					if (abs(num1 - num3) > 3 && !end)
					{
						good = false;
						break;
					}


					oneFail = true;
					continue;
				}
				else
				{
					good = false;
					break;
				}

			}

			num1 = num2;
			num2 = num3;

			line >> num3;
		}
		if (good)
			safe++;*/
	}

	//breaks at eg. 1 4 2 4 4

	return safe; //406 too low
}


void Day2(stringstream& input)
{
	cout << "Part 1 result is: " << Day2_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day2_Part2(input) << endl << endl;

	return;
}