

#ifndef OBSTACLE_H
#define OBSTACLE_H


#include "SnakeGameSizes.h"

#include "SnakeObject.h"
#include "TextureManager.h"

#include <iostream>

#include "vector"

#include <random>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <thread>


class Obstacle
{
private:
    // in Snake pixels
    SnakePoint pointA, pointB;

    SDL_Texture* selfTexture;
    SDL_Rect src, place;
    SDL_Renderer * renderer;

    //==========================random engine ===========================

    // creates seed
    long seed = time(nullptr);
    // creates a random engine
    std::default_random_engine random_generator = std::default_random_engine(seed);

    // distribution on real and int numbers
    // uniform_real_distribution<float> attackOptions = uniform_real_distribution<float> (0.0f, 1.0f);
    std::uniform_int_distribution<int> intDistribution = std::uniform_int_distribution<int>(0, 10000);


public:
    Obstacle(SDL_Renderer * ren, std::vector<SnakeObject *> * body, Direction direction, SnakePoint foodLocation);

    bool hasCollide(SnakePoint point)
    {
        return (point.xPos >= pointA.xPos and point.xPos <= pointB.xPos
            and point.yPos >= pointA.yPos and point.yPos <= pointB.yPos);
    }

    void render();
};




#endif  // OBSTACLE_H

