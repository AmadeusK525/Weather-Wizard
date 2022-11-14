#ifndef ENDGAMERENDERER_H_
#define ENDGAMERENDERER_H_

#pragma once

#include "Renderer.h"
#include "Collectable.h"

namespace ww
{
	class EndGameRenderer : public Renderer
	{
	private:
		const int m_nCollectableScore;
		//const std::vector<Collectable*> m_vCollectables;

	public:
		EndGameRenderer(const std::vector<Collectable*>& collectables);

		virtual void Render(olc::PixelGameEngine* engine, float fElapsedTime);
	};
}

#endif // ENDGAMERENDERER_H_