#include "../general.h"

size_t Day9_Part1(stringstream& input)
{
	string data = input.str();

	vector<int> IDs;
	size_t cursor = 0;

	for (int i = 0; i < data.size(); i += 2)
	{
		int id = i / 2;
		IDs.resize(IDs.size() + data[i] - '0');

		fill(IDs.begin() + cursor, IDs.end(), id);
		cursor += data[i] - '0';

		if (i != data.size() - 1)
		{
			IDs.resize(IDs.size() + data[i + 1] - '0');

			fill(IDs.begin() + cursor, IDs.end(), -1);
			cursor += data[i + 1] - '0';
		}
	}
	size_t checksum = 0;

	size_t pos = IDs.size() - 1;
	for (size_t i = 0; i < IDs.size(); i++)
	{
		if (IDs[i] == -1 && pos > i)
		{
			swap(IDs[i], IDs[pos]);
			while (IDs[pos] == -1)
				pos--;
		}
		else if (IDs[i] == -1)
			break;

		checksum += IDs[i] * i;
	}

	return checksum;
}

size_t Day9_Part2(stringstream& input)
{
	string data = input.str();

	const int numOfIds = data.size() / 2;

	vector<int> IDs;
	size_t cursor = 0;

	vector<pair<int, int>> freeSpaces; //amount, where

	for (int i = 0; i < data.size(); i += 2)
	{
		int id = i / 2;
		IDs.resize(IDs.size() + data[i] - '0');

		fill(IDs.begin() + cursor, IDs.end(), id);
		cursor += data[i] - '0';

		if (i != data.size() - 1)
		{
			IDs.resize(IDs.size() + data[i + 1] - '0');

			freeSpaces.push_back({ data[i + 1] - '0', cursor });
			fill(IDs.begin() + cursor, IDs.end(), -1);
			cursor += data[i + 1] - '0';
		}
	}

	size_t watched = data.size() - 1;

	int i = 0;
	int fr = 0;
	while (i < numOfIds)
	{
		watched = data.size() - 1 - 2 * i;

		for (fr = 0; fr < freeSpaces.size(); fr++)
		{
			if (freeSpaces[fr].first >= (data[watched] - '0') && fr < watched / 2)
				break;
		}

		if (fr >= freeSpaces.size() || fr >= watched)
		{
			i++;
			continue;
		}

		//SWAP
		int amount = data[watched] - '0';

		auto from1 = IDs.begin() + freeSpaces[fr].second;\
		auto to1 = from1 + amount;
		auto from2 = ranges::find(IDs, numOfIds - i);
		i++;

		swap_ranges(from1, to1, from2);

		freeSpaces[fr].first -= amount;
		freeSpaces[fr].second += amount;
	}

	size_t checksum = 0;
	for (size_t i = 0; i < IDs.size(); i++)
	{
		if (IDs[i] != -1)
			checksum += IDs[i] * i;
	}

	return checksum;
}


void Day9(stringstream& input)
{
	cout << "Part 1 result is: " << Day9_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day9_Part2(input) << endl << endl;

	return;
}