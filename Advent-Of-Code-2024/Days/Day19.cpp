#include "../general.h"
#include <map>

size_t countSolutions(vector<string>& patterns, map<string, size_t>& solutions, string request)
{
	if (request.size() == 0)
		return 0;

	if (solutions.contains(request))
		return solutions[request];

	for (auto& patt : patterns)
	{
		if (request == patt)
		{
			solutions[request]++;
		}
		else if (request.starts_with(patt))
		{
			solutions[request] += countSolutions(patterns, solutions, request.substr(patt.size()));
		}
	}

	return solutions[request];
}

void Day19(stringstream& input)
{
	vector<string> patterns;
	vector<string> requests;
	bool readPatterns = true;
	while (!input.eof())
	{
		string stuff;
		input >> stuff;
		if (readPatterns)
		{
			if (!stuff.ends_with(','))
			{
				readPatterns = false;
			}
			else
				stuff.erase(stuff.size() - 1);
			patterns.push_back(stuff);
		}
		else
		{
			requests.push_back(stuff);
		}
	}

	int validP1 = 0;
	size_t combinationsP2 = 0;

	for (auto req : requests)
	{
		map<string, size_t> seen;
		size_t solutions = countSolutions(patterns, seen, req);
		if (solutions > 0)
			validP1++;
		combinationsP2 += solutions;
	}

	cout << "Part 1 result is: " << validP1 << endl;
	cout << "Part 2 result is: " << combinationsP2 << endl << endl;

	return;
}