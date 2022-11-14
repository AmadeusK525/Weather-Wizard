#include "WizardRenderer.h"

#include "AssetManager.h"

namespace ww
{
	void WizardRenderer::Render(olc::PixelGameEngine* engine, float fElapsedTime)
	{
		olc::vi2d playerSize = { 
			(int)std::round(float(m_pCamera->blockSize.x) * m_pWizard->sizeInUnits.x),
			(int)std::round(float(m_pCamera->blockSize.y) * m_pWizard->sizeInUnits.y)
		};
		olc::vf2d drawPos = (m_pWizard->pos - m_pCamera->pos) * m_pCamera->blockSize;
		olc::vi2d roundedDrawPos = { (int)drawPos.x, (int)drawPos.y };

		if ( roundedDrawPos.x > engine->ScreenWidth()
			|| roundedDrawPos.y > engine->ScreenHeight()
			|| roundedDrawPos.x + playerSize.x < 0
			|| roundedDrawPos.y + playerSize.y < 0 )
		{
			return;
		}

		olc::Sprite* pSpriteSheet = GetSpriteForWizard(m_pWizard);
		olc::vi2d posInSprite = GetPosInSpriteAndUpdateTimer(fElapsedTime);
		const olc::vi2d spriteSize = { 11, 16 };

		engine->SetPixelMode(olc::Pixel::ALPHA);
		engine->DrawPartialSprite(
			roundedDrawPos,
			pSpriteSheet,
			posInSprite *  spriteSize,
			{ 11, 16 });
		engine->SetPixelMode(olc::Pixel::NORMAL);
	}

	olc::Sprite* WizardRenderer::GetSpriteForWizard(const Wizard* wizard)
	{
		switch ( wizard->lastFaceDirection )
		{
		case FaceDirection::RIGHT: return AssetManager::LoadSprite(Asset::SPRITESHEET_WIZARD_RIGHT);
		case FaceDirection::LEFT: return AssetManager::LoadSprite(Asset::SPRITESHEET_WIZARD_LEFT);
		default: return nullptr;
		}
	}

	olc::vi2d WizardRenderer::GetPosInSpriteAndUpdateTimer(float fElapsedTime)
	{
		if ( m_pWizard->vel.x == 0.0f || !m_pWizard->bIsOnGround )
			return { 0, 0 };

		m_fTimer += fElapsedTime;
		if ( m_fTimer >= 0.4f / std::fabs(m_pWizard->vel.x) )
		{
			m_fTimer = 0.0f;
			m_spritePosCounter.x++;
			m_spritePosCounter.x %= 4;

			if ( m_bUpdateSpritePosCounterY )
			{
				m_spritePosCounter.y++;
				m_spritePosCounter.y %= 2;
				m_bUpdateSpritePosCounterY = false;
			}

			if ( m_spritePosCounter.x == 3 )
				m_bUpdateSpritePosCounterY = true;
		}

		return m_spritePosCounter;
	}
}