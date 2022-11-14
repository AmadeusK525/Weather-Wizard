#ifndef GAMEENTITYMANAGER_H_
#define GAMEENTITYMANAGER_H_

#pragma once

#include "AssetManager.h"
#include "Camera.h"
#include "Collectable.h"
#include "Map.h"
#include "Renderer.h"
#include "Season.h"
#include "WandBar.h"
#include "Wizard.h"

namespace ww
{
	class GameEntityManager
	{
	public:
		Wizard* m_pWizard;
		Camera* m_pCamera;
		Map* m_pMap;
		Season* m_pActiveSeason;
		WandBar* m_pWandBar;

		std::vector<Collectable*> m_vCollectables;

	public:
		GameEntityManager() = default;
		~GameEntityManager();

		void Initialize();

	private:
		void SortOutRenderers();
	};
}

#endif // GAMEENTITYMANAGER_H_