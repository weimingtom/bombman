#pragma once
#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>		// Header File For The Glaux Library
#include <gl/glut.h>

class Texture
{
public:
	Texture();
	bool LoadTexture(TCHAR *Filename);
	void DisplayTexture(GLdouble width,GLdouble height,GLdouble x,GLdouble y);
	void ScaleTexture();
	bool DestroyTexture();
private:
	AUX_RGBImageRec* textureImage;
};