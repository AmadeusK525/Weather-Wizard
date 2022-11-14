#include "EndGameControl.h"

namespace ww
{
	namespace endgame_control
	{
		EndGameControlPayload ProcessInput(const olc::PixelGameEngine* engine, float fElapsedTime)
		{
			bool bShouldRestart = engine->GetKey(olc::Key::SPACE).bReleased;
			return EndGameControlPayload(bShouldRestart);
		}
	}
}