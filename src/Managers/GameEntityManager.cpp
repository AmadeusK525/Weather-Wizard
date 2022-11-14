#include "GameEntityManager.h"

namespace ww
{
	GameEntityManager::~GameEntityManager() 
	{
		delete m_pWizard;
		delete m_pCamera;
		delete m_pMap;
		delete m_pActiveSeason;
		delete m_pWandBar;

		for ( Collectable* collectable : m_vCollectables )
			delete collectable;

		m_vCollectables.clear();
	}

	void GameEntityManager::Initialize()
	{
		olc::Sprite* summerWandIcon = AssetManager::LoadSprite(Asset::WAND_SUMMER);
		olc::Sprite* fallWandIcon = AssetManager::LoadSprite(Asset::WAND_FALL);
		olc::Sprite* winterWandIcon = AssetManager::LoadSprite(Asset::WAND_WINTER);
		olc::Sprite* springWandIcon = AssetManager::LoadSprite(Asset::WAND_SPRING);

		std::vector<SeasonWand> wands = {
			SeasonWand(summerWandIcon, Season::CreateSummer()),
			SeasonWand(fallWandIcon, Season::CreateFall()),
			SeasonWand(winterWandIcon, Season::CreateWinter()),
			SeasonWand(springWandIcon, Season::CreateSpring()),
		};

		m_pMap = Map::CreateLevel1();
		m_pWizard = new Wizard(m_pMap->m_startPos);
		m_pCamera = new Camera({ 0.0f, 0.0f }, { 16, 16 });
		m_pActiveSeason = new Season(wands[0].season);
		m_pWandBar = new WandBar(wands);
	}
}