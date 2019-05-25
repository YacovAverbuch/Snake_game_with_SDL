
#include "Obstacle.h"


enum Layout{
    HORIZONTAL, VERTICAL
};



Obstacle::Obstacle(SDL_Renderer * ren, std::vector<SnakeObject *> * body, Direction direction,
        SnakePoint foodLocation)
{

    renderer = ren;

    int texture_num = intDistribution(random_generator) % NUM_OF_OBSTACLES;
    Layout layout;

    switch (texture_num){
        case 0:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/vertical/gravel_obstacle_1.png");
            layout = VERTICAL;
            break;
        case 1:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/vertical/shrubbery_obstacle_1.png");
            layout = VERTICAL;
            break;
        case 2:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/vertical/snake_obstacle_1.png");
            layout = VERTICAL;
            break;
        case 3:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/vertical/wood_Shell_obstacle_1.png");
            layout = VERTICAL;
            break;
        case 4:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/horizontal/gravel_obstacle_2.png");
            layout = HORIZONTAL;
            break;
        case 5:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/horizontal/shrubbery_obstacle_2.png");
            layout = HORIZONTAL;
            break;
        case 6:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/horizontal/snake_obstacle_2.png");
            layout = HORIZONTAL;
            break;
        case 7:
            selfTexture = TextureManager::LoadTexture("assets/obstacles/horizontal/wood_Shell_obstacle_2.png");
            layout = HORIZONTAL;
            break;
    }

    int counter = 0;
    while (counter < 1000)
    {
        counter ++;
        pointA.xPos = intDistribution(random_generator) % PIXELS_WIDTH;
        pointA.yPos = intDistribution(random_generator) % PIXELS_HEIGHT;
        switch (layout){
            case VERTICAL:
                pointB.xPos = pointA.xPos + 3;
                pointB.yPos = pointA.yPos + 15;
                break;
            case HORIZONTAL:
                pointB.xPos = pointA.xPos + 15;
                pointB.yPos = pointA.yPos + 3;
        }

        for (SnakeObject * part : * body)
        {
            if (hasCollide(part->position)) continue;
        }
//        for(Obstacle * obstacle : * obstacles)
//        {
//            if (hasCollide(obstacle->hasCollide)) continue;
//        }
//
        if (hasCollide(foodLocation)) continue;
        // if it didn't continued, then it is a good place
        break;
    }

    if (counter == 1000)
    {
        std::cerr << "Couldn't find a legal place for food" << std::endl;
    }

    place.x = SIDE_BAR_WIDTH + BORDER_WIDTH + (pointA.xPos * PIXEL_SIZE);
    place.y = BORDER_WIDTH + (pointA.yPos * PIXEL_SIZE);

    switch (layout){
        case HORIZONTAL:
            place.w = 256;
            place.h = 64;
            break;
        case VERTICAL:
            place.w = 64;
            place.h = 256;
            break;
    }
    // std::cerr << "Obstacle pointA.x: " << pointA.xPos << " Obstacle pointB.y: " << pointA.yPos << std::endl;
}



void Obstacle::render()
{
    SDL_RenderCopy(renderer, selfTexture, NULL, & place);
}