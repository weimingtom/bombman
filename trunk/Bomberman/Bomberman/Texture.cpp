#include"Texture.h"

Texture::Texture()
{
	textureImage = NULL;
}

bool Texture::LoadTexture(TCHAR *Filename)
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		//textureImage = NULL;
		return false;									// If Not Return NULL
	}

	textureImage = auxDIBImageLoad(Filename);// Load The Bitmap And Return A Pointer
	if(!textureImage) return false;
		return true;
}

void Texture::DisplayTexture(GLdouble width,GLdouble height,GLdouble x,GLdouble y)
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,width,0,height,-1,1);							// Set Up An Ortho Screen

	glRasterPos2d(x,y);
	glDrawPixels(textureImage->sizeX,textureImage->sizeY,GL_RGB,GL_UNSIGNED_BYTE,textureImage->data);
	glPopMatrix();									
}

bool Texture::DestroyTexture()
{
	if(textureImage)
	{
		if(textureImage->data)
			free(textureImage->data);
		free(textureImage);
	}
	return true;
}