#include "InputHandler.h"

InputHandler::InputHandler()
{

}

bool InputHandler::CheckInput(SDL_Keycode key, SDL_Event event) {
	if (event.key.keysym.sym == key)
		return true;
	else
		return false;
}