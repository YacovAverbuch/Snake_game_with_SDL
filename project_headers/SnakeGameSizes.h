//
// Created by Yacov Averbuch on 23/02/2019.
//

#ifndef SDL_TRAIL_NEW_SNAKEGAMESIZES_H
#define SDL_TRAIL_NEW_SNAKEGAMESIZES_H


enum Direction{
    RIGHT, LEFT, UP, DOWN
};

enum SnakeColor{
    HEAD,
    RED, BLUE, GREEN
};

// cont in m.s.
#define FOOD_MAX_TIME 6000

#define PIXELS_WIDTH 46
#define PIXELS_HEIGHT 30
#define BORDER_WIDTH 32


#define PIXEL_SIZE 16

#define SIDE_BAR_WIDTH 200


#define LEVEL_UP_SCORE 50

#define NUM_OF_OBSTACLES 8

#endif //SDL_TRAIL_NEW_SNAKEGAMESIZES_H
