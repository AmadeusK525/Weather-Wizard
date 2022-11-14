#include "EndGameRenderer.h"

#include <numeric>

namespace ww
{
	EndGameRenderer::EndGameRenderer(const std::vector<Collectable*>& collectables) :
		m_nCollectableScore(std::reduce(
			collectables.begin(),
			collectables.end(),
			0,
			[](const int sum, const Collectable* col) { return sum + col->GetPoints(); }
		))
	{
	}

	void EndGameRenderer::Render(olc::PixelGameEngine* engine, float fElapsedTime)
	{
		// Cover entire background with a transparent white pass
		engine->SetPixelMode(olc::Pixel::ALPHA);
		engine->FillRect({ 0, 0 }, { engine->ScreenWidth(), engine->ScreenHeight() }, { 255, 255, 255, 140 });
		engine->SetPixelMode(olc::Pixel::NORMAL);

		engine->DrawString({ 10, 10 }, "CONGRATULATIONS!", olc::DARK_GREEN, 2U);
		engine->DrawString({ 10, 30 }, "Final score: " + std::to_string(m_nCollectableScore), olc::BLACK);
		engine->DrawString({ 10, 50 }, "Press Space Bar to restart", olc::VERY_DARK_MAGENTA);
	}
}