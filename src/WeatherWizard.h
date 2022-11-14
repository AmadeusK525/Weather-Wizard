#ifndef WEATHERWIZARD_H_
#define WEATHERWIZARD_H_

#pragma once

#include "GameEntityManager.h"
#include "olcPixelGameEngine.h"

namespace ww
{
	class WeatherWizard : public olc::PixelGameEngine
	{
	private:
		GameEntityManager* m_pGameEntityManager;
		std::vector<Renderer*> m_vRenderers;

		bool m_bHasFinishedGame = false;
		bool m_bIsInMenu = false;

	public:
		WeatherWizard();
		virtual ~WeatherWizard();

	public:
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;
		bool OnUserDestroy() override;

		void RestartGame();

	private:
		void CollectCollectablesIfAnyAndUpdateMap(const Wizard* wizard, Map* map);
		bool CheckWizardForFinishInMap(const Wizard* wizard, const Map* map);

		void RecreateRenderers();

		template<typename T>
		inline void DeletePointerVector(std::vector<T>* vector)
		{
			for ( T t : *vector )
				delete t;

			vector->clear();
		}
	};
}

#endif // WEATHERWIZARD_H_