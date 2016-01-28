#ifndef PLAYER2_H
#define PLAYER2_H

#include <iostream> 
#include "SDL.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputHandler.h"

class Player2
{
public:
	Player2();
	void Init(SDL_Rect);
	bool Update();
	void Draw();
	void Move(InputHandler & input);
	void Animate();
	void Respawn();
	void Add_SubHealth(int amount);
	int frame;
	SDL_Rect getRectangle();
	int score;
	int GetScore();
	bool respawnPlayer;

private:
	int health;
	SDL_Rect initPos;
	SDL_Rect myRect;
	SDL_Rect source;
	int spriteOffset;

	Sprite playerSprite;
	int direction;
	bool canJump;
	bool lastLeft;
	float xPos;
};

#endif