#include "WandBar.h"

namespace ww
{
	void WandBar::IncreaseWandSelection()
	{
		if ( nCurrentWandIndex >= (wands.size() - 1) )
			nCurrentWandIndex = 0;
		else
			nCurrentWandIndex++;
	}

	void WandBar::DecreaseWandSelection()
	{
		if ( nCurrentWandIndex <= 0 )
			nCurrentWandIndex = int(wands.size() - 1);
		else
			nCurrentWandIndex--;
	}
}