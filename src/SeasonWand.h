#ifndef SEASONWAND_H_
#define SEASONWAND_H_

#pragma once

#include "olcPixelGameEngine.h"
#include "Season.h"

namespace ww
{
	struct SeasonWand
	{
		olc::Sprite* icon;
		Season season;

		SeasonWand(olc::Sprite* icon, Season season) : icon(icon), season(season) {}
	};
}

#endif // SEASONWAND_H_