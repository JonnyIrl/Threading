#include "Player.h"
#include <SDL_image.h>

static const float SCALE = 30.f;

// Constructor
Player::Player()
{

}

void Player::Init(SDL_Rect pRect)
{

	respawnPlayer = false;

	lastLeft = false;
	health = 5;
	direction = 0;
	initPos = pRect;
	myRect = pRect;

	source = { 0, 0, 64, 64 };
	playerSprite.Init("Assets/player.png", pRect, source);
	xPos = 0;
	score = 0;
}

//Doesnt work... Oh well... Who really cares?
void Player::Animate()
{

}

bool Player::Update()
{

	return true;
}

void Player::Move(InputHandler & input)
{
	if (xPos > 1200)
	{
		xPos = 0;
	}

	xPos += 10;
}

void Player::Draw()
{
	playerSprite.Draw();
	playerSprite.SetPosition(xPos, 0);
}

void Player::Respawn() {

}

void Player::Add_SubHealth(int amount) {
	health += amount;
}

SDL_Rect Player::getRectangle()
{
	return myRect;
}

int Player::GetScore()
{
	return score;
}
