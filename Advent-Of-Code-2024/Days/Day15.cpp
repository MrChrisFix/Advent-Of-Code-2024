#include "../general.h"
#include <map>

struct vec2
{
	int y;
	int x;

	vec2 operator+(const vec2& rhs) const
	{
		return { this->y + rhs.y, this->x + rhs.x };
	}

	bool operator==(const vec2& rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y;
	}
};

int calculatePoints(const vector<string>& warehouse, char box)
{
	int points = 0;
	for (int y = 0; y < warehouse.size(); y++)
	{
		for (int x = 0; x < warehouse[y].size(); x++)
		{
			if (warehouse[y][x] != box)
				continue;
			points += 100 * y + x;
		}
	}
	return points;
}

int Day15_Part1(stringstream& input)
{
	vector<string> warehouse;
	bool readMap = true;
	string instructions;
	vec2 pos{ 1,1 };
	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.empty())
		{
			if (readMap)
			{
				readMap = false;
				continue;
			}
			break;
		}

		if (readMap)
		{
			int x = line.find('@');
			if (x != string::npos)
				pos = { int(warehouse.size()), x };
			warehouse.push_back(line);
		}
		else
		{
			instructions += line;
		}
	}

	map<char, vec2> dir = { {'v',{1,0}},{'<',{0,-1}},{'^',{-1,0}},{'>',{0,1}} };

	for (char ins : instructions)
	{
		vec2 d = dir[ins];

		vec2 looked = pos + d;

		if (warehouse[looked.y][looked.x] == '.')
		{
			warehouse[looked.y][looked.x] = '@';
			warehouse[pos.y][pos.x] = '.';
			pos = looked;
		}
		else if (warehouse[looked.y][looked.x] == '#')
			continue;
		else if (warehouse[looked.y][looked.x] == 'O')
		{
			while (warehouse[looked.y][looked.x] == 'O')
				looked = looked + d;
			if (warehouse[looked.y][looked.x] == '#')
			{//cannot move
				continue;
			}
			warehouse[looked.y][looked.x] = 'O';
			looked = pos + d;
			warehouse[looked.y][looked.x] = '@';
			warehouse[pos.y][pos.x] = '.';
			pos = pos + d;
		}
	}

	int points = calculatePoints(warehouse, 'O');

	return points;
}


bool canMove(const vector<string>& warehouse, vec2 who, const vec2& dir, const bool& horizontal)
{
	
	if (horizontal)
	{
		vec2 next = who + dir;
		while (warehouse[next.y][next.x] == '[' || warehouse[next.y][next.x] == ']')
			next = next + dir;
		if (warehouse[next.y][next.x] == '#')
			return false;
	}
	else
	{
		int n = 1;

		if (warehouse[who.y][who.x] == ']')
			n = -1;

		vec2 next = who + dir;
		if (warehouse[next.y][next.x] == '#' || warehouse[next.y][next.x + n] == '#')
			return false;

		if (warehouse[next.y][next.x] == '[' || warehouse[next.y][next.x] == ']')
		{
			if (!canMove(warehouse, next, dir, horizontal))
				return false;
		}

		if (warehouse[next.y][next.x + n] == '[' || warehouse[next.y][next.x + n] == ']')
		{
			vec2 tmp = next;
			tmp.x += n;
			if (!canMove(warehouse, tmp, dir, horizontal))
				return false;
		}
	}

	return true;
}

void moveBoxes(vector<string>& warehouse, vec2 who, const vec2& dir, const bool& horizontal)
{

	if (horizontal)
	{
		vec2 next = who + dir;
		if (warehouse[next.y][next.x] != '.')
			moveBoxes(warehouse, next, dir, horizontal);
		warehouse[next.y][next.x] = warehouse[who.y][who.x];
	}
	else
	{
		int n = 1;

		if (warehouse[who.y][who.x] == ']')
			n = -1;

		vec2 next = who + dir;

		if (warehouse[next.y][next.x] != '.')
			moveBoxes(warehouse, next, dir, horizontal);

		if (warehouse[next.y][next.x + n] != '.')
		{
			vec2 tmp = next;
			tmp.x += n;
			moveBoxes(warehouse, tmp, dir, horizontal);
		}

		if (warehouse[who.y][who.x] == '[')
		{
			warehouse[next.y][next.x] = '[';
			warehouse[next.y][next.x + n] = ']';
		}
		else
		{
			warehouse[next.y][next.x] = ']';
			warehouse[next.y][next.x + n] = '[';
		}

		warehouse[who.y][who.x] = '.';
		warehouse[who.y][who.x + n] = '.';
	}
}

int Day15_Part2(stringstream& input)
{
	vector<string> warehouse;
	bool readMap = true;
	string instructions;
	vec2 pos{ 1,1 };
	while (!input.eof())
	{
		string line;
		getline(input, line);
		if (line.empty())
		{
			if (readMap)
			{
				readMap = false;
				continue;
			}
			break;
		}

		if (readMap)
		{
			string newLine;

			for (char c : line)
			{
				if (c == '@')
				{
					newLine += "@.";
				}
				else if (c == '#' || c == '.')
				{
					newLine += c;
					newLine += c;
				}
				else if (c == 'O')
				{
					newLine += "[]";
				}
			}
			warehouse.push_back(newLine);
		}
		else
		{
			instructions += line;
		}
	}

	for (int y = 0; y < warehouse.size(); y++)
	{
		int x = warehouse[y].find('@');
		if (x != string::npos)
		{
			pos = { y, x };
			break;
		}
	}

	map<char, vec2> dir = { {'v',{1,0}},{'<',{0,-1}},{'^',{-1,0}},{'>',{0,1}} };

	for (char ins : instructions)
	{
		vec2 d = dir[ins];

		vec2 looked = pos + d;

		char lookedAt = warehouse[looked.y][looked.x];

		if (lookedAt == '.')
		{
			warehouse[looked.y][looked.x] = '@';
			warehouse[pos.y][pos.x] = '.';
			pos = looked;
		}
		else if (lookedAt == '#')
			continue;
		else if (lookedAt == '[' || lookedAt == ']')
		{
			bool hor = ins == '<' || ins == '>';

			if (!canMove(warehouse, looked, d, hor))
				continue;

			moveBoxes(warehouse, looked, d, hor);
			warehouse[looked.y][looked.x] = '@';
			warehouse[pos.y][pos.x] = '.';
			pos = pos + d;
		}
	}

	int points = calculatePoints(warehouse, '[');

	return points;
}


void Day15(stringstream& input)
{
	cout << "Part 1 result is: " << Day15_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day15_Part2(input) << endl << endl;

	return;
}