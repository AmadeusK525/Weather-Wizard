#define OLC_PGE_APPLICATION
#include "WeatherWizard.h"

int main()
{
	ww::WeatherWizard weatherWizard;

	if ( weatherWizard.Construct(320, 240, 2, 2) )
		weatherWizard.Start();

	return 0;
}
	