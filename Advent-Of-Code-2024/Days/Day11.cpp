#include "../general.h"
#include <map>

int numLen(size_t num)
{
	return floor(log10(num)) + 1;
}

pair<size_t, size_t> split(size_t num)
{
	int size = numLen(num);
	size_t power = pow(10, size / 2);

	return { num / power, num % power };
}

size_t blink(map<size_t, size_t> occurences, int blinks)
{
	for (int i = 0; i < blinks; i++)
	{
		map<size_t, size_t> newOcc;
		for (auto& occ : occurences)
		{
			if (occ.first == 0)
				newOcc[1] += occ.second;
			else if (numLen(occ.first) % 2 == 0)
			{
				auto splitted = split(occ.first);
				newOcc[splitted.first] += occ.second;
				newOcc[splitted.second] += occ.second;
			}
			else
			{
				newOcc[occ.first * 2024] += occ.second;
			}
		}
		occurences = newOcc;
	}

	size_t res = 0;

	for (auto& num : occurences)
		res += num.second;

	return res;
}

void Day11(stringstream& input)
{
	map<size_t, size_t> occurences;
	while (!input.eof())
	{
		int num;
		input >> num;
		occurences[num]++;
	}
	size_t part1 = blink(occurences, 25);
	size_t part2 = blink(occurences, 75);

	cout << "Part 1 result is: " << part1 << endl;
	cout << "Part 2 result is: " <<part2 << endl << endl;

	return;
}