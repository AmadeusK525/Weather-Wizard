#include "WeatherWizard.h"

#include "Book.h"
#include "EndGameRenderer.h"
#include "EndGameControl.h"
#include "InteractionControl.h"
#include "MapRenderer.h"
#include "MenuRenderer.h"
#include "MovementControl.h"
#include "SkyBoxRenderer.h"
#include "WandBarRenderer.h"
#include "WizardRenderer.h"

namespace ww
{
	WeatherWizard::WeatherWizard()
	{
		sAppName = "Weather Wizard";

		m_pGameEntityManager = new GameEntityManager;
		m_pGameEntityManager->Initialize();

		RecreateRenderers();
	}

	WeatherWizard::~WeatherWizard()
	{
		delete m_pGameEntityManager;
		DeletePointerVector(&m_vRenderers);
	}

	bool WeatherWizard::OnUserCreate()
	{
		return true;
	}

	bool WeatherWizard::OnUserUpdate(float fElapsedTime)
	{
		for ( Renderer* renderer : m_vRenderers )
			renderer->Render(this, fElapsedTime);

		if ( !m_bIsInMenu )
		{
			if ( m_bHasFinishedGame )
			{
				EndGameControlPayload inputPayload = endgame_control::ProcessInput(this, fElapsedTime);
				if ( inputPayload.bShouldRestartGame )
					RestartGame();
			}
			else
			{
				interaction_control::ProcessInputAndUpdateSeasonAndWandBarInMap(
					m_pGameEntityManager->m_pWizard,
					m_pGameEntityManager->m_pActiveSeason,
					m_pGameEntityManager->m_pWandBar,
					m_pGameEntityManager->m_pMap,
					this,
					fElapsedTime
				);

				movement_control::UpdateWizardAndCameraForMapAndSeason(
					m_pGameEntityManager->m_pWizard,
					m_pGameEntityManager->m_pCamera,
					m_pGameEntityManager->m_pMap,
					m_pGameEntityManager->m_pActiveSeason,
					this,
					fElapsedTime
				);
			}
		}

		if ( GetKey(olc::Key::ESCAPE).bPressed )
		{
			m_bIsInMenu = !m_bIsInMenu;
			RecreateRenderers();
		}

		CollectCollectablesIfAnyAndUpdateMap(m_pGameEntityManager->m_pWizard, m_pGameEntityManager->m_pMap);

		if ( CheckWizardForFinishInMap(m_pGameEntityManager->m_pWizard, m_pGameEntityManager->m_pMap) )
		{
			m_bHasFinishedGame = true;
			RecreateRenderers();
		}

		//DrawString({ 0, 0 }, std::to_string(m_pGameEntityManager->m_pWizard->vel.x));
		return true;
	}

	bool WeatherWizard::OnUserDestroy()
	{
		return true;
	}

	void WeatherWizard::RestartGame()
	{
		m_pGameEntityManager->m_pWizard->pos = m_pGameEntityManager->m_pMap->m_startPos;
		m_pGameEntityManager->m_pWizard->vel = { 0.0f, 0.0f };
		m_pGameEntityManager->m_pMap->ResetToOriginalData();
		m_bHasFinishedGame = false;
		DeletePointerVector(&m_pGameEntityManager->m_vCollectables);

		RecreateRenderers();
	}

	void WeatherWizard::CollectCollectablesIfAnyAndUpdateMap(const Wizard* wizard, Map* map)
	{
		std::set<MapBlockRef> intersectingBlockRefs = wizard->GetIntersectingBlockRefsInMap(map);

		for ( const MapBlockRef& blockRef : intersectingBlockRefs )
		{
			switch ( blockRef.block )
			{
			case MapBlock::BOOK:
				m_pGameEntityManager->m_vCollectables.push_back(new Book);
				break;
			default:
				continue;
			}

			map->SetBlockAt(MapBlock::AIR, blockRef.coordinate.x, blockRef.coordinate.y);
		}
	}

	bool WeatherWizard::CheckWizardForFinishInMap(const Wizard* wizard, const Map* map)
	{
		std::set<MapBlockRef> intersectingBlockRefs = wizard->GetIntersectingBlockRefsInMap(map);
		bool bHasFinishedGame = true;

		for ( const MapBlockRef& blockRef : intersectingBlockRefs )
		{
			if ( blockRef.block != MapBlock::FINISH )
			{
				bHasFinishedGame = false;
				break;
			}
		}

		return bHasFinishedGame;
	}

	void WeatherWizard::RecreateRenderers()
	{
		DeletePointerVector(&m_vRenderers);

		m_vRenderers.push_back(new SkyBoxRenderer(m_pGameEntityManager->m_pCamera, m_pGameEntityManager->m_pActiveSeason));
		m_vRenderers.push_back(new MapRenderer(
			m_pGameEntityManager->m_pMap,
			m_pGameEntityManager->m_pCamera, 
			m_pGameEntityManager->m_pActiveSeason
		));
		m_vRenderers.push_back(new WizardRenderer(
			m_pGameEntityManager->m_pWizard,
			m_pGameEntityManager->m_pCamera
		));
		m_vRenderers.push_back(new WandBarRenderer(m_pGameEntityManager->m_pWandBar));

		if ( m_bHasFinishedGame )
			m_vRenderers.push_back(new EndGameRenderer(m_pGameEntityManager->m_vCollectables));

		if ( m_bIsInMenu )
			m_vRenderers.push_back(new MenuRenderer);
	}
}