#include "SDL.h"
#include "SDL_thread.h"
#include <string>
#include "Renderer.h"
#include "Player.h"
#include "Player2.h"
#include "InputHandler.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1248;			//SDL
const int SCREEN_HEIGHT = 704;			//SDL

//methods
void Init();
void DrawGame();
void UpdateGame();
void fpsinit();
void fpsthink();
int Thread(void* ptr);
int ThreadTwo(void* ptr);
float CalculateFPS();

// Player
SDL_Rect myRect{ 0, 0, 64, 64 };
Player player;

// Player2
SDL_Rect myRect2{ 0, 0, 64, 64 };
Player2 player2;

InputHandler inputHandler = InputHandler();
SDL_mutex* mut;

//Data access semaphore
SDL_sem* gDataLock = NULL;

// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 5

// An array to store frame times:
Uint32 frametimes[FRAME_VALUES];

// Last calculated SDL_GetTicks
Uint32 frametimelast;

// total frames rendered
Uint32 framecount;

// the value you want
float framespersecond;

// This function gets called once on startup.
void fpsinit() {

	// Set all frame times to 0ms.
	memset(frametimes, 0, sizeof(frametimes));
	framecount = 0;
	framespersecond = 0;
	frametimelast = SDL_GetTicks();

}

void fpsthink() {

	Uint32 frametimesindex;
	Uint32 getticks;
	Uint32 count;
	Uint32 i;

	// frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
	// This value rotates back to 0 after it hits FRAME_VALUES.
	frametimesindex = framecount % FRAME_VALUES;

	// store the current time
	getticks = SDL_GetTicks();

	// save the frame time value
	frametimes[frametimesindex] = getticks - frametimelast;

	// save the last frame time for the next fpsthink
	frametimelast = getticks;

	// increment the frame count
	framecount++;

	// Work out the current framerate

	// The code below could be moved into another function if you don't need the value every frame.

	// I've included a test to see if the whole array has been written to or not. This will stop
	// strange values on the first few (FRAME_VALUES) frames.
	if (framecount < FRAME_VALUES) {

		count = framecount;

	}
	else {

		count = FRAME_VALUES;

	}

	// add up all the values and divide to get the average frame time.
	framespersecond = 0;
	for (i = 0; i < count; i++) {

		framespersecond += frametimes[i];

	}

	framespersecond /= count;

	// now to make it an actual frames per second value...
	framespersecond = 1000.f / framespersecond;

}


int Thread(void* ptr)
{
	unsigned int result = 0;
	Uint32 update, elapsed = 0;
	update = 1000;

	while (true)
	{
		//Lock
		SDL_SemWait(gDataLock);
		std::cout << "Semephore Locked 1" << std::endl;
		player.Move(inputHandler);
		SDL_Delay(100);
		std::cout << "Semephore Updating 1" << std::endl;

		//Unlock
		SDL_SemPost(gDataLock);

		std::cout << "Semephore unLocked 1" << std::endl;
	}
	return result;
}

int ThreadTwo(void* ptr)
{
	unsigned int result = 0;
	Uint32 update, elapsed = 0;
	update = 1000;

	while (true)
	{
		//Lock
		SDL_SemWait(gDataLock);
		std::cout << "Semephore Locked 2" << std::endl;
		player2.Move(inputHandler);
		SDL_Delay(100);
		std::cout << "Semephore Updating 2" << std::endl;
		//Unlock
		SDL_SemPost(gDataLock);
		std::cout << "Semephore unLocked 2" << std::endl;
	}
	return result;
}



int main(int argc, char* args[])
{
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//Create window
	window = SDL_CreateWindow("SDL Threading", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create Renderer for the Window
		if (!Renderer::GetInstance()->Init(window, SCREEN_WIDTH, SCREEN_HEIGHT))
		{
			return 0;
		}

		bool quit = false;
		Init();



		SDL_Thread* id = SDL_CreateThread(Thread, "MoveThread", (void*)NULL);
		SDL_Delay(100);
		SDL_Thread* id2 = SDL_CreateThread(ThreadTwo, "MoveThreadTwo", (void*)NULL);


		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0) 
			{

			}

			UpdateGame();
			DrawGame();
			fpsthink();
			//printf("%f\n", framespersecond);
		}

		//Wait for threads to finish
		SDL_WaitThread(id, NULL);
		SDL_WaitThread(id2, NULL);

		return 0;
	}
}


void Init()
{
	player.Init(myRect);
	player2.Init(myRect2);
	//mut = SDL_CreateMutex();
	fpsinit();
}

void DrawGame()
{
	Renderer::GetInstance()->ClearRenderer();
	player.Draw();
	player2.Draw();
	Renderer::GetInstance()->RenderScreen();
}

void DrawMenu()
{

}

void DrawLeaderboard()
{

}

bool UpdateMenu(SDL_Event e)
{
	return true;
}

void UpdateGame()
{

}

void Reset()
{

}

void ClearPointers()
{

}
