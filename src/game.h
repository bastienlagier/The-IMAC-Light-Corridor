#include "3D_tools.h"

typedef struct Point Point;
struct Point{
	float x;
	float y;
};

void drawBall();
void drawWalls();
void drawFrame();
void drawCursor();
float convertClic(float nbr);
void drawRectangleMove(float scale);