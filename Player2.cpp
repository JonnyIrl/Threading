#include "Player2.h"
#include <SDL_image.h>

static const float SCALE = 30.f;

// Constructor
Player2::Player2()
{

}

void Player2::Init(SDL_Rect pRect)
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
void Player2::Animate()
{

}

bool Player2::Update()
{

	return true;
}

void Player2::Move(InputHandler & input)
{
	if (xPos > 1200)
	{
		xPos = 0;
	}

	xPos += 10;
}

void Player2::Draw()
{
	playerSprite.Draw();
	playerSprite.SetPosition(xPos, 100);
}

void Player2::Respawn() {

}

void Player2::Add_SubHealth(int amount) {
	health += amount;
}

SDL_Rect Player2::getRectangle()
{
	return myRect;
}

int Player2::GetScore()
{
	return score;
}
