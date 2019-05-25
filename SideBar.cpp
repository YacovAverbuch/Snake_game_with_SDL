
#include "SideBar.h"


SideBar::SideBar(SDL_Renderer * ren)
{
    initBorders();
    renderer = ren;

    if(TTF_Init() < 0) {
        std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
        return;
    }

    arielFont = TTF_OpenFont("assets/arial.ttf", 20); //this opens a font style and sets a size

    if (arielFont){
        // std::cout << "ariel font loaded successfully" << std::endl;
    }
    else{
        std::cout << "problem loading ariel: " << TTF_GetError() << "\n";
    }
    // color = black
    messageColor = {0, 0, 0, 255};


    // rect.x = 20, rect.y = 20, so it won't start the text on the borders
    messageRect = {20, 20, SIDE_BAR_WIDTH - 20, PIXELS_HEIGHT * 16 };
}


void SideBar::initBorders()
{
    // every rect is with x, y coordinates and width and heighet
    upBorder = SDL_Rect{SIDE_BAR_WIDTH, 0,
                        (PIXELS_WIDTH * PIXEL_SIZE) + (BORDER_WIDTH * 2), BORDER_WIDTH};
    downBorder = SDL_Rect{SIDE_BAR_WIDTH, (PIXELS_HEIGHT * PIXEL_SIZE) + BORDER_WIDTH,
                          (PIXELS_WIDTH * PIXEL_SIZE) + (BORDER_WIDTH * 2) , BORDER_WIDTH};
    leftBorder = SDL_Rect{SIDE_BAR_WIDTH, 0,
                          BORDER_WIDTH, (PIXELS_WIDTH * PIXEL_SIZE) + (BORDER_WIDTH * 2)};
    rightBorder = SDL_Rect{SIDE_BAR_WIDTH + (PIXELS_WIDTH * PIXEL_SIZE) + BORDER_WIDTH, 0,
                           BORDER_WIDTH, (PIXELS_WIDTH * PIXEL_SIZE) + (BORDER_WIDTH * 2)};
}


void SideBar::update(int level, int score, int time)
{
    std::string tmpMessage = ("\nLEVEL: " + std::to_string(level) + "\n\n" + "SCORE: "
            + std::to_string(score) +
            "\n\n\n\n\n\n" + "TIME: " + std::to_string(time));

    surfaceMessage = TTF_RenderText_Blended_Wrapped(arielFont, tmpMessage.c_str(), messageColor, 500);

    messageRect.w = surfaceMessage->w;
    messageRect.h = surfaceMessage->h;

    messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
}


void SideBar::renderBorders()
{
    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect(renderer, & upBorder);
    SDL_RenderFillRect(renderer, & downBorder);
    SDL_RenderFillRect(renderer, & leftBorder);
    SDL_RenderFillRect(renderer, & rightBorder);

}


void SideBar::renderLost()
{

}

void SideBar::render()
{
    renderBorders();
    SDL_RenderCopy(renderer, messageTexture, NULL, & messageRect);
}