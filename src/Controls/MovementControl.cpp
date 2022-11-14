#include "MovementControl.h"

#include <numeric>
#include <set>

namespace ww
{
	namespace movement_control
	{
		// Forward declarations. These aren't in the MovementController.h file because they shouldn't be part
		// of the public API, so they're "private".
		void ProcessInputForWizard(Wizard* wizard, const olc::PixelGameEngine* engine, float fElapsedTime);
		void UpdateWizard(Wizard* wizard, const Map* map, const Season* activeSeason, float fElapsedTime);
		void UpdateCamera(Camera* camera, Wizard* wizard, const Map* map, const olc::PixelGameEngine* engine);
		bool ReturnToStartIfOutOfBounds(Wizard* wizard, const Map* map);
		void UpdateWizardPosAndVelWithCollision(Wizard* wizard, const Map* map, const Season* activeSeason, float fElapsedTime);
		void UpdateWizardPosAndVelWithSpecialBlocks(Wizard* wizard, const Map* map, const Season* activeSeason, float fElapsedTime);
		void ApplySpecialBlockTransformToWizard(
			MapBlock block,
			Wizard* wizard,
			float fElapsedTime,
			const Season* activeSeason
		);
		bool IsBlockSolidInSeason(MapBlock block, const Season* season);

		// Definitions
		void UpdateWizardAndCameraForMapAndSeason(
			Wizard* wizard,
			Camera* camera,
			const Map* map,
			const Season* activeSeason,
			const olc::PixelGameEngine* engine,
			float fElapsedTime
		)
		{
			ProcessInputForWizard(wizard, engine, fElapsedTime);
			UpdateWizard(wizard, map, activeSeason, fElapsedTime);
			UpdateCamera(camera, wizard, map, engine);
		}

		void ProcessInputForWizard(Wizard* wizard, const olc::PixelGameEngine* engine, float fElapsedTime)
		{
			if ( engine->GetKey(olc::Key::D).bHeld )
				wizard->vel.x += (wizard->bIsOnGround ? 32.0f : 10.f) * fElapsedTime;
			if ( engine->GetKey(olc::Key::A).bHeld )
				wizard->vel.x -= (wizard->bIsOnGround ? 32.0f : 10.f) * fElapsedTime;
			if ( wizard->bIsInFlowerTangle )
			{
				if ( engine->GetKey(olc::Key::W).bHeld )
					wizard->vel.y = std::min(-2.0f, wizard->vel.y);

				if ( engine->GetKey(olc::Key::SPACE).bPressed && (engine->GetKey(olc::Key::W).bHeld || wizard->bIsOnGround) )
					wizard->vel.y = -12.0f;
			}
			else if ( engine->GetKey(olc::Key::SPACE).bHeld && wizard->bIsOnGround && !wizard->bIsInStrongWind )
				wizard->vel.y = -12.0f;

			wizard->vel = {
				std::max(-10.0f, std::min(10.0f, wizard->vel.x)),
				std::max(-100.0f, std::min(100.0f, wizard->vel.y))
			};
		}

		void UpdateWizard(Wizard* wizard, const Map* map, const Season* activeSeason, float fElapsedTime)
		{
			if ( ReturnToStartIfOutOfBounds(wizard, map) )
				return;

			// Apply gravity
			wizard->vel.y += 30.f * fElapsedTime;

			// Slow Wizard down to stop movement
			if ( wizard->bIsOnGround )
			{
				wizard->vel.x += -4.0f * wizard->vel.x * fElapsedTime;

				if ( std::fabs(wizard->vel.x) < 0.01f )
					wizard->vel.x = 0.0f;
			}

			// These flags are recalculated each frame, so we always reset them to false
			wizard->bIsOnGround = false;
			wizard->bIsInFlowerTangle = false;
			wizard->bIsInStrongWind = false;

			UpdateWizardPosAndVelWithCollision(wizard, map, activeSeason, fElapsedTime);
			UpdateWizardPosAndVelWithSpecialBlocks(wizard, map, activeSeason, fElapsedTime);

			if ( wizard->vel.x > 0.0f )
				wizard->lastFaceDirection = FaceDirection::RIGHT;
			else if ( wizard->vel.x < 0.0f )
				wizard->lastFaceDirection = FaceDirection::LEFT;
		}

		void UpdateCamera(Camera* camera, Wizard* wizard, const Map* map, const olc::PixelGameEngine* engine)
		{
			float fVerticalBlockCapacity = float(engine->ScreenHeight()) / camera->blockSize.y;
			float fHorizontalBlockCapacity = float(engine->ScreenWidth()) / camera->blockSize.x;

			float fNewCameraPosX = wizard->pos.x - (fHorizontalBlockCapacity / 2) + (wizard->sizeInUnits.x * 0.5f);
			float fNewCameraPosY = wizard->pos.y - (fVerticalBlockCapacity / 2) + (wizard->sizeInUnits.y * 0.5f);

			if ( fNewCameraPosX + fHorizontalBlockCapacity > map->m_nWidth )
				fNewCameraPosX = map->m_nWidth - fHorizontalBlockCapacity;
			if ( fNewCameraPosY + fVerticalBlockCapacity > map->m_nHeight )
				fNewCameraPosY = map->m_nHeight - fVerticalBlockCapacity;

			camera->pos = { std::max(0.0f, fNewCameraPosX), std::max(0.0f, fNewCameraPosY) };
		}

		bool ReturnToStartIfOutOfBounds(Wizard* wizard, const Map* map)
		{
			if ( wizard->pos.x > map->m_nWidth || wizard->pos.y > map->m_nHeight )
			{
				wizard->pos = map->m_startPos;
				wizard->vel = { 0.0f, 0.0f };
				return true;
			}

			return false;
		}

