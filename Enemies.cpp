///LIBARIES
#include <stdio.h>

///HEADERS
#include "Enemy.h"

/*----------------------------------------------------------------------------------------*/
//CONSTRUCTORS / DESTRUCTORS//
/*----------------------------------------------------------------------------------------*/
///INITIATE ENEMY
Enemy::Enemy(sf::Texture* textureSheet, sf::Vector2f newPos, short EnemyTypes)
{
	//enemy is alive
	isAlive = true;

	//Set texture to sprite
	shape.setTexture(*textureSheet);

	//Set enemyType
	types = EnemyTypes;

	//set currentFrame - Frame 1
	currentFrame = sf::IntRect(0, 0, 46, 32);

	//change texture frame based on enemy type
	if (types == 10) //ENEMYA
	{
		currentFrame.top = 0.f;
	}
	else if (types == 20) //ENEMYB
	{
		currentFrame.top = 32.f;
	}
	else if (types == 30) //ENEMYC
	{
		currentFrame.top = 64.f;
	}
	else if (types == 40) //ENEMYD
	{
		currentFrame.top = 96.f;
	}

	//Set Position
	shape.setPosition(newPos);

	//Resize the sprite
	shape.scale(1.f, 1.f);

	//set texture to currentFrame
	shape.setTextureRect(currentFrame);

	//set imageCountMax
	imageCountMax = imageCountMaxOriginal;

	//Start animationTimer
	animationTimer.restart();
}

Enemy::~Enemy()
{
}

/*----------------------------------------------------------------------------------------*/
//ACCESSORS//
/*----------------------------------------------------------------------------------------*/
///GRAB ENEMY GLOBALBOUNDS
sf::FloatRect Enemy::getGlobalBounds()
{
	return shape.getGlobalBounds();
}

///GRAB ENEMY POSITION
sf::Vector2f Enemy::getPos()
{
	return shape.getPosition();
}

///SET ENEMY POSITION
void Enemy::setPos(sf::Vector2f newPos)
{
	shape.setPosition(newPos);
}

///SET ENEMY POSITION
void Enemy::move(sf::Vector2f newPos)
{
	shape.move(newPos);
}

/*----------------------------------------------------------------------------------------*/
//PUBLIC FUNCTIONS//
/*----------------------------------------------------------------------------------------*/

///ENEMY ANIMATIONS
void Enemy::updateAnimations()
{
	if (isAlive)
	{
		deathDelay = 0;
		if (animationTimer.getElapsedTime().asMilliseconds() >= imageCountMax)
		{
			imageCount++;
			//when imageCount is 5 and not ENEMYD change to next frame
			if (imageCount == movementSpeed)
			{
				moving = true;
				
				if(types != 40)
				{
					currentFrame.left += 48.f;
					imageCount = 0;
				}
				
			}

			if (types == 40 && imageCount > 20)
			{
				imageCount = 0;
			}

			//if frame is bigger than 96 and not ENEMYD restart it
			if (currentFrame.left >= 96.f && types != 40)
			{
				currentFrame.left = 0.f;
			}

			//set texture new frame
			shape.setTextureRect(currentFrame);
			//restart timer
			animationTimer.restart();
		}
	}
	else
	{
		imageCount = 0;
		//set frame to death texture
		currentFrame.top = 128.f;
		currentFrame.left = 0.f;

		//set texture as the frame
		shape.setTextureRect(currentFrame);

		//Timer to destroy enemy in 20 milliseconds, allowing it to show death texture before destroying
		if (animationTimer.getElapsedTime().asMilliseconds() >= 1.f)
		{
			deathDelay++;
			animationTimer.restart();
		}

		if (deathDelay >= 20.f)
		{
			//Goto game.cpp -> update collision function -> bullet collision with enemy
			isDead = true;
			isAlive = true;
		}
	}
}

///UPDATE ENEMY
void Enemy::updateEnemy()
{
	updateAnimations();
	

	//Using a bool to change enemy direction based off collision with window
	//Enemy Movement is based off animation
	//Move Enemies

	//while enemy is not enemy D and is alive and moving
	while (moving && isAlive && types != 40)
	{
		if (!windowHit)
		{
			//Move Right
			shape.setPosition(sf::Vector2f((getPos().x + directionForce), getPos().y));

			moving = false;
			updateAnimations();
		}
		else
		{
			//Move Left
			shape.setPosition(sf::Vector2f((getPos().x - directionForce), getPos().y));

			moving = false;
			updateAnimations();
		}
	}

	//while enemy is enemy D move it
	if (types == 40)
	{
		shape.move(sf::Vector2f(1, 0));
		moving = false;
	}
}

///INCREASE SPEED
void Enemy::increaseSpeed(float speed)
{
	imageCount = 0;

	movementSpeed = movementSpeed - speed;

	if (movementSpeed < 1)
	{
		movementSpeed = 1;
	}

	speedIncreased = true;
}

///RENDER
void Enemy::renderTo(sf::RenderTarget* target)
{
	target->draw(shape);
}

