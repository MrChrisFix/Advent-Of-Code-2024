#include "../general.h"
#include <map>
#include <set>

void readDay5Input(stringstream& input, map<int, set<int>>& rules, vector<vector<int>>& pages)
{
	bool readRulesPart = true;
	while(!input.eof())
	{
		string sline;
		getline(input, sline);
		if (sline.empty())
		{
			readRulesPart = false;
			continue;
		}
		stringstream line(sline);

		if (readRulesPart)
		{
			while (!line.eof())
			{
				int num1, num2;
				char I;
				line >> num1 >> I >> num2;
				rules[num2].insert(num1);
			}
		}
		else
		{
			vector<int> page;
			while (!line.eof())
			{
				int num;
				char comma;
				line >> num >> comma;

				page.push_back(num);
			}
			pages.push_back(page);
		}
	}
}


int Day5_Part1(stringstream& input)
{
	map<int, set<int>> aftBef; //after before mapping
	vector<vector<int>> pages;

	readDay5Input(input, aftBef, pages);

	int sum = 0;
	for (auto& page : pages)
	{
		bool invalid = false;
		for (int i = 0; i < page.size() && !invalid; i++)
		{
			set<int> rightSide(page.begin() + i + 1, page.end());
			auto list = aftBef[page[i]];

			for (auto& bef : list)
			{
				if (rightSide.contains(bef))
				{
					invalid = true;
					break;
				}
			}
		}

		if (!invalid)
		{
			sum += page[page.size() / 2];
		}
	}

	return sum;
}

vector<int> repairPage(vector<int> broken, map<int, set<int>> rules)
{
	bool didRepairs = true; //this is for skipping fully repaired pages 

	for (int s = 0; s < broken.size() && didRepairs; s++)
	{
		didRepairs = false;
		for (int i = 0; i < broken.size(); i++)
		{
			set<int> rightSide(broken.begin() + i + 1, broken.end());
			auto list = rules[broken[i]];

			for (auto& bef : list)
			{
				if (rightSide.contains(bef))
				{
					swap(broken[i], broken[i + 1]);
					didRepairs = true;
					break;
				}
			}
		}
	}
	return broken;
}

int Day5_Part2(stringstream& input)
{
	map<int, set<int>> aftBef; //after before mapping
	vector<vector<int>> pages;

	readDay5Input(input, aftBef, pages);

	int sum = 0;
	for (auto& page : pages)
	{
		auto repaired = repairPage(page, aftBef);
		if (repaired != page)
		{
			page = repaired;
			sum += page[page.size() / 2];
		}
	}

	return sum;
}


void Day5(stringstream& input)
{
	cout << "Part 1 result is: " << Day5_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day5_Part2(input) << endl << endl;

	return;
}