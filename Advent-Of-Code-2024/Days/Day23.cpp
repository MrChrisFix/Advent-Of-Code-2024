#include "../general.h"
#include <map>
#include <set>

int Day23_Part1(stringstream& input)
{
	map<string, set<string>> connections;

	while (!input.eof())
	{
		string line, first, second;
		input >> line;
		first = line.substr(0, 2);
		second = line.substr(3, 2);
		connections[first].insert(second);
		connections[second].insert(first);
	}

	set<set<string>> computerSets;

	for (auto& PC : connections)
	{
		for (auto& first : PC.second)
		{
			for (auto&second : PC.second)
			{
				if (first == second)
					continue;

				if (PC.first[0] != 't' && first[0] != 't' && second[0] != 't')
					continue;

				if (connections[first].contains(second) && connections[second].contains(PC.first))
				{
					set<string> PCset = {first, second, PC.first};
					computerSets.insert(PCset);
				}
			}
		}
	}

	int t_computers = computerSets.size();

	return t_computers;
}

string Day23_Part2(stringstream& input)
{
	map<string, set<string>> connections;

	while (!input.eof())
	{
		string line, first, second;
		input >> line;
		first = line.substr(0, 2);
		second = line.substr(3, 2);
		connections[first].insert(second);
		connections[second].insert(first);
	}

	set<set<string>> computerSets;

	for (auto& PC : connections)
	{
		for (auto& first : PC.second)
		{
			for (auto& second : PC.second)
			{
				if (first == second)
					continue;

				if (PC.first[0] != 't' && first[0] != 't' && second[0] != 't')
					continue;

				if (connections[first].contains(second) && connections[second].contains(PC.first))
				{
					set<string> PCset = { first, second, PC.first };
					computerSets.insert(PCset);
				}
			}
		}
	}

	//WIP

	int maxSize = 0;

	for (auto& TPC : connections)
	{
		if (TPC.first[0] != 't')
			continue;

		int cliqueSize = 0;

		for (auto& first : TPC.second)
		{
			int connected = 0;
			for (auto& second : TPC.second)
			{
				if (first == second)
					continue;

				if (connections[first].contains(second))
				{
					connected++;
				}
			}
			cliqueSize = max(cliqueSize, connected);
		}
		maxSize = max(maxSize, cliqueSize);
	}


	return "";
}


void Day23(stringstream& input)
{
	cout<<"Part 1 result is: " << Day23_Part1(input)<<endl;
	input.seekg(0);
	cout<<"Part 2 result is: " << Day23_Part2(input)<<endl<<endl;

	return;
}