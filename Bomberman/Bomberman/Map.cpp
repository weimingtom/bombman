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
		return false;
	return true;
}

void Map::SetBomb( int gridId )
{
	grids[gridId].expDanger = 100;
}
