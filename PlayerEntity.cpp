#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string spriteID) : WorldEntity(spriteID)
{
	speed = 5;
	damageInflicted = 50;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update(WorldModel &world)
{	
	static const HAPI_TKeyboardData &kData = HAPI.GetKeyboardData();
	static const HAPI_TMouseData &mData = HAPI.GetMouseData();
	const HAPI_TControllerData &kControllerData = HAPI.GetControllerData(0);

	Vector2 pos{ getPosition() };

	//Keyboard controls

	if (kData.scanCode['W'] && pos.y > 0)
	{
		pos.y -= speed;
	}

	if (kData.scanCode['S'] && pos.y < 699) //699 is screenHeight - textureHeight
	{
		pos.y += speed;
	}

	if (kData.scanCode['A'] && pos.x > 0)
	{
		pos.x -= speed;
	}

	if (kData.scanCode['D'] && pos.x < 960) //960 is screenWidth - textureWidth
	{
		pos.x += speed;
	}

	if (mData.leftButtonDown)
	{	
		if (HAPI.GetTime() > nextFire)
		{
			world.fireBullet(getSide(), getPosition(), Vector2(0, -1), 10);
			nextFire = (HAPI.GetTime() + kFiringDelay);
		}
	}

	//Controller Input

	if (kControllerData.isAttached) //Makes sure a controller is attached first
	{

		if (kControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && pos.x < 960)
		{
			pos.x += speed;
		}

		if (kControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && pos.x > 0)
		{
			pos.x -= speed;
		}

		if (kControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE && pos.y > 0)
		{
			pos.y -= speed;
		}

		if (kControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE && pos.y < 699)
		{
			pos.y += speed;
		}

		if (kControllerData.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER])
		{
			world.fireBullet(getSide(), getPosition(), Vector2(0, -1), 10);
			nextFire = (HAPI.GetTime() + kFiringDelay);
		}
	}

	setPosition(pos);
}
