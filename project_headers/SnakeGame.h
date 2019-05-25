//
// Created by Yacov Averbuch on 17/02/2019.
//

#ifndef SNAKEGAME_H
#define SNAKEGAME_H


#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


#include "SnakeObject.h"
#include "SideBar.h"
#include "Food.h"
#include "Obstacle.h"

#include "SnakeGameSizes.h"


class SnakeGame
{
public:
    SnakeGame();
    ~SnakeGame();

    void init(const char * title, bool fullScreen);

	void initSnakeBody();

    void update();
    void handleEvents();

    void render();
    void clean();

    void levelUp();

    bool running() { return isRunning; }
    static SDL_Renderer * renderer;
    void initSideTextBar();
    void run();

    void checkCollision();

    SnakeObject *  addPart(int x, int y);

private:
    bool isRunning;
    SDL_Window * window;
    SideBar * bar;

    Direction direction;
    // frames per second
    float FPS = 6;
    // 1000 milly seconds divide by amount of FPS
    int frameDelay = 1000 / FPS;

    bool toSpeedUp;

    std::vector<Obstacle *> obstacles;
    std::vector<SnakeObject *> snakeBody;
    Food * food;


    int level, score;

	// count in num of frame the food is on the screen
	// 60 FPS
    int foodStartTime = 600;

};


#endif // SNAKEGAME_H
