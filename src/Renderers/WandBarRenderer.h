#ifndef WANDBARRENDERER_H_
#define WANDBARRENDERER_H_

#include "Renderer.h"
#include "WandBar.h"

namespace ww
{
	class WandBarRenderer : public Renderer
	{
	private:
		const WandBar* wandBar;

	public:
		WandBarRenderer(const WandBar* wandBar) : wandBar(wandBar) {}

		void Render(olc::PixelGameEngine* engine, float fElapsedTime);
	};
}

#endif // WANDBARRENDERER_H_