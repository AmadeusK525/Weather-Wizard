#ifndef WIZARDRENDERER_H_
#define WIZARDRENDERER_H_

#pragma once

#include "Camera.h"
#include "Renderer.h"
#include "Wizard.h"

namespace ww
{
	class WizardRenderer : public Renderer
	{
	private:
		const Wizard* m_pWizard;
		const Camera* m_pCamera;

		float m_fTimer = 0.0f;
		olc::vi2d m_spritePosCounter = { 0, 0 };
		bool m_bUpdateSpritePosCounterY = false;

	public:
		WizardRenderer(const Wizard* wizard, const Camera* camera) : m_pWizard(wizard), m_pCamera(camera) {}

		void Render(olc::PixelGameEngine* engine, float fElapsedTime);

	private:
		olc::Sprite* GetSpriteForWizard(const Wizard* wizard);
		olc::vi2d GetPosInSpriteAndUpdateTimer(float fElapsedTime);
	};
}

#endif // WIZARDRENDERER_H_