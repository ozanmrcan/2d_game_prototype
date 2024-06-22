#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class InputHandler 
{
public:
    InputHandler();
    void update();
    bool isKeyDown(SDL_Scancode key) const;
private:
    const Uint8* m_keystates;
    void updateKeyboardState();
};