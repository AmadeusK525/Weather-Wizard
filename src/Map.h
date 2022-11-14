#ifndef MAP_H_
#define MAP_H_

#pragma once

#include <string>

#include "MapBlock.h"
#include "olcPixelGameEngine.h"

namespace ww
{
	class Map
	{
	private:
		const std::string m_sData;
		MapBlock* m_pBlocks;

	public:
		const int m_nWidth;
		const int m_nHeight;
		const olc::vi2d m_startPos;


	public:
		Map(int width, int height, const std::string& data, const olc::vi2d& startPos);
		~Map();

		inline const MapBlock* GetBlocks() const { return m_pBlocks; }

		MapBlock GetBlockAt(int x, int y) const;
		void SetBlockAt(MapBlock block, int x, int y);

		void ResetToOriginalData();

		static Map* CreateTestLevel();
		static Map* CreateLevel1();

	private:
		static MapBlock* ProcessDataAndGetBlocks(const std::string& data);
		static MapBlock ProcessCharAndGetBlock(char character);
	};
}

#endif // MAP_H_