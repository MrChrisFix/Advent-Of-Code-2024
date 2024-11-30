#pragma once
#include "general.h"

class DaysExecutor
{
private:
	bool useTestVal;
	bool doAll;
	int day;

public:
	static StartParams getParamsFromUser();

	DaysExecutor(StartParams params);

	void execute();

private:
	stringstream readInput(int dayNumber);
	void doDay(int dayNumber);
};

