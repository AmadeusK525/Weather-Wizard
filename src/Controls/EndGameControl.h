#ifndef ENDGAMECONTROL_H_
#define ENDGAMECONTROL_H_

#pragma once

#include "EndGameControlPayload.h"
#include "olcPixelGameEngine.h"

namespace ww
{
	namespace endgame_control
	{
		EndGameControlPayload ProcessInput(const olc::PixelGameEngine* engine, float fElapsedTime);
	}
}

#endif // ENDGAMECONTROL_H_