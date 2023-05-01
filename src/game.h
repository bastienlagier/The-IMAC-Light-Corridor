#include "3D_tools.h"

typedef struct Point Point;
struct Point{
	float x;
	float y;
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    STRAIGHT,
    NONE
};


typedef struct Ball {
    float x, y, z;
    enum Direction direction;
} Ball;

void drawBall(Ball ball);
void drawWalls();
void drawFrame();
void drawCursor();
float convertClic(float nbr);
void drawRectangleMove(float scale);