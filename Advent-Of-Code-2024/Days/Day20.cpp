#include "../general.h"

vector<vector<int>> getTimedPath(const vector<string>& raceMap, pair<int, int> start, pair<int, int> end)
{
	vector<vector<int>> timed(raceMap.size(), vector<int>(raceMap[0].size(), -'#'));

	pair<int, int> pos = start;
	pair<int, int> prev;

	int i = 0;
	while (pos != end)
	{
		timed[pos.first][pos.second] = i++;

		if (raceMap[pos.first + 1][pos.second] != '#' && pos.first + 1 != prev.first)
		{
			prev = pos;
			pos = { pos.first + 1, pos.second };
		}
		else if (raceMap[pos.first - 1][pos.second] != '#' && pos.first - 1 != prev.first)
		{
			prev = pos;
			pos = { pos.first - 1, pos.second };
		}
		else if (raceMap[pos.first][pos.second + 1] != '#' && pos.second + 1 != prev.second)
		{
			prev = pos;
			pos = { pos.first, pos.second + 1 };
		}
		else if (raceMap[pos.first][pos.second - 1] != '#' && pos.second - 1 != prev.second)
		{
			prev = pos;
			pos = { pos.first, pos.second - 1 };
		}

		if (pos == end)
			timed[pos.first][pos.second] = i++;
	}

	return timed;
}


int countCheats(const vector<vector<int>> timedRaceMap, const pair<int, int> start, const pair<int, int> end, const int radius, const int picoSafe)
{
	int count = 0;
	pair<int, int> pos = start;

	pair<int, int> dirs[4] = { {0,1},{1,0}, {0,-1}, {-1,0} };

	while (pos != end)
	{
		for (int y = radius; y >= -radius; y--)
		{
			if (pos.first + y > timedRaceMap.size() - 1 || pos.first + y < 0)
				continue;

			for (int x = radius - abs(y); x >= -(radius - abs(y)); x--)
			{
				if (y == 0 && x == 0) continue;

				if (pos.second + x < timedRaceMap.size() && pos.second + x >= 0 && timedRaceMap[pos.first + y][pos.second + x] != -'#')
				{
					int diff = timedRaceMap[pos.first + y][pos.second + x] - timedRaceMap[pos.first][pos.second] - abs(y) - abs(x);
					if (diff >= picoSafe)
					{
						count++;
					}
				}
			}
		}


		for (auto dir : dirs)
		{
			pair<int, int> next = { pos.first + dir.first, pos.second + dir.second };
			if (timedRaceMap[next.first][next.second] > timedRaceMap[pos.first][pos.second])
			{
				pos = next;
				break;
			}
		}
	}

	return count;
}

void Day20(stringstream& input)
{
	vector<string> raceMap;
	pair<int, int> start, end;

	while (!input.eof())
	{
		string line;
		input >> line;
		raceMap.push_back(line);

		size_t found = line.find('S');
		if (found != string::npos)
			start = { raceMap.size() - 1, found };

		found = line.find('E');
		if (found != string::npos)
			end = { raceMap.size() - 1, found };
	}
	auto pathed = getTimedPath(raceMap, start, end);

	int part1 = countCheats(pathed, start, end, 2, 100);
	cout << "Part 1 result is: " << part1 << endl;

	int part2 = countCheats(pathed, start, end, 20, 100);
	cout << "Part 2 result is: " << part2 << endl << endl;

	return;
}