#include "../general.h"
#include <set>

size_t Day22_Part1(stringstream& input)
{
	size_t result = 0;
	while (!input.eof())
	{
		size_t num;
		input >> num;
		for (int i = 0; i < 2000; i++)
		{
			num = (num ^ num << 6) % 16777216;
			num = (num ^ num >> 5) % 16777216;
			num = (num ^ num << 11) % 16777216;
		}
		result += num;
	}

	return result;
}

int Day22_Part2(stringstream& input)
{

	vector<vector<short>> allPrices;
	vector<vector<short>> allPriceDiffs;
	while (!input.eof())
	{
		vector<short> prices(2000);
		vector<short> priceDiffs(2000);
		size_t num;
		input >> num;
		short prev = num % 10;
		for (int i = 0; i < 2000; i++)
		{
			num = (num ^ num << 6) % 16777216;
			num = (num ^ num >> 5) % 16777216;
			num = (num ^ num << 11) % 16777216;

			priceDiffs[i] = num % 10 - prev;
			prev = num % 10;
			prices[i] = num % 10;
		}
		allPrices.push_back(prices);
		allPriceDiffs.push_back(priceDiffs);
	}

	set<vector<short>> tested;
	int bananas = 0;

	//VEEEEERY SLOW
	//TODO: optimize

	for (auto& vec : allPriceDiffs)
	{
		for (int i = 0; i < vec.size() - 4; i++)
		{
			vector<short> subVec(vec.begin() + i, vec.begin() + i + 4);
			if (!tested.insert(subVec).second)
				continue;
			int gotBananas = 0;

			for (int d = 0; d < allPriceDiffs.size(); d++)
			{
				auto& diffs = allPriceDiffs[d];
				auto it = search(diffs.begin(), diffs.end(), vec.begin() + i, vec.begin() + i + 4);

				if (it != diffs.end())
				{
					advance(it, 3);
					if (it != diffs.end())
					{
						gotBananas += allPrices[d][distance(diffs.begin(), it)];
					}
				}
			}

			bananas = max(bananas, gotBananas);
		}
	}

	return bananas;
}


void Day22(stringstream& input)
{
	cout << "Part 1 result is: " << Day22_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day22_Part2(input) << endl << endl;

	return;
}