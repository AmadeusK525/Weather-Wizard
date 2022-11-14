#ifndef WIZARD_H_
#define WIZARD_H_

#pragma once

#include <set>

#include "FaceDirection.h"
#include "Map.h"
#include "MapBlockRef.h"
#include "olcPixelGameEngine.h"

namespace ww
{
	struct Wizard
	{
		const olc::vf2d sizeInUnits = { 0.6875f, 1.0f };

		olc::vf2d pos;
		olc::vf2d vel = { 0.0f, 0.0f };
		FaceDirection lastFaceDirection = FaceDirection::RIGHT;

		bool bIsOnGround = false;
		bool bIsInFlowerTangle = false;
		bool bIsInStrongWind = false;

		Wizard(const olc::vf2d& startPos = { 0.0f, 0.0f }, const olc::vf2d& startVel = { 0.0f, 0.0f }) :
			pos(startPos), vel(startVel) {}

		std::set<MapBlockRef> GetIntersectingBlockRefsInMap(const Map* map) const;
	};
}

#endif // WIZARD_H_