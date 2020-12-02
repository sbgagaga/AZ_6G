#include "Apply.h"

int main()
{
	SystemClockInit();
	GPIOInit();
	UARTInit();
	TimerInit();
	for(;;)
	{
		Apply();
	}
}























