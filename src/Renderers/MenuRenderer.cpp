#include "MenuRenderer.h"

namespace ww
{
	void MenuRenderer::Render(olc::PixelGameEngine* engine, float fElapsedTime)
	{
		// Cover entire background with a transparent black pass
		engine->SetPixelMode(olc::Pixel::ALPHA);
		engine->FillRect({ 0, 0 }, { engine->ScreenWidth(), engine->ScreenHeight() }, { 0, 0, 0, 140 });
		engine->SetPixelMode(olc::Pixel::NORMAL);

		engine->DrawString(
			{ 10, 10 },
			"Controls:\n\nA - WALK LEFT\nD - WALK RIGHT\nW - CLIMB FLOWERS (IF POSSIBLE)\nLEFT/RIGHT - CHANGE WAND SELECTION\n"
			"SPACEBAR - JUMP\nENTER - CHANGE SEASON TO CURRENT WAND\nESC - EXIT MENU",
			olc::WHITE
		);
	}
}