
#include "Food.h"



Food::Food()
{
    selfTexture = TextureManager::LoadTexture("assets/SnakeFood.png");;

    srcRect.h = PIXEL_SIZE;
    srcRect.w = PIXEL_SIZE;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = PIXEL_SIZE;
    destRect.w = PIXEL_SIZE;

    foodStart = SDL_GetTicks();

    location.xPos = 10;
    location.yPos = 10;
    destRect.x = SIDE_BAR_WIDTH + BORDER_WIDTH + (location.xPos * PIXEL_SIZE);
    destRect.y = BORDER_WIDTH + (location.yPos * PIXEL_SIZE);
}



void Food::findNewLoc(std::vector<SnakeObject *> * snakeBody, std::vector<Obstacle *> * obstacles)
{
    int counter = 0;
    while (counter < 1000)
    {
        counter ++;
        location.xPos = intDistribution(random_generator) % PIXELS_WIDTH;
        location.yPos = intDistribution(random_generator) % PIXELS_HEIGHT;
        for (SnakeObject * part : * snakeBody)
        {
            if (part->position == location) continue;
        }
        for(Obstacle * obstacle : * obstacles)
        {
            if (obstacle->hasCollide(location)) continue;
        }
        // if it didn't continued, then it is a good place
        break;
    }


    if (counter == 1000)
    {
        std::cerr << "Couldn't find a legal place for food" << std::endl;
    }



    destRect.x = SIDE_BAR_WIDTH + BORDER_WIDTH + (location.xPos * PIXEL_SIZE);
    destRect.y = BORDER_WIDTH + (location.yPos * PIXEL_SIZE);

    foodStart = SDL_GetTicks();

//    std::cerr << "food x: " << location.xPos << " food y: " << location.yPos << std::endl;
}

void Food::update(std::vector<SnakeObject *> * snakeBody, std::vector<Obstacle *> * obstacles)
{
    if((foodStart + FOOD_MAX_TIME) < SDL_GetTicks())
    {
        findNewLoc(snakeBody, obstacles);
    }
}

void Food::render()
{
    SDL_RenderCopy(TextureManager::renderer, selfTexture, & srcRect, & destRect);
}


