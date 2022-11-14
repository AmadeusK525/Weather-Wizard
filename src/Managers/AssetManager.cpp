#include "AssetManager.h"

namespace ww
{
	AssetManager::~AssetManager()
	{
		for ( AssetRef<olc::Sprite*> ref : loadedSprites )
			delete ref.ref;

		for ( AssetRef<olc::Decal*> ref : loadedDecals )
			delete ref.ref;

		loadedSprites.clear();
		loadedDecals.clear();
	}

	olc::Sprite* AssetManager::LookForSprite(Asset id)
	{
		return LookForAsset(id, loadedSprites);
	}

	olc::Decal* AssetManager::LookForDecal(Asset id)
	{
		return LookForAsset(id, loadedDecals);
	}

	std::string AssetManager::GetFilenameFromAsset(Asset id)
	{
		switch ( id )
		{
		case Asset::BOOK: return "Assets/Book.png";
		case Asset::SKY_FALL: return "Assets/Sky-Fall.png";
		case Asset::SKY_SPRING: return "Assets/Sky-Spring.png";
		case Asset::SKY_SUMMER: return "Assets/Sky-Summer.png";
		case Asset::SKY_WINTER: return "Assets/Sky-Winter.png";
		case Asset::SPRITESHEET_BLOCKS: return "Assets/Spritesheet-Blocks.png";
		case Asset::SPRITESHEET_PORTAL: return "Assets/Spritesheet-Portal.png";
		case Asset::SPRITESHEET_WIZARD_LEFT: return "Assets/Spritesheet-Wizard-Left.png";
		case Asset::SPRITESHEET_WIZARD_RIGHT: return "Assets/Spritesheet-Wizard-Right.png";
		case Asset::WAND_FALL: return "Assets/Wand-Fall.png";
		case Asset::WAND_SPRING: return "Assets/Wand-Spring.png";
		case Asset::WAND_SUMMER: return "Assets/Wand-Summer.png";
		case Asset::WAND_WINTER: return "Assets/Wand-Winter.png";
		default:
			return "";
		}
	}

	olc::Sprite* AssetManager::LoadSpriteImpl(Asset id, bool takeOwnership)
	{
		olc::Sprite* loadedSprite = LookForSprite(id);
		if ( loadedSprite ) return loadedSprite;

		std::string filename = GetFilenameFromAsset(id);
		olc::Sprite* sprite = new olc::Sprite(filename);

		if ( !takeOwnership )
			loadedSprites.push_back(AssetRef<olc::Sprite*>(id, sprite));

		return sprite;
	}

	olc::Decal* AssetManager::LoadDecalImpl(Asset id, bool takeOwnership)
	{
		olc::Decal* loadedDecal = LookForDecal(id);
		if ( loadedDecal ) return loadedDecal;

		olc::Sprite* sprite = LoadSprite(id);
		olc::Decal* decal = new olc::Decal(sprite);

		if ( !takeOwnership )
			loadedDecals.push_back(AssetRef<olc::Decal*>(id, decal));

		return decal;
	}
}