#include "WandBarRenderer.h"

namespace ww
{
	void WandBarRenderer::Render(olc::PixelGameEngine* engine, float fElapsedTime)
	{
		const int nSpacing = 2;
		const std::vector<SeasonWand>& wands = wandBar->GetWands();

		olc::vi2d wandBarSize = { nSpacing * (int(wands.size()) - 1), 0 };
		for ( const SeasonWand& wand : wands )
			wandBarSize += { wand.icon->width, std::max(0, (wand.icon->height + nSpacing) - wandBarSize.y) };

		const olc::vi2d wandBarDrawPos = { (engine->ScreenWidth() - wandBarSize.x) / 2, engine->ScreenHeight() - wandBarSize.y };
		int nOffsetX = 0;

		engine->SetPixelMode(olc::Pixel::ALPHA);
		engine->FillRect(wandBarDrawPos, wandBarSize, { 0, 0, 0, 120 });
		engine->SetPixelMode(olc::Pixel::NORMAL);

		for ( int i = 0; i < wands.size(); i++ )
		{
			olc::Sprite* icon = wands[i].icon;
			olc::vi2d pos = { wandBarDrawPos.x + nOffsetX, wandBarDrawPos.y };

			engine->SetPixelMode(olc::Pixel::ALPHA);
			engine->DrawSprite(pos, icon);
			engine->SetPixelMode(olc::Pixel::NORMAL);

			nOffsetX += icon->width + nSpacing;

			if ( wandBar->GetCurrentWandIndex() == i )
			{
				engine->DrawRect(pos, { icon->width, icon->height });
				engine->DrawString({ pos.x, pos.y - 10 }, wands[i].season.name);
			}
		}
	}
}