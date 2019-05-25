

#ifndef FOOD_H
#define FOOD_H

#include "SnakeGameSizes.h"

#include "SnakeObject.h"
#include "Obstacle.h"

#include "TextureManager.h"

#include <iostream>

#include <random>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <thread>

#include "vector"


class Food{
public:

    Food();

    void findNewLoc(std::vector<SnakeObject *> * snakeBody, std::vector<Obstacle *> * obstacles);

    SnakePoint getPoint(){ return location; }

    void update(std::vector<SnakeObject *> * snakeBody, std::vector<Obstacle *> * obstacles);
    void render();

    int getTimeOnScreen(){ return SDL_GetTicks() - foodStart; }

private:

    //==========================random engine ===========================

    // creates seed
    long seed = time(nullptr);
    // creates a random engine
    std::default_random_engine random_generator = std::default_random_engine(seed);

    // distribution on real and int numbers
    // uniform_real_distribution<float> attackOptions = uniform_real_distribution<float> (0.0f, 1.0f);
    std::uniform_int_distribution<int> intDistribution = std::uniform_int_distribution<int>(0, 10000);

    //===============================================================
    SnakePoint location;
    SDL_Texture* selfTexture;

    SDL_Rect srcRect;
    SDL_Rect destRect;

    Uint32 foodStart;

};



#endif