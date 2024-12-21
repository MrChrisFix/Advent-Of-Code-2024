#include "../general.h"
#include <map>

map<char, map<char, string>> createKeypadRoutes(const vector<string> keypad)
{
	map<char, map<char, string>> routed;

	for (int sy = 0; sy < keypad.size(); sy++)
	{
		for (int sx = 0; sx < keypad[0].size(); sx++)
		{
			if (keypad[sy][sx] == '#')
				continue;
			for (int y = 0; y < keypad.size(); y++)
			{
				for (int x = 0; x < keypad[0].size(); x++)
				{
					if (sy == y && sx == x)
						continue;
					if (keypad[y][x] == '#')
						continue;

					int dy = y - sy;
					int dx = x - sx;

					string output;

					if (dx < 0) //go left
					{
						if (keypad[sy][sx + dx] != '#')
						{
							for (int i = 0; i < abs(dx); i++)
							{
								output += "<";
							}
							for (int i = 0; i < abs(dy); i++)
							{
								if (dy > 0)
									output += "V";
								else
									output += "^";
							}
						}
						else
						{
							for (int i = 0; i < abs(dy); i++)
							{
								if (dy > 0)
									output += "V";
								else
									output += "^";
							}
							for (int i = 0; i < abs(dx); i++)
							{
								output += "<";
							}
						}
					}
					else if (dy > 0) //go down
					{
						if (keypad[sy + dy][sx] != '#')
						{
							for (int i = 0; i < abs(dy); i++)
							{
								output += "V";
							}
							for (int i = 0; i < abs(dx); i++)
							{
								output += ">";
							}
						}
						else
						{
							for (int i = 0; i < abs(dx); i++)
							{
								output += ">";
							}
							for (int i = 0; i < abs(dy); i++)
							{
								output += "V";
							}
						}
					}
					else
					{
						for (int i = 0; i < abs(dx); i++)
						{
							if (dx > 0)
								output += ">";
							else
								output += "<";
						}
						for (int i = 0; i < abs(dy); i++)
						{
							if (dy > 0)
								output += "V";
							else
								output += "^";
						}
					}

					routed[keypad[sy][sx]][keypad[y][x]] = output;
				}
			}
		}
	}
	return routed;
}

void createNumpads(map<char, map<char, string>>& numeric, map<char, map<char, string>>& directional)
{
	const vector<string> numberKeypad = { "789", "456","123","#0A" };
	const vector<string> dirKeypad = { "#^A", "<V>" };

	numeric = createKeypadRoutes(numberKeypad);
	directional = createKeypadRoutes(dirKeypad);
}


string execute(map<char, map<char, string>>& keyPad, const string code)
{
	string out;
	char prev = 'A';
	for (auto& c : code)
	{
		out += keyPad[prev][c] + "A";
		prev = c;
	}
	return out;
}


size_t Day21_Part1(stringstream& input)
{
	vector<string> codes;
	while (!input.eof())
	{
		string code;
		input >> code;
		codes.push_back(code);
	}
	map<char, map<char, string>> numericPad, directionalPad;

	createNumpads(numericPad, directionalPad);
	size_t result = 0;

	for (auto& code : codes)
	{
		int value = stoi(code.substr(0, 3));

		string out = execute(numericPad, code);
		for (int i = 0; i < 2; i++)
		{
			out = execute(directionalPad, out);
		}

		result += value * out.size();
	}

	return result;
}

size_t Day21_Part2(stringstream& input)
{
	vector<string> codes;
	while (!input.eof())
	{
		string code;
		input >> code;
		codes.push_back(code);
	}
	map<char, map<char, string>> numericPad, directionalPad;

	createNumpads(numericPad, directionalPad);
	size_t result = 0;

	map<string, string> memory;

	for (auto& code : codes)
	{
		int value = stoi(code.substr(0, 3));

		string out = execute(numericPad, code);

		map<string, size_t> substringCount;

		size_t found_pos;
		size_t offset = 0;
		while ((found_pos = out.find_first_of('A', offset)) != string::npos)
		{
			string sub = out.substr(offset, found_pos - offset + 1);
			substringCount[sub]++;
			offset = found_pos + 1;
		}

		for (int i = 0; i < 25; i++)
		{
			map<string, size_t> nextCount;

			for (auto substring : substringCount)
			{
				if (!memory.contains(substring.first))
				{
					memory[substring.first] = execute(directionalPad, substring.first);
				}

				string res = memory[substring.first];
				offset = 0;
				while ((found_pos = res.find_first_of('A', offset)) != string::npos)
				{
					string sub = res.substr(offset, found_pos - offset + 1);
					nextCount[sub] += substring.second;
					offset = found_pos + 1;
				}

			}

			substringCount = nextCount;
		}

		size_t subresult = 0;

		for (auto sub : substringCount)
			subresult += sub.first.size() * sub.second;
		result += subresult * value;
	}

	return result;
}


void Day21(stringstream& input)
{
	cout << "Part 1 result is: " << Day21_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day21_Part2(input) << endl << endl;

	return;
}