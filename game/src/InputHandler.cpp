#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler()
{
	m_keystates = SDL_GetKeyboardState(NULL);
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//if (event.type = SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE){}
		switch (event.type)
		{
		case(SDL_KEYDOWN || SDL_KEYUP):
			updateKeyboardState();
			break;
		}
	}
}

void InputHandler::updateKeyboardState()
{
	SDL_PumpEvents();
}

bool InputHandler::isKeyDown(SDL_Scancode keyCode) const
{
	return m_keystates[keyCode];
}
