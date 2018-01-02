#pragma once

#include "WorldEntity.h"
#include "WorldModel.h"

constexpr int kFiringDelay{ 250 };

class PlayerEntity : public WorldEntity
{
public:
	PlayerEntity(std::string spriteID);
	~PlayerEntity();

	void Update(WorldModel &world) override final;

	float getPosX()
	{
		return pos.x;
	}

	float getPosY()
	{
		return pos.y;
	}

	virtual eSide getSide() const override final
	{
		return eSide::Player;
	}

	int getHealth()
	{
		return health;
	}

	void setScore(int val)
	{
		score += val;
	}

	void resetScore()
	{
		score = 0;
	}

	int getScore()
	{
		return score;
	}

private:

	DWORD nextFire{ 0 };
	int score{ 0 };
};

