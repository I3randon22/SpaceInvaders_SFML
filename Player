///LIBARIES
#include <stdio.h>

///HEADERS
#include "Player.h"

/*----------------------------------------------------------------------------------------*/
//CONSTRUCTORS / DESTRUCTORS//
/*----------------------------------------------------------------------------------------*/
Player::Player(sf::Texture* textureSheet)
{
	//set texture to player
	shape.setTexture(*textureSheet);
	currentFrame = sf::IntRect(0, 0, 60, 32);
	shape.setTextureRect(currentFrame);

	//set texture and position to lives
	for (int i = 0; i < playerLives; i++)
	{
		lives.push_back(sf::Sprite(*textureSheet));
		lives[i].setTextureRect(sf::IntRect(0, 0, 60, 32));
		lives[i].setPosition(sf::Vector2f(100 + (i * 80), 950));
	}

	animationTimer.restart();
	bulletCounter = bulletCounterMax;
}

Player::~Player()
{
}

/*----------------------------------------------------------------------------------------*/
//ACCESSORS//
/*----------------------------------------------------------------------------------------*/

///Get Players Position
const sf::Vector2f& Player::getPos() const
{
	return shape.getPosition();
}

///Get Players Global Bounds
sf::FloatRect Player::getGlobalBounds()
{
	return shape.getGlobalBounds();
}

///Check If Player Can Shoot
const bool Player::canShoot()
{
	//if bullet counter is smaller than bullet counter max return true and set counter to 0, else return false.
	if (bulletCounter >= bulletCounterMax)
	{
		bulletCounter = 0.f;
		return true;
	}

	return false;
}

/*----------------------------------------------------------------------------------------*/
//PUBLIC FUNCTIONS//
/*----------------------------------------------------------------------------------------*/
///Set Players Position
void Player::setPos(sf::Vector2f newPos)
{
	//Spawn position
	shape.setPosition(newPos);
}

///Move Player
void Player::move(const float directionX, const float directionY)
{
	//Movement
	shape.move(movementSpeed * directionX, movementSpeed * directionY);
}

///Update Shooting
void Player::updateShoot()
{
	if (bulletCounter < bulletCounterMax)
	{
		bulletCounter += 0.5f; //change bullet frequency - normal is 0.5
	}
}

///Update Player
void Player::updatePlayer()
{
	updateShoot();

	//if hit by bullet play death animation, prevent player from moving
	if (isHit)
	{
		updateAnimations();
		movementSpeed = 0;
	}
	else //if not hit by bullet
	{
		//set player frame back to first frame
		currentFrame.left = 0;
		shape.setTextureRect(currentFrame);

		//player can move again
		movementSpeed = originalSpeed;
	}

	//if imagecount is bigger than or equal to 20 (this occurs when player is hit by bullet, the image count is for the death animation)
	if (imageCount >= 20)
	{
		//take away a life
		playerLives--;
		isHit = false;
		imageCount = 0;
	}
}

///Update Player Animations
void Player::updateAnimations()
{
	//Death Animation
	if (animationTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		//increase counter by 1
		imageCount++;

		//change frame / Image frame = 60 width, 32 height
		currentFrame.left += 60.f;

		//switch between last two death frames
		if (currentFrame.left >= 300.f)
		{
			currentFrame.left = 180;
		}
		animationTimer.restart();

		//set texture as the frame
		shape.setTextureRect(currentFrame);
	}
}

///Render Player To Screen
void Player::renderTo(sf::RenderTarget* target)
{
	target->draw(shape);

	for (int i = 0; i < playerLives; i++)
	{
		target->draw(lives[i]);
	}
}



