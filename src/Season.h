#ifndef SEASON_H_
#define SEASON_H_

#pragma once

#include "AssetManager.h"
#include "SkyColor.h"

namespace ww
{
	struct Season
	{
		olc::Sprite* skySprite;
		std::string name;
		float temperatureCelsius;
		float windSpeed;
		float flowerGrowthPercent;

		Season(
			olc::Sprite* skySprite,
			std::string name,
			float temperatureCelsius,
			float windSpeedMPS,
			float flowerGrowthPercent
		) :
			skySprite(skySprite), 
			name(name),
			temperatureCelsius(temperatureCelsius), 
			windSpeed(windSpeedMPS),
			flowerGrowthPercent(flowerGrowthPercent)
		{
		}

		static Season CreateFall()
		{
			return Season(AssetManager::LoadSprite(Asset::SKY_FALL), "Fall", 18.0f, 36.0f, 0.4f);
		}

		static Season CreateSpring()
		{
			return Season(AssetManager::LoadSprite(Asset::SKY_SPRING), "Spring", 25.0f, 4.0f, 0.86f);
		}

		static Season CreateSummer()
		{
			return Season(AssetManager::LoadSprite(Asset::SKY_SUMMER), "Summer", 35.0f, 1.2f, 0.30f);
		}

		static Season CreateWinter()
		{
			return Season(AssetManager::LoadSprite(Asset::SKY_WINTER), "Winter", - 8.0f, 4.0f, 0.02f);
		}
	};
}

#endif // SESASON_H_