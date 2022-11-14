#ifndef SKYCOLOR_H_
#define SKYCOLOR_H_

#pragma once

#include "olcPixelGameEngine.h"

namespace ww
{
	struct SkyColor
	{
		olc::Pixel topColor;
		olc::Pixel bottomColor;

		SkyColor(olc::Pixel topColor, olc::Pixel bottomColor): topColor(topColor), bottomColor(bottomColor) {}
	};
}

#endif // SKYCOLOR_H_