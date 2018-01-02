#pragma once

#include <HAPI_lib.h>
#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite
{
public:
	Sprite();
	~Sprite();

	bool Load(const std::string &filename, int numFrames = 1, bool alpha = false);
	void Render(const Rectangle& screenRect, int posX, int posY, BYTE* screenint, int frameNum);
	int GetNumFrames()
	{
		return numFrames;
	}

	Rectangle getRect() const
	{
		return frameRect;
	}

private:

	BYTE* texturePnter{ nullptr };
	Rectangle textureRect;
	Rectangle frameRect;
	int numFrames{ 1 };
	bool hasAlpha{ false };
};

