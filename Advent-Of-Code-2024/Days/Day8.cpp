#include "../general.h"
#include <map>
#include <set>

int Day8_Part1(stringstream& input)
{
	int width = 0, height = 0;

	map<char, vector<pair<int, int>>> positions;

	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.empty())
			break;

		width = line.size();

		for (int x = 0; x < line.size(); x++)
		{
			if (line[x] != '.')
			{
				positions[line[x]].push_back({ height, x });
			}
		}

		height++;
	}

	set<pair<int, int>> antiNodes;

	for (auto& freq : positions)
	{
		vector<pair<int, int>>& pos = freq.second;
		for (int i = 0; i < pos.size(); i++)
		{
			for (int j = i + 1; j < pos.size(); j++)
			{
				pair<int, int> vec = { pos[j].first - pos[i].first, pos[j].second - pos[i].second };
				int curX = pos[i].second, curY = pos[i].first;

				if (curX + 2 * vec.second < width && curY + 2 * vec.first < height &&
					curX + 2 * vec.second >= 0 && curY + 2 * vec.first >= 0
					)
				{
					antiNodes.insert({ curY + 2 * vec.first, curX + 2 * vec.second });
				}

				if (curX - vec.second < width && curY - vec.first < height &&
					curX - vec.second >= 0 && curY - vec.first >= 0
					)
				{
					antiNodes.insert({ curY - vec.first, curX - vec.second });
				}
			}
		}
	}

	int count = antiNodes.size();

	return count;
}

int Day8_Part2(stringstream& input)
{
	int width = 0, height = 0;

	map<char, vector<pair<int, int>>> positions;

	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.empty())
			break;

		width = line.size();

		for (int x = 0; x < line.size(); x++)
		{
			if (line[x] != '.')
			{
				positions[line[x]].push_back({ height, x });
			}
		}

		height++;
	}

	set<pair<int, int>> antiNodes;

	for (auto& freq : positions)
	{
		vector<pair<int, int>>& pos = freq.second;
		antiNodes.insert(pos.begin(), pos.end());
		for (int i = 0; i < pos.size(); i++)
		{
			for (int j = i + 1; j < pos.size(); j++)
			{
				pair<int, int> vec = { pos[j].first - pos[i].first, pos[j].second - pos[i].second };
				int curX = pos[i].second + vec.second, curY = pos[i].first + vec.first;

				while (
					curX + vec.second < width && curY + vec.first < height &&
					curX + vec.second >= 0 && curY + vec.first >= 0
					)
				{
					antiNodes.insert({ curY + vec.first, curX + vec.second });
					curX += vec.second;
					curY += vec.first;
				}

				curX = pos[i].second, curY = pos[i].first;

				while (
					curX - vec.second < width && curY - vec.first < height &&
					curX - vec.second >= 0 && curY - vec.first >= 0
					)
				{
					antiNodes.insert({ curY - vec.first, curX - vec.second });
					curX -= vec.second;
					curY -= vec.first;
				}
			}
		}
	}

	int count = antiNodes.size();

	return count;
}


void Day8(stringstream& input)
{
	cout << "Part 1 result is: " << Day8_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day8_Part2(input) << endl << endl;

	return;
}