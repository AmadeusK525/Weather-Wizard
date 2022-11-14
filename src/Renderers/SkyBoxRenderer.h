#ifndef SKYBOXRENDERER_H_
#define SKYBOXRENDERER_H_

#pragma once

#include "Camera.h"
#include "Renderer.h"
#include "Season.h"

namespace ww
{
	class SkyBoxRenderer : public Renderer
	{
	private:
		const Camera* m_pCamera;
		const Season* m_pActiveSeason;
		//const SkyColor* skyColor;

	public:
		SkyBoxRenderer(const Camera* camera, const Season* activeSeason): m_pCamera(camera), m_pActiveSeason(activeSeason) {}

		void Render(olc::PixelGameEngine* engine, float fElapsedTime);
		void RenderVerticalGradient(
			olc::PixelGameEngine* engine,
			float fElapsedTime,
			olc::Pixel topColor,
			olc::Pixel bottomColor,
			const olc::vi2d& pos,
			const olc::vi2d& size
		);

		static olc::Pixel GetColorMix(olc::Pixel col1, olc::Pixel col2, float percentage);
	};
}


#endif // SKYBOXRENDRER_H_