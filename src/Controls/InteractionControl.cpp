#include "InteractionControl.h"

namespace ww
{
	namespace interaction_control
	{
		bool BlockRefsContainBlock(const std::set<MapBlockRef>& blockRefs, MapBlock block);

		void ProcessInputAndUpdateSeasonAndWandBarInMap(
			const Wizard* wizard,
			Season* season,
			WandBar* wandBar,
			const Map* map,
			const olc::PixelGameEngine* engine,
			float fElapsedTime
		)
		{
			if ( engine->GetKey(olc::Key::LEFT).bPressed )
				wandBar->DecreaseWandSelection();
			else if ( engine->GetKey(olc::Key::RIGHT).bPressed )
				wandBar->IncreaseWandSelection();

			if ( engine->GetKey(olc::Key::ENTER).bPressed )
			{
				Season newSeason = wandBar->GetCurrentWand().season;
	
				if ( CanWizardChangeToSeasonInMap(wizard, newSeason, map) )
					*season = newSeason;
			}
		}

		bool CanWizardChangeToSeasonInMap(const Wizard* wizard, const Season& season, const Map* map)
		{
			std::set<MapBlockRef> intersectingBlockRefs = wizard->GetIntersectingBlockRefsInMap(map);

			if ( season.temperatureCelsius >= 25.0f && BlockRefsContainBlock(intersectingBlockRefs, MapBlock::FIRE) )
				return false;
			else if ( season.temperatureCelsius < 0.0f && BlockRefsContainBlock(intersectingBlockRefs, MapBlock::ICE_WATER) )
				return false;

			return true;
		}

		bool BlockRefsContainBlock(const std::set<MapBlockRef>& blockRefs, MapBlock block)
		{
			for ( const MapBlockRef& blockRef : blockRefs )
				if ( blockRef.block == block ) return true;

			return false;
		}
	}
}