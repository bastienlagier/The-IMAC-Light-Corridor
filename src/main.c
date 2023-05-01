#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "game.h"

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "The IMAC Light Corridor";
static float aspectRatio = 1.0;

static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 1.;

// coordonnées z du dernier mur
static const float depth = 100; 


void onError(int error, const char* description) {
	fprintf(stderr, "GLFW Error: %s\n", description);
}

Point pos_actual;
float rectangleMove1;
float rectangleMove2;
Ball ball;


void onWindowResized(GLFWwindow* window, int width, int height) {
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if( aspectRatio > 1)
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
	glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
        }
    }
}


// gère les clics
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		printf("%f %f\n", xpos, ypos);

		if (ball.direction == NONE) {
			ball.direction = STRAIGHT;
		}
	}
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
	pos_actual.x=xpos;
	pos_actual.y=ypos;
}



int main(int argc, char** argv) {

    GLFWwindow* window;
	if (!glfwInit()) return -1;

    glfwSetErrorCallback(onError);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        glfwTerminate();
		return -1;
    }

    glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

	ball.direction = NONE;

    pos_actual.x=0.;
	pos_actual.y=0.;

	rectangleMove1 = 1.;
	rectangleMove2 = 1.5;

	bool bouncing = false;
	Point bouncing_point;
	bouncing_point.x = 0;
	bouncing_point.y = 0;

	int nbLife = 3;


    while (!glfwWindowShouldClose(window)) {

		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.0,0.0,0.0,0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		glfwSetCursorPosCallback(window, cursor_position_callback);

		glPushMatrix();

			float cursor_x, cursor_y;

			cursor_x = convertClic(pos_actual.x);
			if(pos_actual.x<40){
				cursor_x = convertClic(40.);
			}
			if(pos_actual.x>760){
				cursor_x = convertClic(760.);
			}

			cursor_y = convertClic(pos_actual.y);
			if(pos_actual.y<40){
				cursor_y = convertClic(40.);
			}
			if(pos_actual.y>460){
				cursor_y = convertClic(460.);
			}

			if (ball.direction == NONE) {
				ball.x = cursor_x;
				ball.y = cursor_y;
				ball.z = 0;
				bouncing_point.x = ball.x;
				bouncing_point.y = ball.y;
				drawBall(ball);
			}
			glTranslatef(cursor_x, cursor_y, 0);
			drawCursor();

		glPopMatrix();


		glPushMatrix();
			drawRectangleMove(rectangleMove1);
			drawRectangleMove(rectangleMove2);
			rectangleMove1 += 0.02;
			rectangleMove2 += 0.02;
			if(rectangleMove1>2)
				rectangleMove1=1;
			if(rectangleMove2>2)
				rectangleMove2=1;
		glPopMatrix();
        
		glPushMatrix();
			drawWalls();
		glPopMatrix();
		

		glPushMatrix();
			//glTranslatef(0.0, 0.0, 5.0);
			if (ball.direction != NONE) {
				drawBall(ball);
			}	
		glPopMatrix();

		float oldX, oldY, oldZ;
		oldX = ball.x;
		oldY = ball.y;
		oldZ = ball.z;

		switch (ball.direction) {
			case STRAIGHT:
			if (ball.x <= convertClic(200.+40.) && !bouncing) {
				ball.x += FRAMERATE_IN_SECONDS/2;
			}
			if (ball.x >= convertClic(600.-40.) && !bouncing) {
				ball.x -= FRAMERATE_IN_SECONDS/2;
			}
			if (ball.y <= convertClic(125.+40.) && !bouncing) {
				ball.y += FRAMERATE_IN_SECONDS/2;
			}
			if (ball.y >= convertClic(375.-40.) && !bouncing) {
				ball.y -= FRAMERATE_IN_SECONDS/2;
			}
			if (ball.x != oldX || ball.y != oldY) {
				break;
			}
			if (ball.z < convertClic(depth) && !bouncing) {
				ball.z += FRAMERATE_IN_SECONDS;
				break;
			}
			if (ball.z >= 0) {
				if (!bouncing) {
					bouncing = true;
				}
				ball.z -= FRAMERATE_IN_SECONDS/2;
			}
			if (ball.z != oldZ) {
				break;
			}
			oldX = ball.x;
			oldY = ball.y;
			if (bouncing) {
				if (ball.x <= bouncing_point.x) {
					ball.x += FRAMERATE_IN_SECONDS/2;
				}
				if (ball.x >= bouncing_point.x) {
					ball.x -= FRAMERATE_IN_SECONDS/2;
				}
				if (ball.y <= bouncing_point.y) {
					ball.y += FRAMERATE_IN_SECONDS/2;
				}
				if (ball.y >= bouncing_point.y) {
					ball.y -= FRAMERATE_IN_SECONDS/2;
				}
				
				if (ball.x == oldX && ball.y == oldY) {
					printf("ball %f %f | old %f %f\n", ball.x, ball.y, oldX, oldY);
					bouncing = false;
					if (ballHit(ball, cursor_x, cursor_y)) {
						// impact de la balle
						printf("heeyeey\n");
					}
					else {
						nbLife--;
						ball.direction = NONE;
					}
				}
			}
			break;
			default:
			break;
		}


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		if (elapsedTime < FRAMERATE_IN_SECONDS) {
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}

		if (nbLife <= 0) {
			// défaite, fin du jeu
			break;
		}
    }
    glfwTerminate();
    return 0;
}