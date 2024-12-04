#include "../general.h"

int searchXMASFromPos(const vector<string>& map, int y, int x)
{
	int found = 0;
	//straight
	if (x + 3 <= map[0].size() - 1 && map[y][x + 1] == 'M' && map[y][x + 2] == 'A' && map[y][x + 3] == 'S')
	{
		found++;
	}
	if (x >= 3 && map[y][x - 1] == 'M' && map[y][x - 2] == 'A' && map[y][x - 3] == 'S')
	{
		found++;
	}
	if (y + 3 <= map.size() - 1 && map[y + 1][x] == 'M' && map[y + 2][x] == 'A' && map[y + 3][x] == 'S')
	{
		found++;
	}
	if (y >= 3 && map[y - 1][x] == 'M' && map[y - 2][x] == 'A' && map[y - 3][x] == 'S')
	{
		found++;
	}

	//diagonal
	if (x + 3 <= map[0].size() - 1 && y + 3 <= map.size() - 1 && map[y + 1][x + 1] == 'M' && map[y + 2][x + 2] == 'A' && map[y + 3][x + 3] == 'S')
	{
		found++;
	}
	if (x >= 3 && y + 3 <= map.size() - 1 && map[y + 1][x - 1] == 'M' && map[y + 2][x - 2] == 'A' && map[y + 3][x - 3] == 'S')
	{
		found++;
	}
	if (x + 3 <= map[0].size() - 1 && y >= 3 && map[y - 1][x + 1] == 'M' && map[y - 2][x + 2] == 'A' && map[y - 3][x + 3] == 'S')
	{
		found++;
	}
	if (x >= 3 && y >= 3 && map[y - 1][x - 1] == 'M' && map[y - 2][x - 2] == 'A' && map[y - 3][x - 3] == 'S')
	{
		found++;
	}

	return found;
}


int Day4_Part1(stringstream& input)
{
	vector<string> map;

	while (!input.eof())
	{
		string line;
		input >> line;
		if (line.empty())
			continue;
		map.push_back(line);
	}

	int found = 0;

	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			if (map[y][x] == 'X')
			{
				found += searchXMASFromPos(map, y, x);
			}
		}
	}

	return found;
}

bool isX_MASinPos(const vector<string>& map, const int y, const int x)
{
	if (x == 0 || y == 0 || x == map[y].size() - 1 || y == map.size() - 1)
		return false;

	//	 1		 2		 3		 4
	//	M_S		M_M		S_M		S_S
	//	_A_		_A_		_A_		_A_
	//	M_S		S_S		S_M		M_M
	if (map[y - 1][x - 1] == 'M' && map[y + 1][x + 1] == 'S' && map[y + 1][x - 1] == 'M' && map[y - 1][x + 1] == 'S' ||
		map[y - 1][x - 1] == 'M' && map[y + 1][x + 1] == 'S' && map[y - 1][x + 1] == 'M' && map[y + 1][x - 1] == 'S' ||
		map[y - 1][x + 1] == 'M' && map[y + 1][x - 1] == 'S' && map[y + 1][x + 1] == 'M' && map[y - 1][x - 1] == 'S' ||
		map[y + 1][x - 1] == 'M' && map[y - 1][x + 1] == 'S' && map[y + 1][x + 1] == 'M' && map[y - 1][x - 1] == 'S'
		)
		return true;

	return false;
}



int Day4_Part2(stringstream& input)
{
	vector<string> map;

	while (!input.eof())
	{
		string line;
		input >> line;
		if (line.empty())
			continue;
		map.push_back(line);
	}

	int found = 0;

	for (int y = 1; y < map.size()-1; y++)
	{
		for (int x = 1; x < map[0].size()-1; x++)
		{
			if (map[y][x] == 'A')
			{
				found += isX_MASinPos(map, y, x);
			}
		}
	}

	return found;
}


void Day4(stringstream& input)
{
	cout << "Part 1 result is: " << Day4_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day4_Part2(input) << endl << endl;

	return;
}