#include "Uwall.h"
#include "Md2Object.h"
#include <iostream>

#include "DataManager.h"

using namespace std;

Uwall::Uwall()
{
	mModel = Md2Object::Load("c:\\uwall.md2","c:\\uwallt.bmp");
	//mModel = Md2Object::Load(DataManager::GetDataPath("Model","uwall","c:\\data.ini"),"c:\\bluebox.bmp");
	this->AddChild(mModel);
}

Uwall::~Uwall()
{
	cout << "uwall released " << endl;
}
