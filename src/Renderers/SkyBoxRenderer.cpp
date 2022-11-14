#include "SkyBoxRenderer.h"

namespace ww
{
	void SkyBoxRenderer::Render(olc::PixelGameEngine* engine, float fElapsedTime)
	{
		int nCameraDrawPosX = int((m_pCamera->pos.x * m_pCamera->blockSize.x) / 3);
		if ( nCameraDrawPosX == 0 )
		{
			engine->DrawSprite({ 0, 0 }, m_pActiveSeason->skySprite);
		}
		else
		{
			olc::vi2d firstDrawPos = { -(nCameraDrawPosX % m_pActiveSeason->skySprite->width), 0 };
			engine->DrawSprite(firstDrawPos, m_pActiveSeason->skySprite);
			engine->DrawSprite({ firstDrawPos.x + m_pActiveSeason->skySprite->width, 0 }, m_pActiveSeason->skySprite);
		}

		//engine->DrawSprite({ 0, 0 }, m_pActiveSeason->skySprite);
		//RenderVerticalGradient(
		//	engine,
		//	fElapsedTime,
		//	skyColor->topColor,
		//	skyColor->bottomColor,
		//	{ 0, 0 },
		//	{ engine->ScreenWidth(), engine->ScreenHeight() }
		//);
	}

	void SkyBoxRenderer::RenderVerticalGradient(
		olc::PixelGameEngine* engine,
		float fElapsedTime,
		olc::Pixel topColor,
		olc::Pixel bottomColor,
		const olc::vi2d& pos,
		const olc::vi2d& size
	)
	{
		for ( int i = 0; i < size.y; i++ )
		{
			float yPercentage = float(i) / size.y;
			engine->DrawLine(
				{ pos.x, pos.y + i },
				{ pos.x + size.x, pos.y + i },
				GetColorMix(topColor, bottomColor, yPercentage)
			);
		}
	}

	olc::Pixel SkyBoxRenderer::GetColorMix(olc::Pixel col1, olc::Pixel col2, float percentage)
	{
		uint8_t newRed = uint8_t((col2.r * percentage) + (col1.r * (1.0f - percentage)));
		uint8_t newGreen = uint8_t((col2.g * percentage) + (col1.g * (1.0f - percentage)));
		uint8_t newBlue = uint8_t((col2.b * percentage) + (col1.b * (1.0f - percentage)));
		uint8_t newAlpha = uint8_t((col2.a * percentage) + (col1.a * (1.0f - percentage)));

		return olc::Pixel(newRed, newGreen, newBlue, newAlpha);
	}
}