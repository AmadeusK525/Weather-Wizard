#ifndef MAPRENDERER_H_
#define MAPRENDERER_H_

#pragma once

#include "Camera.h"
#include "Map.h"
#include "olcPixelGameEngine.h"
#include "Renderer.h"
#include "Season.h"

namespace ww
{
	class MapRenderer : public Renderer
	{
	private:
		const Map* map;
		const Camera* camera;
		const Season* activeSeason;

		float m_fPortalTimer = 0.0f;
		olc::vi2d m_portalSpritePosCounter = { 0, 0 };
		bool m_bUpdatePortalSpritePosCounterY = false;

	public:
		MapRenderer(const Map* map, const Camera* camera, const Season* activeSeason);

		void Render(olc::PixelGameEngine* engine, float fElapsedTime);
		void RenderBlock(
			olc::PixelGameEngine* engine,
			float fElapsedTime,
			MapBlock block,
			const Season* activeSeason,
			const olc::vi2d& pos,
			const olc::vi2d& size
		);

	private:
		olc::vi2d GetSpritePosFromBlock(MapBlock);
		olc::Sprite* GetSpriteForBlockAndUpdateElapsedTime(MapBlock block, float fElapsedTime);
	};
}

#endif // MAPRENDRERER_H_