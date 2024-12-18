#include "../general.h"
#include <queue>
#include <set>

struct position
{
	int y, x;
	int steps = 0;

	pair<int, int> getCoords() const
	{
		return { y,x };
	}
};

int getSteps(const vector<string> map, pair<int, int> from, pair<int, int> to, char wall = '#')
{
	queue<position> toSearch;
	position start; start.y = from.first, start.x = from.second;
	toSearch.push(start);

	set<pair<int, int>> visited;

	while (!toSearch.empty())
	{
		auto now = toSearch.front();
		toSearch.pop();

		if (!visited.insert(now.getCoords()).second)
		{
			continue;
		}

		if (now.getCoords() == to)
		{
			return now.steps;
		}

		if (now.y > 0 && map[now.y - 1][now.x] != wall)
			toSearch.push({ now.y - 1, now.x, now.steps + 1 });
		if (now.y < map.size() - 1 && map[now.y + 1][now.x] != wall)
			toSearch.push({ now.y + 1, now.x, now.steps + 1 });

		if (now.x > 0 && map[now.y][now.x - 1] != wall)
			toSearch.push({ now.y, now.x - 1, now.steps + 1 });
		if (now.x < map[0].size() - 1 && map[now.y][now.x + 1] != wall)
			toSearch.push({ now.y, now.x + 1, now.steps + 1 });
	}

	return 0;
}


int Day18_Part1(stringstream& input)
{
	vector<pair<int, int>> positions;
	while (!input.eof())
	{
		int x, y;
		char comma;
		input >> x >> comma >> y;
		positions.push_back({ y,x });
	}

	const int SIZE = 1 + 70;
	const int BYTES = 1024;
	vector<string> map(SIZE, string(SIZE, '.'));

	for (int i = 0; i < BYTES; i++)
	{
		map[positions[i].first][positions[i].second] = '#';
	}

	int steps = getSteps(map, { 0,0 }, { SIZE - 1, SIZE - 1 }, '#');

	return steps;
}

string Day18_Part2(stringstream& input)
{
	vector<pair<int, int>> positions;
	while (!input.eof())
	{
		int x, y;
		char comma;
		input >> x >> comma >> y;
		positions.push_back({ y,x });
	}

	const int SIZE = 1 + 70;
	const int BYTES = 1024;
	vector<string> map(SIZE, string(SIZE, '.'));

	for (int i = 0; i < BYTES; i++)
	{
		map[positions[i].first][positions[i].second] = '#';
	}

	string result;

	for (int i = BYTES; i < positions.size(); i++)
	{
		map[positions[i].first][positions[i].second] = '#';
		int steps = getSteps(map, { 0,0 }, { SIZE - 1, SIZE - 1 }, '#');
		if (steps == 0)
		{
			result += to_string(positions[i].second) + "," + to_string(positions[i].first);
			break;
		}
	}

	return result; //Slow solution
}


void Day18(stringstream& input)
{
	cout << "Part 1 result is: " << Day18_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day18_Part2(input) << endl << endl;

	return;
}