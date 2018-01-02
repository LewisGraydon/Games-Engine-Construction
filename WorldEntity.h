#pragma once

#include <HAPI_lib.h>
#include <algorithm>
#include "Visualisation.h"
#include "Rectangle.h"
#include "Vector2.h"

#include "WorldModel.h"

#include <iostream>

using namespace HAPISPACE;

enum class eSide 
{
	Player,
	Enemy,
	Neutral
};

class WorldEntity
{
public:
	//WorldEntity();
	WorldEntity(std::string spriteID) : spriteName(spriteID){}
	virtual ~WorldEntity();

	virtual void Update(WorldModel &world) = 0;
	virtual eSide getSide() const = 0;
	virtual void Render(Visualisation &cGraphics, float s);
	virtual void checkCollision(Visualisation &cGraphics, WorldEntity& other);

	void setPosition(Vector2 newPos)
	{
		lastPos = pos;
		pos = newPos;
	}

	Vector2 getPosition() const
	{
		return pos;
	}

	Vector2 getLastPosition() const
	{
		return lastPos;
	}

	void setExploded(bool status)
	{
		exploded = status;
	}

	bool getExploded() const
	{
		return exploded;
	}

	bool isAlive() const
	{
		return alive;
	}

	void setAlive(bool status)
	{
		alive = status;
	}

	void takeDamage(int value) 
	{
		health -= value;
		
		if (health <= 0)
		{
			alive = false;
		}
	}

protected:
	
	Vector2 pos;
	Vector2 lastPos;

	std::string spriteName;
	
	int damageInflicted{ 0 };
	float speed{ 1.0f };
	eSide side;

	int health{ 100 };
	bool alive{ true };
	bool exploded{ false };

	int currentFrameNum{ 0 };
};

