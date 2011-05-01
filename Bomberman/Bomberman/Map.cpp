#include"Map.h"

void Map::Load()
{

}

void Map::Unload()
{

}

Map::Map()
{

}

Map::~Map()
{

}

bool Map::CanPass( int gridId )
{
	if(grids[gridId].gridState == Dwall||grids[gridId].gridState == Uwall)
		return true;
	return false;
}
