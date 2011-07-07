#include "BFaster.h"
#include "Md2Object.h"

BFaster::BFaster()
{
	//mModel = Md2Object::Load("c:\\box.md2","c:\\boxorange.bmp");
	mModel = Md2Object::Load(DataManager::GetDataPath("Model","bonus","resource\\data.ini"),DataManager::GetDataPath("Texture","orange","resource\\data.ini"));
	this->AddChild(mModel);
}
