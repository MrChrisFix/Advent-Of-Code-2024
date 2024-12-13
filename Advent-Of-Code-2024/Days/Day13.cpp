#include "../general.h"

int Day13_Part1(stringstream& input)
{
	int tokens = 0;

	while (!input.eof())
	{
		string strash;
		int num[6];
		char ctrash;
		input >> strash >> strash >> ctrash >> num[0] >> ctrash >> ctrash >> num[1];
		input >> strash >> strash >> ctrash >> num[2] >> ctrash >> ctrash >> num[3];
		input >> strash >> ctrash >> ctrash >> num[4] >> ctrash >> ctrash >> ctrash >> num[5];

		float Af = (num[2] * num[5] - num[3] * num[4]*1.0f) / (-num[3] * num[0]*1.0f + num[2] * num[1]);
		if (round(Af) != Af)
		{
			continue;
		}
		int A = round(Af);
		float Bf = (-num[0] * A + num[4]) / num[2];
		if (round(Bf) != Bf)
			continue;
		int B = round(Bf);
		tokens += 3 * A + B;
	}

	return tokens;
}

size_t Day13_Part2(stringstream& input)
{
	size_t tokens = 0;

	while (!input.eof())
	{
		string strash;
		long long num[6];
		char ctrash;
		input >> strash >> strash >> ctrash >> num[0] >> ctrash >> ctrash >> num[1];
		input >> strash >> strash >> ctrash >> num[2] >> ctrash >> ctrash >> num[3];
		input >> strash >> ctrash >> ctrash >> num[4] >> ctrash >> ctrash >> ctrash >> num[5];

		num[4] += 10000000000000;
		num[5] += 10000000000000;

		long double Af = (num[2] * num[5] - num[3] * num[4] * 1.0) / (-num[3] * num[0]*1.0 + num[2] * num[1]);
		if (round(Af) != Af)
		{
			continue;
		}
		size_t A = round(Af);
		long double Bf = (-num[0]*1.0 * A + num[4]) / num[2];
		if (round(Bf) != Bf)
			continue;
		size_t B = round(Bf);
		tokens += 3 * A + B;
	}

	return tokens;
}


void Day13(stringstream& input)
{
	cout << "Part 1 result is: " << Day13_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day13_Part2(input) << endl << endl;

	return;
}