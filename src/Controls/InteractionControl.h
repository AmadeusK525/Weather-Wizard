#ifndef INTERACTIONCONTROL_H_
#define INTERACTIONCONTROL_H_

#pragma once

#include "Map.h"
#include "olcPixelGameEngine.h"
#include "Season.h"
#include "WandBar.h"
#include "Wizard.h"

namespace ww
{
	namespace interaction_control
	{
		void ProcessInputAndUpdateSeasonAndWandBarInMap(
			const Wizard* wizard,
			Season* season, 
			WandBar* wandBar, 
			const Map* map,
			const olc::PixelGameEngine* engine,
			float fElapsedTime
		);
		bool CanWizardChangeToSeasonInMap(const Wizard* wizard, const Season& season, const Map* map);
	}
}

#endif // INTERACTIONCONTROL_H_