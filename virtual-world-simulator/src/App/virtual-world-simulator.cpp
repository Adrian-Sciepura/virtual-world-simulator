#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "SimulationManager.h"

void program()
{
	srand(time(NULL));
	SimulationManager simulationManager;
	simulationManager.start();
}

int main()
{
	program();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}