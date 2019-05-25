

#ifndef SIDEBAR_H
#define SIDEBAR_H


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>
#include <string.h>

#include "SnakeGameSizes.h"


class SideBar{
public:

    SideBar(SDL_Renderer * ren);

    void update(int level, int score, int time);

    void render();

    void renderLost();


    void initBorders();
    void renderBorders();

private:

    int windowWidth;
    int windowHeight;


    SDL_Rect upBorder, downBorder, rightBorder, leftBorder;

    TTF_Font* arielFont;

    SDL_Renderer * renderer;

    char * message;
    SDL_Surface* surfaceMessage;
    SDL_Texture * messageTexture;
    SDL_Rect messageRect;

    SDL_Color messageColor;
};



#endif // SIDEBAR_H