#include <UnitTestKit/tc_rand.h>
#include <time.h>

bool lsrand = false;
void checkRandomSeed()
{ 
	if(!lsrand)
	{
		srand(clock());
		lsrand = true;
	}
}