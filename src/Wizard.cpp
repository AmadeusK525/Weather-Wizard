#include "Wizard.h"

namespace ww
{
	std::set<MapBlockRef> Wizard::GetIntersectingBlockRefsInMap(const Map* map) const
	{
		float fSanitizedSizeX = sizeInUnits.x * 0.99f;
		float fSanitizedSizeY = sizeInUnits.y * 0.99f;

		olc::vi2d coordinates[] = {
			{ int(pos.x), int(pos.y) }, // Top Left
			{ int(pos.x + fSanitizedSizeX), int(pos.y) }, // Top Right
			{ int(pos.x), int(pos.y + fSanitizedSizeY) }, // Bottom Left
			{ int(pos.x + fSanitizedSizeX), int(pos.y + fSanitizedSizeY) } // Bottom Right
		};

		std::set<MapBlockRef> blocks = {
			MapBlockRef(map->GetBlockAt(coordinates[0].x, coordinates[0].y), coordinates[0]),
			MapBlockRef(map->GetBlockAt(coordinates[1].x, coordinates[1].y), coordinates[1]),
			MapBlockRef(map->GetBlockAt(coordinates[2].x, coordinates[2].y), coordinates[2]),
			MapBlockRef(map->GetBlockAt(coordinates[3].x, coordinates[3].y), coordinates[3])
		};

		return blocks;
	}
}