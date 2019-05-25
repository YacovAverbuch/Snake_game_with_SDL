//
// Created by Yacov Averbuch on 18/02/2019.
//

#include "SnakeObject.h"
#include "TextureManager.h"

#include "SnakeGame.h"


/**
 *
 * @param color
 * @param xInit pixel on Snake screen to start on
 * @param yInit pixel on Snake screen to start on
 */
SnakeObject::SnakeObject(SnakeColor color, int xInit, int yInit)
{
    pieceColor = color;
    switch (pieceColor)
   {
       case HEAD:
           selfTexture = TextureManager::LoadTexture("assets/SnakeHead.png");
           break;
        case GREEN:
            selfTexture = TextureManager::LoadTexture("assets/green.png");
            break;
        case BLUE:
            selfTexture = TextureManager::LoadTexture("assets/blue.png");
            break;
        case RED:
            selfTexture = TextureManager::LoadTexture("assets/red.png");
            break;
        default:
            break;
    }

    position.xPos = xInit;
    position.yPos = yInit;

    // std::cerr << "x: " << position.xPos << " y: " << position.yPos << std::endl;

    srcRect.h = PIXEL_SIZE;
    srcRect.w = PIXEL_SIZE;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = PIXEL_SIZE;
    destRect.w = PIXEL_SIZE;
    destRect.x = SIDE_BAR_WIDTH + BORDER_WIDTH + (xInit * PIXEL_SIZE);
    destRect.y = BORDER_WIDTH + (yInit * PIXEL_SIZE);
}


/**
 * This function get only parts witch are not the head of the snake
 *
 * @param front the object in front of this object
 */
void SnakeObject::update(SnakeObject * front)
{
    position = front->position;

    destRect.x = front->destRect.x;
    destRect.y = front->destRect.y;
}


void SnakeObject::updateHead(Direction direction)
{
    switch (direction){
        case UP:
            position.yPos -= 1;
            destRect.y -= 16;
            break;
        case DOWN:
            position.yPos += 1;
            destRect.y += 16;
            break;
        case RIGHT:
            position.xPos += 1;
            destRect.x += 16;
            break;
        case LEFT:
            position.xPos -= 1;
            destRect.x -= 16;
            break;
    }
}


void SnakeObject::render()
{
    SDL_RenderCopy(SnakeGame::renderer, selfTexture, & srcRect, & destRect);
}


