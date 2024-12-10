#include "../general.h"
#include <set>

int countTrails(const vector<vector<int>>& map, int x, int y, int current, set<pair<int, int>>& nines)
{
	if (current == 9)
	{
		nines.insert({ y,x });
		return 1;
	}

	int paths = 0;

	if (x + 1 < map[y].size() && map[y][x + 1] == current + 1)
		paths += countTrails(map, x + 1, y, current + 1, nines);
	if (y + 1 < map.size() && map[y + 1][x] == current + 1)
		paths += countTrails(map, x, y + 1, current + 1, nines);

	if (x - 1 >= 0 && map[y][x - 1] == current + 1)
		paths += countTrails(map, x - 1, y, current + 1,nines);
	if (y - 1 >= 0 && map[y - 1][x] == current + 1)
		paths += countTrails(map, x, y - 1, current + 1,nines);

	return paths;
}

void Day10(stringstream& input)
{
	vector<vector<int>> map;
	string line;
	while (getline(input, line))
	{
		vector<int> row;
		for (char c : line)
		{
			row.push_back(c - '0');
		}
		map.push_back(row);
	}

	int resultPart1 = 0;
	int resultPart2 = 0;

	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == 0)
			{
				set<pair<int, int>> pos;
				resultPart2 += countTrails(map, x, y, 0, pos);
				resultPart1 += pos.size();
			}
		}
	}

	cout << "Part 1 result is: " << resultPart1 << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << resultPart2 << endl << endl;

	return;
}