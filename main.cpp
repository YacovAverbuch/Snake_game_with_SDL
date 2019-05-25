

#include <iostream>
#include "SDL.h"

#include "SnakeGameSizes.h"
#include "SnakeGame.h"

#ifdef main
# undef main
#endif /* main */


int main (int argc, char * argv[])
{
    SnakeGame * snakeGame = new SnakeGame();
    snakeGame->init("SnakeGame", false);

    snakeGame->run();
    snakeGame->clean();
    delete snakeGame;

    std::cout << "Game Cleaned\n";
	return 0;
}
