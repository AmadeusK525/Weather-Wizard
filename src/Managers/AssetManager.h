#ifndef ASSETMANAGER_H_
#define ASSETMANAGER_H_

#pragma once

#include "Asset.h"
#include "olcPixelGameEngine.h"

namespace ww
{
	class AssetManager
	{
	private:
		template<typename T>
		struct AssetRef
		{
			Asset id;
			T ref;

			AssetRef(Asset id, T ref) : id(id), ref(ref) {}
		};

		std::vector<AssetRef<olc::Sprite*>> loadedSprites;
		std::vector<AssetRef<olc::Decal*>> loadedDecals;

		olc::Sprite* LookForSprite(Asset id);
		olc::Decal* LookForDecal(Asset id);

	private:
		AssetManager() = default;

		inline static AssetManager& Get()
		{
			static AssetManager manager;
			return manager;
		}

		template<typename T>
		T LookForAsset(Asset id, std::vector<AssetRef<T>> vec)
		{
			for ( AssetRef<T> assetRef: vec )
			{
				if ( assetRef.id == id )
					return assetRef.ref;
			}

			return nullptr;
		}

		std::string GetFilenameFromAsset(Asset id);
		olc::Sprite* LoadSpriteImpl(Asset id, bool takeOwnership = false);
		olc::Decal* LoadDecalImpl(Asset id, bool takeOwnership = false);

	public:
		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		~AssetManager();

		inline static olc::Sprite* LoadSprite(Asset id, bool takeOwnership = false)
		{
			return Get().LoadSpriteImpl(id, takeOwnership);
		}
		inline static olc::Decal* LoadDecal(Asset id, bool takeOwnership = false)
 {
			return Get().LoadDecalImpl(id, takeOwnership);
		}
	};
}

#endif // ASSETMANAGER_H_