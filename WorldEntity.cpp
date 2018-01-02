#include "WorldEntity.h"


bool canCollideWith(eSide thisSide, eSide otherSide)
{
	if (thisSide != eSide::Neutral && otherSide != eSide::Neutral && thisSide != otherSide)
		return true;

	return false;
}

WorldEntity::~WorldEntity()
{
}

void WorldEntity::Render(Visualisation &cGraphics, float s)
{
	Vector2 interpolatedPos{ lastPos + (pos - lastPos) * s };

	cGraphics.RenderSprite(spriteName, (int)interpolatedPos.x, (int)interpolatedPos.y, currentFrameNum);
}

void WorldEntity::checkCollision(Visualisation &cGraphics, WorldEntity &other)
{
	if (!alive || !other.alive)
		return;

	if (!canCollideWith(getSide(), other.getSide()))
		return;

	Rectangle thisRect{ cGraphics.getCollisionRect(spriteName) };

	int width{ thisRect.width() };

	thisRect.left += width / 10;
	thisRect.right -= width / 10;

	Rectangle otherRect{ cGraphics.getCollisionRect(other.spriteName) };

	thisRect.Translate((int)pos.x, (int)pos.y);
	otherRect.Translate((int)other.pos.x, (int)other.pos.y);

	if (!thisRect.CompletelyOutside(otherRect))
	{
		//collision stuff
		takeDamage(other.damageInflicted);
		other.takeDamage(damageInflicted);

		while (!thisRect.CompletelyOutside(otherRect))
		{
			Vector2 direction{lastPos - pos};
			direction.NormaliseInPlace();
			pos += direction;
			thisRect.Translate((int)direction.x, (int)direction.y);

			Vector2 otherDirection{ other.lastPos - other.pos };
			otherDirection.NormaliseInPlace();
			other.pos += otherDirection;
			otherRect.Translate((int)otherDirection.x, (int)otherDirection.y);
		}
	}
}
