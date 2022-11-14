#ifndef RENDERER_H_
#define RENDERER_H_

#pragma once

#include "olcPixelGameEngine.h"

namespace ww
{
	class Renderer
	{
	protected:
		bool bIsEnabled = true;

	public:
		virtual ~Renderer() {}

		bool IsEnabled() { return bIsEnabled; }
		virtual void Render(olc::PixelGameEngine* engine, float fElapsedTime) = 0;
	};
}

#endif // RENDERER_H_