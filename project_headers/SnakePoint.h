


#ifndef SNAKE_POINT
#define SNAKE_POINT



class SnakePoint{
public:
    bool operator== (SnakePoint other)
    {
        return (xPos == other.xPos) and (yPos == other.yPos);
    }

    int xPos, yPos;
};


#endif