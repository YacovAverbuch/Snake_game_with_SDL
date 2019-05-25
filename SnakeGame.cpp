//
// Created by Yacov Averbuch on 17/02/2019.
//

#include "project_headers\SnakeGame.h"
#include "project_headers\TextureManager.h"
#include "project_headers\SnakeObject.h"


#include "project_headers\SnakeGameSizes.h"


SnakeObject * player;
SDL_Renderer * SnakeGame::renderer = nullptr;

SnakeGame::SnakeGame()
{
    bar = nullptr;
    food = nullptr;
}

SnakeGame::~SnakeGame()
{}

void SnakeGame::init(const char * title, bool fullScreen)
{
    level = 1;
    score = 0;
    direction = RIGHT;

    int flags = 0;
    if (fullScreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // std::cout << "Initialised successfully.. \n";
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SIDE_BAR_WIDTH + (2 * BORDER_WIDTH) + (PIXELS_WIDTH * PIXEL_SIZE),
                (BORDER_WIDTH * 2) + (PIXELS_HEIGHT * PIXEL_SIZE),
                flags);
        if (window)
        {
            // std::cout << "Window created .. \n";
        }

        // create a renderer (prosesor) to proses the changes of the objects
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            // set the BG color to white, so it will draw everything
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            // std::cout << "renderer created.. \n";
        }
        TextureManager::init(renderer);
        isRunning = true;
    }
    else{
        isRunning = false;
    }
    initSnakeBody();
    bar = new SideBar(renderer);
    food = new Food();
    food->findNewLoc(& snakeBody, & obstacles);
}


void SnakeGame::initSnakeBody(){

    snakeBody = std::vector<SnakeObject *>(1);
    // the head is in the snakeBody[0]
    snakeBody[0] = new SnakeObject(HEAD, 4, 10);

    for (int i = 1; i < 6; i ++)
    {
        SnakeObject * newOb = addPart(4, 10 - i);
        snakeBody.push_back(newOb);
    }
}



SnakeObject * SnakeGame::addPart(int x, int y){
    SnakeColor curColor;
    switch (snakeBody.size() % 3)
    {
        case 0:
            curColor = RED;
            break;
        case 1:
            curColor = GREEN;
            break;
        case 2:
            curColor = BLUE;
            break;
    }
    return new SnakeObject(curColor, x, y);
}


void SnakeGame::levelUp()
{
    level += 1;
    // add 0.5 frames per second. the maximum is 15 FPS
    FPS = (FPS + 0.5 < 15.0) ? (FPS + 0.5) : 15.0;
    frameDelay = 1000 / FPS;
}


void SnakeGame::run(){

    // unsigned int with 32 bit long (until 2 ^ 31)
    Uint32 frameStart;
    int frameTime;

    while(isRunning)
    {
        // return MS that passed from the init of SDK
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();
        checkCollision();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            if (! toSpeedUp){ SDL_Delay(frameDelay - frameTime); }
            else{
                SDL_Delay((frameDelay - frameTime) / 6);
            }
        }
    }

    SDL_Delay(2500);
    // in case of lost
    render();
}


void SnakeGame::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(& event);

    switch (event.type){
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_SPACE){ toSpeedUp = false; }
            SDL_PollEvent(& event);
    }

    switch (event.type) {

        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            /* Checks the current press */
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    if (direction != RIGHT) direction = LEFT;
                    break;

                case SDLK_RIGHT:
                    if (direction != LEFT) direction = RIGHT;
                    break;

                case SDLK_UP:
                    if (direction != DOWN) direction = UP;
                    break;

                case SDLK_DOWN:
                    if (direction != UP) direction = DOWN;
                    break;
                case SDLK_SPACE:
                    toSpeedUp = true;
                    break;
            }
        default:
            break;
    }
}


void SnakeGame::update()
{
    bool toAddPart = false;

    if (food->getPoint() == snakeBody[0]->position)
    {
        // std::cout << "Eaten\n";
        food->findNewLoc(& snakeBody, & obstacles);
        score = score + 3 + (1 - (food->getTimeOnScreen() / FOOD_MAX_TIME)) * 3 * level;
//        Obstacle * newObstacle = new Obstacle(renderer, & snakeBody, direction, food->getPoint());
//        obstacles.push_back(newObstacle);
        if (1 + score / LEVEL_UP_SCORE > level){
            levelUp();
        }

        toAddPart = true;
    }
    food->update(& snakeBody, & obstacles);

    bar->update(level, score, SDL_GetTicks() / 1000);

    SnakePoint tailLoc = snakeBody[snakeBody.size() - 1]->position;
    for (int i = snakeBody.size() - 1; i > 0 ; i --)
    {
        (snakeBody[i])->update(snakeBody[i - 1]);
    }


    if (toAddPart)
    {
        // new tail location
        SnakeObject * newTail = addPart(tailLoc.xPos, tailLoc.yPos);
        snakeBody.push_back(newTail);
    }

    snakeBody[0]->updateHead(direction);
}


void SnakeGame::render()
{
    // Set render color ( when we will do 'clear' it will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (SnakeObject * part : snakeBody ) part->render();
    for (Obstacle * ob : obstacles) ob->render();

    bar->render();
    food->render();

    if (! isRunning) bar->renderLost();

    SDL_RenderPresent(renderer);
}


void SnakeGame::checkCollision()
{
    int headX = snakeBody[0]->getX();
    int headY = snakeBody[0]->getY();

    for (int i = 1; i < snakeBody.size(); i ++)
    {
        if (snakeBody[i]->position == snakeBody[0]->position)
        {
            std::cerr << "Collision with part " << i << std::endl;
            isRunning = false;
        }
    }

    if ((headX < 0) or (headX >= PIXELS_WIDTH) or (headY < 0) or (headY >= PIXELS_HEIGHT))
    {
        std::cerr << "Boarders Colision: X: " << headX << " Y: " << headY << "\n";
        isRunning = false;
    }
//    for (Obstacle * ob : obstacles){
//        if(){
//        }
//    }
}


void SnakeGame::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    delete bar;

    for (SnakeObject * object : snakeBody) { delete object; }
    for (Obstacle * ob : obstacles) delete ob;
}



