//
// Created by Yacov Averbuch on 18/02/2019.
//

#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

// #include "SnakeGame.h"

#include "SnakePoint.h"
#include "SnakeGameSizes.h"

class SnakeObject
{
public:

    SnakeObject(){}
    SnakeObject(SnakeColor color, int xInit, int yInit);
    ~SnakeObject() {}

    void update(SnakeObject * front);
    void updateHead(Direction direction);

    void render();

    int getX(){ return position.xPos; }
    int getY(){ return position.yPos; }

    SnakePoint position;

private:

    SDL_Texture* selfTexture;
    SnakeColor pieceColor;



    SDL_Rect srcRect;
    SDL_Rect destRect;
};

#endif //SnakeObject_H
