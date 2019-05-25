
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>


class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char * fileName);
    static void Draw (SDL_Texture * tex, SDL_Rect src, SDL_Rect dest);

    static void init(SDL_Renderer * ren);
    static SDL_Renderer * renderer;
};

#endif //TEXTUREMANAGER_H
