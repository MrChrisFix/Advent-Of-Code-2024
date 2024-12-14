#include "../general.h"
#include <regex>
#include <queue>
#include <set>

int Day14_Part1(stringstream& input)
{
	vector<pair<int, int>> positions, velocities;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.empty())
			break;

		smatch match;
		regex_match(line, match, regex("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)"));

		positions.push_back({ stoi(match[2]), stoi(match[1]) });
		velocities.push_back({ stoi(match[4]), stoi(match[3]) });
	}

	const int WIDTH = 101;
	const int HEIGHT = 103;

	int quadrant_score[4]{};

	for (int i = 0; i < positions.size(); i++)
	{
		long long newY = positions[i].first + 100 * velocities[i].first;
		long long newX = positions[i].second + 100 * velocities[i].second;

		newY = newY % HEIGHT;
		newX = newX % WIDTH;
		if (newY < 0)
			newY += HEIGHT;
		if (newX < 0)
			newX += WIDTH;
		positions[i] = { newY, newX };

		if (newY == HEIGHT / 2 || newX == WIDTH / 2)
			continue;

		int quadrant = (newY > HEIGHT / 2 ? 2 : 0) + (newX > WIDTH / 2 ? 1 : 0);
		quadrant_score[quadrant]++;
	}


	int result = quadrant_score[0] * quadrant_score[1] * quadrant_score[2] * quadrant_score[3];

	return result;
}

int Day14_Part2(stringstream& input)
{
	vector<pair<int, int>> positions, velocities;
	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.empty())
			break;

		smatch match;
		regex_match(line, match, regex("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)"));

		positions.push_back({ stoi(match[2]), stoi(match[1]) });
		velocities.push_back({ stoi(match[4]), stoi(match[3]) });
	}

	const int WIDTH = 101;
	const int HEIGHT = 103;
	int elapsed = 0;

	bool searching = true;
	while (searching)
	{
		vector<string> image(HEIGHT, string(WIDTH, '.'));

		//New positions
		for (int i = 0; i < positions.size(); i++)
		{
			long long newY = positions[i].first + velocities[i].first;
			long long newX = positions[i].second + velocities[i].second;

			newY = newY % HEIGHT;
			newX = newX % WIDTH;
			if (newY < 0)
				newY += HEIGHT;
			if (newX < 0)
				newX += WIDTH;
			positions[i] = { newY, newX };
			image[newY][newX] = '#';
		}

		//Check if connected
		set<pair<int, int>> visited;
		for (int i = 0; i < HEIGHT && searching; i++)
		{
			for (int j = 0; j < WIDTH && searching; j++)
			{
				if (image[i][j] == '.' || visited.contains({ i,j }))
					continue;

				queue<pair<int, int>> next;
				next.push({ i,j });
				int cnt = 0;
				visited.insert({ i,j });
				while (!next.empty())
				{
					auto cur = next.front();
					next.pop();
					visited.insert(cur);
					cnt++;
					if (cur.first > 0 && image[cur.first - 1][cur.second] == '#' && !visited.contains({ cur.first - 1, cur.second }))
						next.push({ cur.first - 1, cur.second });
					if (cur.second > 0 && image[cur.first][cur.second - 1] == '#' && !visited.contains({ cur.first, cur.second - 1 }))
						next.push({ cur.first, cur.second - 1 });
					if (cur.first < HEIGHT - 1 && image[cur.first + 1][cur.second] == '#' && !visited.contains({ cur.first + 1, cur.second }))
						next.push({ cur.first + 1, cur.second });
					if (cur.second < WIDTH - 1 && image[cur.first][cur.second + 1] == '#' && !visited.contains({ cur.first, cur.second + 1 }))
						next.push({ cur.first, cur.second + 1 });

					if (cnt > 30)
					{
						searching = false;
						break;
					}
				}
			}
		}

		//If found print the image :)
		if (!searching)
		{
			std::cout << endl << endl;
			for (int i = 0; i < HEIGHT; i++)
				cout << image[i] << endl;

			std::cout << endl << endl;
		}

		elapsed++;
	}

	return elapsed;
}


void Day14(stringstream& input)
{
	cout << "Part 1 result is: " << Day14_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day14_Part2(input) << endl << endl;

	return;
}