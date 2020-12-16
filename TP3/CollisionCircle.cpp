#include "CollisionCircle.h"

CollisionCircle::CollisionCircle()
{
	this->radius = 1;
	this->posX = 0;
	this->posY = 0;
}

CollisionCircle::CollisionCircle(const float radius, const float posX, const float posY)
{
	this->radius = radius;
	this->posX = posX;
	this->posY = posY;
}

bool CollisionCircle::checkCollision(const CollisionCircle &otherCircle) const
{
	float lineX = this->posX - otherCircle.posX;
	float lineY = this->posY - otherCircle.posY;

	float distance = lineX * lineX + lineY * lineY;
	float totalRadius = this->radius + otherCircle.radius;
	
	//À la place de faire la racine carré de la distance, on met la somme des rayons au carré; plus économe.
	totalRadius *= totalRadius;
	
	//Deux cercles qui se touchent sont considérées en collision
	if (distance <= totalRadius)
	{
		return true;
	}

	return false;
}

float CollisionCircle::getRadius() const
{ 
	return radius; 
}

float CollisionCircle::getPosX() const
{
	return posX; 
}

float CollisionCircle::getPosY() const
{ 
	return posY; 
}
