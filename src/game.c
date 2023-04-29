#include "game.h"

void drawBall() {
    glColor3f(0.8, 1.0, 1.0);
    glPushMatrix();
        drawSphere();
    glPopMatrix();
}

void drawWalls() {
    glColor3f(0., 0., 1.);
    glPushMatrix();
	    // glScalef(10., 10. , 10.);
        drawRectangle(12, 6);
    glPopMatrix();
}

void drawFrame() {
	// dessin du repère
	glBegin(GL_LINES);
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(10 ,0.,0.);
		glColor3f(0.,1.,0.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,10,0.);
		glColor3f(0.,0.,1.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,0.,10);
	glEnd();
}