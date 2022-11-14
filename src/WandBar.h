#ifndef WANDBAR_H_
#define WANDBAR_H_

#pragma once

#include "SeasonWand.h"

namespace ww
{
	struct WandBar
	{
	private:
		int nCurrentWandIndex = 0;
		std::vector<SeasonWand> wands;

	public:
		WandBar(std::vector<SeasonWand> wands): wands(wands) {}

		void IncreaseWandSelection();
		void DecreaseWandSelection();

		inline const std::vector<SeasonWand>& GetWands() const { return wands; }
		inline int GetCurrentWandIndex() const { return nCurrentWandIndex; }
		inline SeasonWand GetCurrentWand() const { return wands[nCurrentWandIndex]; }
	};
}

#endif // WANDBAR_H_