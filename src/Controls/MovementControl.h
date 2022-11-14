#ifndef MOVEMENTCONTROL_H_
#define MOVEMENTCONTROL_H_

#pragma once

#include "Camera.h"
#include "CollisionCommand.h"
#include "Map.h"
#include "MapBlockCorners.h"
#include "olcPixelGameEngine.h"
#include "Season.h"
#include "Wizard.h"

namespace ww
{
	namespace movement_control
	{
		void UpdateWizardAndCameraForMapAndSeason(
			Wizard* wizard,
			Camera* camera,
			const Map* map,
			const Season* activeSeason,
			const olc::PixelGameEngine* engine, 
			float fElapsedTime
		);
	}
		//void ProcessInput(const olc::PixelGameEngine* engine, float fElapsedTime);

		//void UpdateWizard(const olc::PixelGameEngine* engine, float fElapsedTime, Wizard* wizard);
		//void UpdateCamera(const olc::PixelGameEngine* engine, Camera* camera);

		//bool ReturnToStartIfOutOfBounds(Wizard* wizard);
		//void UpdateWizardPosAndVelWithCollision(Wizard* wizard, float fElapsedTime);
		//void UpdateWizardPosAndVelWithSpecialBlocks(Wizard* wizard, const Season* activeSeason, float fElapsedTime);
		//void ApplySpecialBlockTransformToWizard(
		//	MapBlock block,
		//	Wizard* wizard,
		//	float fElapsedTime,
		//	const Season* activeSeason
		//);

		//CollisionCommand GetCollisionCommandAndSetWizardFlags(MapBlock block);
		//olc::vf2d GetNewPosWithCommandsAndSetWizardVelocityAndFlags(
		//	olc::vf2d newPos,
		//	std::pair<CollisionCommand, CollisionCommand> commands, 
		//	MapBlockCorners corners
		//);
		//bool IsBlockSolidInActiveSeason(MapBlock block);
}

#endif // MOVEMENTCONTROL_H_