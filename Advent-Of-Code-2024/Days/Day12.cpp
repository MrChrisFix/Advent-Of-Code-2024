#include "../general.h"
#include <queue>
#include <set>

struct Farm
{
	int field, fences, corners;
};

Farm getFieldFencesAndCorners(const vector<string> farm, queue<pair<int, int>>& nextPos, set<pair<int, int>>& visited)
{
	int field = 0, fences = 0, corners = 0;

	char searched = farm[nextPos.front().first][nextPos.front().second];

	while (!nextPos.empty())
	{
		auto now = nextPos.front();
		nextPos.pop();

		if (!visited.insert(now).second)
		{
			continue;
		}
		field++;

#define UP (now.first > 0 && farm[now.first - 1][now.second] == searched)
#define LEFT (now.second > 0 && farm[now.first][now.second - 1] == searched)
#define DOWN (now.first < farm.size() - 1 && farm[now.first + 1][now.second] == searched)
#define RIGHT (now.second < farm[0].size() - 1 && farm[now.first][now.second + 1] == searched)

		if (UP)
		{
			nextPos.push({ now.first - 1, now.second });
		}
		else
			fences++;

		if (LEFT)
		{
			nextPos.push({ now.first, now.second - 1 });
		}
		else
			fences++;

		if (DOWN)
		{
			nextPos.push({ now.first + 1, now.second });
		}
		else
			fences++;

		if (RIGHT)
		{
			nextPos.push({ now.first, now.second + 1 });
		}
		else
			fences++;

		//Convex
		if (!(UP) && !(LEFT))
			corners++;
		if (!(UP) && !(RIGHT))
			corners++;
		if (!(DOWN) && !(LEFT))
			corners++;
		if (!(DOWN) && !(RIGHT))
			corners++;

		//Concave
		if (UP && LEFT && farm[now.first - 1][now.second - 1] != searched)
			corners++;
		if (UP && RIGHT && farm[now.first - 1][now.second + 1] != searched)
			corners++;
		if (DOWN && LEFT && farm[now.first + 1][now.second - 1] != searched)
			corners++;
		if (DOWN && RIGHT && farm[now.first + 1][now.second + 1] != searched)
			corners++;
	}

	return { field, fences, corners };
}

void Day12(stringstream& input)
{
	vector<string> farm;
	while (!input.eof())
	{
		string line;
		input >> line;
		farm.push_back(line);
	}

	queue<pair<int, int>> nextPos;
	set<pair<int, int>> visited;

	int scoreP1 = 0;
	int scoreP2 = 0;

	for (int y = 0; y < farm.size(); y++)
	{
		for (int x = 0; x < farm[y].size(); x++)
		{
			if (visited.contains({ y,x }))
				continue;

			nextPos.push({ y,x });

			Farm res = getFieldFencesAndCorners(farm, nextPos, visited);

			scoreP1 += res.field * res.fences;
			scoreP2 += res.field * res.corners;
		}
	}

	cout << "Part 1 result is: " << scoreP1 << endl;
	cout << "Part 2 result is: " << scoreP2 << endl << endl;

	return;
}