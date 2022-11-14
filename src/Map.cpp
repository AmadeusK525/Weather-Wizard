#include "Map.h"

namespace ww
{
	Map::Map(int width, int height, const std::string& data, const olc::vi2d& startPos) : 
		m_nWidth(width), m_nHeight(height), m_sData(data), m_startPos(startPos)
	{
		m_pBlocks = ProcessDataAndGetBlocks(data);
	}

	Map::~Map()
	{
		delete[] m_pBlocks;
	}

	MapBlock* Map::ProcessDataAndGetBlocks(const std::string& data)
	{
		MapBlock* blocks = new MapBlock[data.size()];

		for ( int i = 0; i < data.size(); i++ )
		{
			MapBlock block = ProcessCharAndGetBlock(data[i]);
			blocks[i] = block;
		}

		return blocks;
	}

	MapBlock Map::ProcessCharAndGetBlock(char character)
	{
		switch ( character )
		{
		case ' ': return MapBlock::AIR;
		case '#': return MapBlock::BRICK;
		case 'B': return MapBlock::BOOK;
		case 'F': return MapBlock::FINISH;
		case '&': return MapBlock::FIRE;
		case '0': return MapBlock::ICE_WATER;
		case '$': return MapBlock::FLOWER_TANGLE;
		case 'u': return MapBlock::WIND_DOWN;
		case '<': return MapBlock::WIND_LEFT;
		case '>': return MapBlock::WIND_RIGHT;
		case '^': return MapBlock::WIND_UP;
		default: return MapBlock::AIR;
		}
	}

	MapBlock Map::GetBlockAt(int x, int y) const
	{
		if ( x < 0 || y < 0 || x > (m_nWidth - 1) || y > (m_nHeight - 1) )
			return MapBlock::AIR;

		return m_pBlocks[(y * m_nWidth) + x];
	}

	void Map::SetBlockAt(MapBlock block, int x, int y)
	{
		if ( x < 0 || y < 0 || x >(m_nWidth - 1) || y > (m_nHeight - 1) )
			return;

		m_pBlocks[(y * m_nWidth) + x] = block;
	}

	void Map::ResetToOriginalData()
	{
		delete[] m_pBlocks;
		m_pBlocks = ProcessDataAndGetBlocks(m_sData);
	}

	Map* Map::CreateTestLevel()
	{
		std::string data;
		data += "#                        $                       #";
		data += "#                        $                       #";
		data += "#                        $                       #";
		data += "#                        $                       #";
		data += "#                        $                       #";
		data += "#                        $                       #";
		data += "#                       &$#^               <<    #";
		data += "#                       &$#^               <<    #";
		data += "#                       &$#^               <<    #";
		data += "#                  &###############        <<  &&#";
		data += "#                 #               #############  #";
		data += "#                ##                              #";
		data += "#              #######                          0#";
		data += "##$###   #####000000000######     ####^&&&&&&&&&&#";
		data += "##$####  ##################     ######^&&&&&&&&&##";
		data += "##$####       $  $$  $       #########^&&&&&&&&&##";
		data += "##$###################################&&&&&&&&&&##";
		data += "##$###################################        ####";
		data += "##$####################################      #####";
		data += "##$#####################################    ######";
		data += "##                                          ######";
		data += "##################################################";

		Map* map = new Map(50, 22, data, { 3, 6 });
		return map;
	}

	Map* Map::CreateLevel1()
	{
		std::string data;
		data += "###               $$                                                      ##########################       #######################";
		data += "#BB               $$^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^#B##$       B B B B B                 BB##################";
		data += "#^                $$                                                    # ##$#######################0000000#######################";
		data += "#^                $$                                                    #B##$  ######BBB############0000000#######################";
		data += "#^                $$                       BBB                          # ##    ###### #############       ####################BB#";
		data += "#                 $$                                                    #B##     #####0#############          BB###############  #";
		data += "#&                $$                           0000000000^^^^           # ## <^#                  ##&&&&&&&####################  #";
		data += "#                 $$      &&&&       ##########0000000000 ^^^^          #B## <^#0    ^#^          ##&&&&&&&####################  F";
		data += "# 0                       &&&&       ##########                         # ##uuu#00    #           ##       ####################$##";
		data += "#                                                              &&&&&&&&$#B##uuu#000   #   BBB     ##          BB###############$##";
		data += "#&                                                             &&&&&&&&$# #######################$##$$$$$$$ ###################$##";
		data += "#                                                                      $#B#######################$##$$$$$$$#################### ##";
		data += "######                                   B                             $# ##############      && $##       #################### $#";
		data += "#                       ^#               ^                             $#B##############      && $##       #####################$#";
		data += "#                       ^#               ^                             $# ##############  BBB && $##^^^^^^^#####################$#";
		data += "#                       ^#                                             $#B##############      &#####^^^^^^^#####################$#";
		data += "#                       ^#   BBB                                       $# ##############&     &#####^^^^^^^#####################$#";
		data += "########000000000##^###############&&&&     00000####                  $#B##########>   &     &#####^^^^^^^^^^^        0        $#";
		data += "########000000000##^###############&&&&     00000#####      BBBBBB     $# ##########^###############^^^^^^^^^^^        0         #";
		data += "########000000000   ###############&&&&     00000######                $#B##########^###############^^^^^^^^^^^        0         #";
		data += "###################################&&&&     00000#######               $# ##########        $#######^^^^^^^^^^^000000  0  &&&&&&&#";
		data += "##############################                   ########################B##########        $#######           000000  0  &&&&&&&#";
		data += "##############################                   ######################## ###############   $#######                             #";
		data += "##############################                   ########################B##########        $#######                             #";
		data += "##############################                   ######################## #########         $#######                             #";
		data += "##############################                   ########################B########     #############                             #";
		data += "#                                                ########################             ##############                             #";
		data += "#                                                ########################            ###############                             #";
		data += "#                                                ########################           ################                             #";
		data += "#                                                ###################################################                             #";

		Map* map = new Map(130, 30, data, { 1, 16 });
		return map;
	}
}