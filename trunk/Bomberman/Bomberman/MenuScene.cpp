#include"MenuScene.h"
#include"Texture.h"
#include"Button.h"

MenuScene::MenuScene()
{
	bgImage = new Texture();
	bgImage->LoadTexture(L"assets/STARTSCENE.bmp");

	//buttons[0] = new Button();
	//buttons[0]->GetTexture()->LoadTexture("");
}

MenuScene::~MenuScene()
{
}

void MenuScene::OnRender()
{
	bgImage->DisplayTexture(800,600,0,0);
	//buttons[0]->GetTexture()->DisplayTexture(30,30,1,1);/
}