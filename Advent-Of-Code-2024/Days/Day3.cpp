#include "../general.h"
#include <regex>

int Day3_Part1(stringstream& input)
{
	string memory = input.str();

	int sum = 0;

	std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");

	auto muls_begin = std::sregex_iterator(memory.begin(), memory.end(), pattern);
	auto muls_end = std::sregex_iterator();
	for (std::sregex_iterator i = muls_begin; i != muls_end; i++)
	{
		std::smatch match = *i;
		sum += stoi(match[1]) * stoi(match[2]);
	}

	return sum;
}

int Day3_Part2(stringstream& input)
{
	string memory = input.str();

	memory = "do()" + memory + "don't()";

	int sum = 0;

	std::regex sectionPattern("do\\(\\)([\\s\\S]*?)don't\\(\\)");
	std::regex mulPattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");

	auto section_begin = std::sregex_iterator(memory.begin(), memory.end(), sectionPattern);

	for (auto section = section_begin; section != sregex_iterator(); section++)
	{
		smatch matchSection = *section;
		string searchMuls = matchSection[1].str();

		auto muls_begin = std::sregex_iterator(searchMuls.begin(), searchMuls.end(), mulPattern);

		for (auto mul = muls_begin; mul != sregex_iterator(); mul++)
		{
			std::smatch matchMul = *mul;
			sum += stoi(matchMul[1]) * stoi(matchMul[2]);
		}
	}

	return sum;
}


void Day3(stringstream& input)
{
	cout << "Part 1 result is: " << Day3_Part1(input) << endl;
	input.seekg(0);
	cout << "Part 2 result is: " << Day3_Part2(input) << endl << endl;

	return;
}