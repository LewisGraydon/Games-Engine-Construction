#include "Sprite.h"



Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	delete[] texturePnter;
}

bool Sprite::Load(const std::string &filename, int numFramesIn, bool alpha)
{
	if (HAPI.LoadTexture(filename, &texturePnter, textureRect.right, textureRect.bottom))
	{
		numFrames = numFramesIn;

		//Dependant on frames being the same size and laid out horizontally
		frameRect = Rectangle(textureRect.width() / numFrames, textureRect.height());
		hasAlpha = alpha;
		return true;
	}
	return false;
}

void Sprite::Render(const Rectangle& screenRect, int posX, int posY, BYTE* screen, int frameNum)
{
	Rectangle clippedRect(frameRect);
	
	//Transforms the texture rectangle into screen space
	clippedRect.Translate(posX, posY);

	//Does a check to see if the texture is completely outside of the screen, if it is then nothing will happen
	if (!clippedRect.CompletelyOutside(screenRect))
	{
		if (!clippedRect.CompletelyContains(screenRect))
		{
			//clips the texture against the screen
			clippedRect.ClipTo(screenRect);
		}
			
		//transforms the texture back into texture space
		clippedRect.Translate(-posX, -posY);

		//clamps negative position values to 0
		posX = std::max(0, posX);
		posY = std::max(0, posY);
		clippedRect.Translate(frameRect.width() * frameNum, 0);

		BYTE* screenPnter = screen + ((posX + posY * screenRect.width()) * 4);
		BYTE* tempTexturePnter = texturePnter;

		//increments the temportary texturePnter by 4 multiplied by the width of the frame rect multiplied by the top coord of the clipped rectangle added to the left coord of the clipped rectangle
		tempTexturePnter += (clippedRect.left + (clippedRect.top * frameRect.width())) * 4;

		int endOfLineOffset = (screenRect.width() - clippedRect.width()) * 4;
		int endOfLineTextureOffset = (textureRect.width() - clippedRect.width()) * 4;

		//if the texture is completely within the screen rect, it will just blit the texture to the screen using a memcpy
		if(!hasAlpha)
		{
			for (int y = 0; y < clippedRect.height(); y++)
			{
				memcpy(screenPnter, tempTexturePnter, clippedRect.width() * 4);

				// Move texture pointer to next line
				tempTexturePnter += textureRect.width() * 4;

				// Move screen pointer to next line
				screenPnter += screenRect.width() * 4;
			}
		}

		else
		{
			//loops through the texture and alpha blits it

			for (int y = 0; y < clippedRect.height(); y++)
			{
				for (int x = 0; x < clippedRect.width(); x++)
				{
					BYTE red = tempTexturePnter[0];
					BYTE green = tempTexturePnter[1];
					BYTE blue = tempTexturePnter[2];
					BYTE alpha = tempTexturePnter[3];

					//does a memcpy if the alpha value is 255 as it is opaque
					if (alpha == 255)
					{
						//memcpy(screenPnter, tempTexturePnter, 4);
						*((int*)screenPnter) = *((int*) tempTexturePnter);
					}

					//does nothing if the alpha value is 0 because it is transparent
					else if (alpha == 0){}

					else
					{
						screenPnter[0] += ((alpha * (blue - screenPnter[0])) >> 8); //bit shifting to divide by 256
						screenPnter[1] += ((alpha * (green - screenPnter[1])) >> 8);
						screenPnter[2] += ((alpha * (red - screenPnter[2])) >> 8);
					}

					//increments the screen and texture pointers by 4 bytes
					screenPnter += 4;
					tempTexturePnter += 4;
				}

				//increments the screen and texture pointers by their offsets
				screenPnter += endOfLineOffset;
				tempTexturePnter += endOfLineTextureOffset;
			}
		}
	}
}


