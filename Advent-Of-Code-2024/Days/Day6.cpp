#include "../general.h"
#include <set>

pair<int, int> findGuard(const vector<string>& map, char ch = '^')
{
	for (int y = 0; y < map.size(); y++)
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == ch)
				return { y,x };
		}
	return{ -1, -1 };
}

int Day6_Part1(stringstream& input)
{
	vector<string> map;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		map.push_back(line);
	}

	pair<int, int> pos = findGuard(map);

	int dir = 0; //N = 0, E-1, S-2, W-3
	vector<pair<int, int>> change = { {-1,0},{0,1},{1,0},{0,-1} };

	while (true)
	{
		map[pos.first][pos.second] = 'X';

		int nextY = pos.first + change[dir].first;
		int nextX = pos.second + change[dir].second;

		if (nextY < 0 || nextY >= map.size() || nextX < 0 || nextX >= map[0].size())
			break;

		if (map[nextY][nextX] == '#')
		{
			dir = (dir + 1) % 4;
			nextY = pos.first + change[dir].first;
			nextX = pos.second + change[dir].second;
		}
		pos.first = nextY;
		pos.second = nextX;
	}

	int sum = 0;
	for (auto& row : map)
		for (auto& col : row)
			if (col == 'X')
				sum++;

	return sum;
}

struct guardState
{
	pair<int, int> pos;
	int dir;

	bool operator<(const guardState& rhs) const
	{
		if (pos.first != rhs.pos.first)
			return pos.first < rhs.pos.first;
		if (pos.second != rhs.pos.second)
			return pos.second < rhs.pos.second;
		return dir < rhs.dir;
	}
};

int Day6_Part2(stringstream& input)
{
	vector<string> map;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		map.push_back(line);
	}

	pair<int, int> gPos = findGuard(map);

	for (auto& row : map)
		for (auto& col : row)
		{
			if (col == '#' || col == '^')
				continue;
			else
				col = '#';

			int dir = 0; //N = 0, E-1, S-2, W-3
			vector<pair<int, int>> change = { {-1,0},{0,1},{1,0},{0,-1} };
			auto pos = gPos;

			bool isLoop = false;
			set<guardState> seenWalls;
			while (true)
			{
				int nextY = pos.first + change[dir].first;
				int nextX = pos.second + change[dir].second;

				if (nextY < 0 || nextY >= map.size() || nextX < 0 || nextX >= map[0].size())
				{
					break;
				}

				if (map[nextY][nextX] == '#')
				{
					if (!seenWalls.insert({ pos, dir }).second)
					{// The guard has been here
						isLoop = true;
						break;
					}

					dir = (dir + 1) % 4;
					continue;
				}
				pos.first = nextY;
				pos.second = nextX;
			}

			if (isLoop)
			{
				col = 'X';
			}
			else
				col = '.';
		}

	int sum = 0;
	for (auto& row : map)
		for (auto& col : row)
		{
			if (col == 'X')
				sum++;
		}

	return sum;
}


void Day6(stringstream& input)
{
	cout << "Part 1 result is: " << Day6_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day6_Part2(input) << endl << endl;

	return;
}