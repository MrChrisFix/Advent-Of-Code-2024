#include "general.h"
#include <iostream>
#include "DaysExecutor.h"


int main()
{
	try
	{
		StartParams params;
		
		params = DaysExecutor::getParamsFromUser();

		DaysExecutor exe(params);
		exe.execute();
	}
	catch (...)
	{
		cout << "Terminating program\n";
		return -1;
	}
	return 0;
}