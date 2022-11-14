#include "MapRenderer.h"

#include "AssetManager.h"

namespace ww
{
	MapRenderer::MapRenderer(const Map* map, const Camera* camera, const Season* activeSeason) 
		: map(map), camera(camera), activeSeason(activeSeason) 
	{
	}

	void MapRenderer::Render(olc::PixelGameEngine* engine, float fElapsedTime)
	{
		engine->SetPixelMode(olc::Pixel::ALPHA);
		for ( int x = int(camera->pos.x); x < map->m_nWidth; x++ )
		{
			for ( int y = int(camera->pos.y); y < map->m_nHeight; y++ )
			{
				if ( y < 0 || x < 0 )
					continue;

				olc::vf2d pos = { float(x), float(y) };
				olc::vf2d drawPos = (pos - camera->pos) * camera->blockSize;
				olc::vi2d sanitizedPos = { (int)drawPos.x, (int)drawPos.y };
				MapBlock block = map->GetBlockAt(x, y);
				RenderBlock(engine, fElapsedTime, block, activeSeason, sanitizedPos, camera->blockSize);
			}
		}
		engine->SetPixelMode(olc::Pixel::NORMAL);

		engine->DrawString({ engine->ScreenWidth() - 55, 5 }, activeSeason->name);
	}

	void MapRenderer::RenderBlock(
		olc::PixelGameEngine* engine,
		float fElapsedTime,
		MapBlock block,
		const Season* activeSeason,
		const olc::vi2d& pos,
		const olc::vi2d& size
	)
	{
		if ( block == MapBlock::AIR )
			return;

		switch ( block )
		{
		case MapBlock::AIR:
			return;
		case MapBlock::BOOK:
		{
			olc::Sprite* pSprite = AssetManager::LoadSprite(Asset::BOOK);
			engine->DrawSprite(pos, pSprite);
			break;
		}
		case MapBlock::FINISH:
		{
			olc::Sprite* pSpriteSheet = AssetManager::LoadSprite(Asset::SPRITESHEET_PORTAL);

			// Ugly code, same as WizardRenderer, needs to be refactored to avoid copying
			m_fPortalTimer += fElapsedTime;
			if ( m_fPortalTimer >= 0.4f )
			{
				m_fPortalTimer = 0.0f;
				m_portalSpritePosCounter.x++;
				m_portalSpritePosCounter.x %= 4;

				if ( m_bUpdatePortalSpritePosCounterY )
				{
					m_portalSpritePosCounter.y++;
					m_portalSpritePosCounter.y %= 2;
					m_bUpdatePortalSpritePosCounterY = false;
				}

				if ( m_portalSpritePosCounter.x == 3 )
					m_bUpdatePortalSpritePosCounterY = true;
			}

			engine->DrawPartialSprite(pos, pSpriteSheet, m_portalSpritePosCounter * 16, { 16, 16 });
			break;
		}
		default:
		{
			olc::Sprite* pSpriteSheet = AssetManager::LoadSprite(Asset::SPRITESHEET_BLOCKS);
			const olc::vi2d posInSprite = GetSpritePosFromBlock(block);;
			const olc::vi2d spriteSize = { 16, 16 };

			engine->DrawPartialSprite(pos, pSpriteSheet, posInSprite * spriteSize, spriteSize);
		}
		}

	}

	olc::vi2d MapRenderer::GetSpritePosFromBlock(MapBlock block)
	{
		switch ( block )
		{
		case MapBlock::BRICK: return { 2, 1 };
		case MapBlock::ICE_WATER: return { activeSeason->temperatureCelsius < 0.0f ? 1 : 0, 0 };
		case MapBlock::FIRE: return { activeSeason->temperatureCelsius >= 30.0f ? 3 : 2, 0 };
		case MapBlock::FLOWER_TANGLE: return { activeSeason->flowerGrowthPercent >= 0.50f ? 0 : 1, 1 };
		case MapBlock::WIND_DOWN: return { 3, activeSeason->windSpeed >= 30.0f ? 3 : 2 };
		case MapBlock::WIND_LEFT: return { 2, activeSeason->windSpeed >= 30.0f ? 3 : 2 };
		case MapBlock::WIND_RIGHT: return { 0, activeSeason->windSpeed >= 30.0f ? 3 : 2 };
		case MapBlock::WIND_UP: return { 1, activeSeason->windSpeed >= 30.0f ? 3 : 2 };
		default: return { 1, 2 };
		}
	}

	olc::Sprite* MapRenderer::GetSpriteForBlockAndUpdateElapsedTime(MapBlock block, float fElapsedTime)
	{
		olc::Sprite* pSprite = nullptr;
		return pSprite;
		//switch ( block )
		//{
		//case MapBlock::AIR: return nullptr;
		//case MapBlock::BRICK:
		//	pSprite
		//}
	}
}