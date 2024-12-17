#include "../general.h"
#include <map>

struct instruction
{
	int opcode;
	int operand;
};

string runProgram(const vector<instruction> program, map<size_t, size_t> combo)
{
	string out;

	int i = -1;
	while (++i < program.size())
	{
		int operand = program[i].operand;

		switch (program[i].opcode)
		{
		case 0:		//adv
			combo[4] /= pow(2, combo[operand]);
			break;
		case 1:		//bxl
			combo[5] = combo[5] ^ operand;
			break;
		case 2:		//bst
			combo[5] = combo[operand] % 8;
			break;
		case 3:		//jnz
			if (combo[4] != 0)
			{
				i = operand - 1;
			}
			break;
		case 4:		//bxc
			combo[5] = combo[5] ^ combo[6];
			break;
		case 5:		//out
			out += to_string(combo[operand] % 8) + ",";
			break;
		case 6:		//bdv
			combo[5] = combo[4] / pow(2, combo[operand]);
			break;
		case 7:		//cdv
			combo[6] = combo[4] / pow(2, combo[operand]);
			break;
		default:
			break;
		}
	}

	return out;
}

string Day17_Part1(stringstream& input)
{
	int A, B, C;
	string s;
	input >> s >> s >> A;
	input >> s >> s >> B;
	input >> s >> s >> C;
	input >> s >> s;
	stringstream codes(s);
	char c;

	vector<instruction> program;
	while (!codes.eof())
	{
		int num1, num2;
		codes >> num1 >> c >> num2 >> c;
		program.push_back({ num1, num2 });
	}
	map<size_t, size_t> combo;
	combo[1] = 1, combo[2] = 2, combo[3] = 3;
	combo[4] = A;
	combo[5] = B;
	combo[6] = C;

	string out = runProgram(program, combo);
	out.erase(out.size() - 1);

	return out;
}


size_t DFS(int i, const string& original, size_t from, const vector<instruction>& program)
{
	if (i == original.size() / 2 + 1)
		return from;
	string search = original.substr(original.size() - 1 - i * 2);
	from = from * 8;
	string out;
	int cnt = 0;
	do
	{
		map<size_t, size_t> combo;
		combo[1] = 1, combo[2] = 2, combo[3] = 3;
		combo[4] = from++;
		combo[5] = 0;
		combo[6] = 0;

		out = runProgram(program, combo);
		out.erase(out.size() - 1);

		if (out == search)
		{
			size_t val = DFS(i + 1, original, from-1, program);
			if (val != 0)
				return val;
		}

	} while (++cnt < 8);

	return 0;
}

size_t Day17_Part2(stringstream& input)
{
	long long A, B, C;
	string s;
	getline(input, s); getline(input, s); getline(input, s);
	string original;
	input >> s >> original;

	stringstream codes(original);
	char c;
	vector<instruction> program;
	while (!codes.eof())
	{
		int num1, num2;
		codes >> num1 >> c >> num2 >> c;
		program.push_back({ num1, num2 });
	}

	size_t result = DFS(0, original, 0,program);
	return result;
}


void Day17(stringstream& input)
{
	cout << "Part 1 result is: " << Day17_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day17_Part2(input) << endl << endl;

	return;
}