		void UpdateWizardPosAndVelWithCollision(Wizard* wizard, const Map* map, const Season* activeSeason, float fElapsedTime)
		{
			olc::vf2d newPos = wizard->pos + (wizard->vel * fElapsedTime);

			// Don't use Wizard::GetIntersectingBlocksInMap(const Map*) in the following calculations because
			// we need to exclude the y axis while calculating the x axis. That's why sometimes we use
			// 'newPos' and other times we use 'wizard->pos'. It'd be a lot simpler though :(
			if ( wizard->vel.x <= 0 )
			{
				bool bIsTopLeftSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x), int(wizard->pos.y)),
					activeSeason
				);
				bool bIsBottomLeftSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x), int(wizard->pos.y + (wizard->sizeInUnits.y * 0.999f))),
					activeSeason
				);

				if ( bIsTopLeftSolid || bIsBottomLeftSolid )
				{
					newPos.x = int(newPos.x) + 1.0f;
					wizard->vel.x = 0.0f;
				}
			}
			else
			{
				bool bIsTopRightSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x + wizard->sizeInUnits.x), int(wizard->pos.y)),
					activeSeason
				);
				bool bIsBottomRightSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x + wizard->sizeInUnits.x), int(wizard->pos.y + (wizard->sizeInUnits.y * 0.999f))),
					activeSeason
				);

				if ( bIsTopRightSolid || bIsBottomRightSolid )
				{
					newPos.x = int(newPos.x) + (1.0f - wizard->sizeInUnits.x);
					wizard->vel.x = 0.0f;
				}
			}

			if ( wizard->vel.y <= 0 )
			{
				bool bIsTopLeftSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x), int(newPos.y)),
					activeSeason
				);
				bool bIsTopRightSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x + (wizard->sizeInUnits.x * 0.999f)), int(newPos.y)),
					activeSeason
				);

				if ( bIsTopLeftSolid || bIsTopRightSolid )
				{
					newPos.y = int(newPos.y) + 1.0f;
					wizard->vel.y = 0.0f;
				}
			}
			else
			{
				bool bIsBottomLeftSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x), int(newPos.y + wizard->sizeInUnits.y)),
					activeSeason
				);
				bool bIsBottomRightSolid = IsBlockSolidInSeason(
					map->GetBlockAt(int(newPos.x + (wizard->sizeInUnits.x * 0.999f)), int(newPos.y + wizard->sizeInUnits.y)),
					activeSeason
				);

				if ( bIsBottomLeftSolid || bIsBottomRightSolid )
				{
					newPos.y = int(newPos.y) + (1.0f - wizard->sizeInUnits.y);
					wizard->vel.y = 0.0f;
					wizard->bIsOnGround = true;
				}
			}

			wizard->pos = newPos;
		}

		void UpdateWizardPosAndVelWithSpecialBlocks(Wizard* wizard, const Map* map, const Season* activeSeason, float fElapsedTime)
		{
			std::set<MapBlockRef> intersectingBlockRefs = wizard->GetIntersectingBlockRefsInMap(map);
			// Apply each block transform only once, even if player is intersecting with two
			std::set<MapBlock> exclusiveBlockRefs = std::reduce(
				intersectingBlockRefs.begin(),
				intersectingBlockRefs.end(),
				std::set<MapBlock>(),
				[](std::set<MapBlock>& sum, const MapBlockRef& blockRef)
				{
					sum.insert(blockRef.block);
					return sum;
				}
			);

			for ( const MapBlock& block : exclusiveBlockRefs )
				ApplySpecialBlockTransformToWizard(block, wizard, fElapsedTime, activeSeason);
		}

		void ApplySpecialBlockTransformToWizard(
			MapBlock block,
			Wizard* wizard,
			float fElapsedTime,
			const Season* activeSeason
		)
		{
			switch ( block )
			{
			case MapBlock::AIR:
			case MapBlock::BRICK:
			case MapBlock::FIRE:
			case MapBlock::ICE_WATER:
				break;
			case MapBlock::FLOWER_TANGLE:
				wizard->bIsInFlowerTangle = activeSeason->flowerGrowthPercent >= 0.5f;
				break;
			case MapBlock::WIND_UP:
				wizard->bIsInStrongWind = activeSeason->windSpeed >= 30.0f;
				wizard->vel.y -= activeSeason->windSpeed * fElapsedTime;
				break;
			case MapBlock::WIND_DOWN:
				wizard->bIsInStrongWind = activeSeason->windSpeed >= 30.0f;
				wizard->vel.y += activeSeason->windSpeed * fElapsedTime;
				break;
			case MapBlock::WIND_LEFT:
				wizard->bIsInStrongWind = activeSeason->windSpeed >= 30.0f;
				wizard->vel.x -= activeSeason->windSpeed * fElapsedTime;
				break;
			case MapBlock::WIND_RIGHT:
				wizard->bIsInStrongWind = activeSeason->windSpeed >= 30.0f;
				wizard->vel.x += activeSeason->windSpeed * fElapsedTime;
				break;
			}
		}

		bool IsBlockSolidInSeason(MapBlock block, const Season* season)
		{
			switch ( block )
			{
			case MapBlock::BRICK:
				return true;
			case MapBlock::FIRE:
				return season->temperatureCelsius >= 30.0f;
			case MapBlock::ICE_WATER:
				return season->temperatureCelsius <= 0.0f;
			case MapBlock::AIR:
			case MapBlock::WIND_DOWN:
			case MapBlock::WIND_LEFT:
			case MapBlock::WIND_RIGHT:
			case MapBlock::WIND_UP:
			case MapBlock::FLOWER_TANGLE:
			default:
				return false;
			}
		}
	}
}