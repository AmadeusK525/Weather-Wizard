#ifndef MAPBLOCKREF_H_
#define MAPBLOCKREF_H_

#pragma once

#include "MapBlock.h"
#include "olcPixelGameEngine.h"

namespace ww
{
	struct MapBlockRef
	{
		MapBlock block;
		olc::vi2d coordinate;

		MapBlockRef(MapBlock block, const olc::vi2d& coordinate) : block(block), coordinate(coordinate) {}

		inline bool operator<(const MapBlockRef& rhs) const { return this->coordinate < rhs.coordinate; }
		inline bool operator==(const MapBlockRef& rhs) const { return this->coordinate == rhs.coordinate; }
	};
}

#endif // MAPBLOCKREF_H_