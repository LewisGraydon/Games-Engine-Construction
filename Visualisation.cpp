#include "Visualisation.h"

Visualisation::Visualisation()
{
}


Visualisation::~Visualisation()
{
	for (auto& p : spriteMap)
		delete p.second;
}

void Visualisation::ClearToColour(int screenWidth, int screenHeight, HAPI_TColour colour)
{
	for (int i = 0; i < screenWidth * screenHeight; i++)
	{
		screenPntr[i * 4] = colour.red;
		screenPntr[i * 4 + 1] = colour.green;
		screenPntr[i * 4 + 2] = colour.blue;
	}
}

bool Visualisation::Initialise(int screenWidth, int screenHeight, std::string string)
{
	if (!HAPI.Initialise(screenWidth, screenHeight, string))
		return false;

	screenPntr = HAPI.GetScreenPointer();

	screenRect.left = 0;
	screenRect.right = screenWidth;
	screenRect.top = 0;
	screenRect.bottom = screenHeight;
	
	return true;
}

bool Visualisation::CreateSprite(const std::string& filename, const std::string& name, int numFrames, bool alpha)
{
	//creates a new sprite
	Sprite* newSprite = new Sprite;

	//if the new sprite cannot be loaded it will delete the sprite and return false
	if (!newSprite->Load(filename, numFrames, alpha))
	{
		delete newSprite;
		return false;
	}
	
	//if it successfully loads the sprite, it will assign that unique name as a key in the map to the new sprite
	spriteMap[name] = newSprite;
	return true;
}

void Visualisation::RenderSprite(const std::string& name, int posX, int posY, int frameNum)
{
	//searches through the sprite map to see if it can find the texture, if not it will throw an error
	if (spriteMap.find(name) != spriteMap.end())
	{
		//calls the sprites render function for that particular sprite
		spriteMap.at(name)->Render(screenRect, posX, posY, screenPntr, frameNum);
	}
	else
	{
		HAPI.UserMessage("Could not find the sprite you are looking for!", "Error", HAPI_ButtonType::eButtonTypeOk);
	}
	
	return;
}

Rectangle Visualisation::getCollisionRect(const std::string& name) const
{
	auto& it = spriteMap.find(name);
	if (it != spriteMap.cend())
	{
		return it->second->getRect();
	}
	return Rectangle(-1, -1);
}




