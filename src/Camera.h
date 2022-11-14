#ifndef CAMERA_H_
#define CAMERA_H_

#pragma once

#include "olcPixelGameEngine.h"

namespace ww
{
	struct Camera
	{
		olc::vf2d pos;
		const olc::vi2d blockSize;

		Camera(const olc::vf2d& startPos, const olc::vi2d blockSize) : pos(startPos), blockSize(blockSize) {}
	};
}

#endif // CAMERA_H_