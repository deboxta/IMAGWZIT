#pragma once

class CollisionCircle
{
public:	
	CollisionCircle();
	CollisionCircle(const float radius, const float posX, const float posY);
	bool checkCollision(const CollisionCircle &otherCircle) const;

	float getRadius() const;
	float getPosX() const;
	float getPosY() const;

private:
	float radius;
	float posX;
	float posY;
};


