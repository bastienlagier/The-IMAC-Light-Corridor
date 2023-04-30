#include "game.h"

void drawBall() {
    glColor3f(0.8, 1.0, 1.0);
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        drawSphere();
    glPopMatrix();
}

void drawWalls() {
    glPushMatrix();
		glColor3f(63./255., 72./255., 204./255.);
	    glTranslatef(0.0, 0.0, 10.0);
        drawRectangle(3.0, 2.0);

		glColor3f(16./255., 19./255., 58./255.);
		glTranslatef(0.0, -4., 0.0);
		glRotatef(90, 1., 0., 0.);
		drawRectangle(6.0, 12.0);

		glColor3f(32./255., 38./255., 119./255.);
		glTranslatef(0.0, 16., 0.0);
		// glRotatef(-90, 1., 0., 0.);
		glRotatef(-90, 1., 0., 0.);

		glRotatef(180, 0., 0., 1.);
		drawRectangle(6.0, 12.0);



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