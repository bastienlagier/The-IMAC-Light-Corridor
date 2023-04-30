#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "The IMAC Light Corridor";
static float aspectRatio = 1.0;

static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 1.;

void onError(int error, const char* description) {
	fprintf(stderr, "GLFW Error: %s\n", description);
}

Point pos_actual;

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

    pos_actual.x=0.;
	pos_actual.y=0.;

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

			cursor_x = -(pos_actual.x-400)/800;
			if(pos_actual.x<40){
				cursor_x = -(40.-400.)/800.;
			}
			if(pos_actual.x>760){
				cursor_x = -(760.-400.)/800.;
			}

			cursor_y = -(pos_actual.y-400)/800;
			if(pos_actual.y<40){
				cursor_y = -(40.-400.)/800.;
			}
			if(pos_actual.y>420){
				cursor_y = -(420.-400.)/800.;
			}

			glTranslatef(cursor_x, cursor_y, 0);
			drawCursor();

		glPopMatrix();

		glPushMatrix();
			//glTranslatef(0.0, 0.0, 5.0);
			drawBall();
		glPopMatrix();

        
		glPushMatrix();
			drawWalls();
		glPopMatrix();
		

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		if (elapsedTime < FRAMERATE_IN_SECONDS) {
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
    }
    glfwTerminate();
    return 0;
}