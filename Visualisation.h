#pragma once

#include <HAPI_lib.h>
#include "Rectangle.h"
#include "Sprite.h"

#include <unordered_map>

#include <iostream>

using namespace HAPISPACE;

class Sprite;

class Visualisation
{
public:

	Visualisation();
	~Visualisation();

	void ClearToColour(int screenWidth, int screenHeight, HAPI_TColour colour);

	int getScreenWidth() const
	{
		return screenWidth;
	}
	
	int getScreenHeight() const
	{
		return screenHeight;
	}

	int getAlphaVal() const
	{
		return alphaVal;
	}

	bool Initialise(int screenWidth, int screenHeight, std::string string); 

	bool CreateSprite(const std::string& filename, const std::string& name, int numFrames = 1, bool alpha = false);
	void RenderSprite(const std::string& name, int posX, int posY, int frameNum = 0);

	int GetNumFrames(const std::string& name)
	{
		return spriteMap.at(name)->GetNumFrames();
	}

	Rectangle getCollisionRect(const std::string& name) const;

private:

	BYTE* screenPntr{ nullptr };

	int screenWidth{ 1024 };
	int screenHeight{ 768 };
	const int alphaVal{ 255 };
	Rectangle screenRect;

	std::unordered_map<std::string, Sprite*> spriteMap;
};

