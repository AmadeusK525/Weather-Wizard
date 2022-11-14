#ifndef MENURENDERER_H_
#define MENURENDERER_H_

#pragma once

#include "Renderer.h"

namespace ww
{
	class MenuRenderer : public Renderer
	{
	public:
		MenuRenderer() = default;

		void Render(olc::PixelGameEngine* engine, float fElapsedTime);
	};
}

#endif // MENURENDERER_H_