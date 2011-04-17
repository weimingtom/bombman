#include"MenuScene.h"
#include"Texture.h"
#include"Button.h"

MenuScene::~MenuScene()
{

}

void MenuScene::OnRender()
{
	bgImage->DisplayTexture(800,600,0,0);
}

void MenuScene::LoadScene()
{
	bgImage = new Texture();
	bgImage->LoadTexture(L"assets/STARTSCENE.bmp");
}

void MenuScene::UnloadScene()
{

}
