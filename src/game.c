#include "game.h"

float convertClic(float nbr){

	/*
	for(int i=0; i<taille; i++){
	if(WINDOW_WIDTH<WINDOW_HEIGHT)
		glVertex2f( ((points[i].x-(WINDOW_WIDTH/2))/(WINDOW_WIDTH/2)), -(points[i].y-(WINDOW_HEIGHT/2))/(WINDOW_WIDTH/2) );
	else
		glVertex2f( ((points[i].x-(WINDOW_WIDTH/2))/(WINDOW_HEIGHT/2)), -(points[i].y-(WINDOW_HEIGHT/2))/(WINDOW_HEIGHT/2) );
	}
	*/

	return -(nbr-400.)/800.;

}

void drawBall() {
    glColor3f(0.8, 1.0, 1.0);
    glPushMatrix();
        glScalef(0.05, 0.05, 0.05); //balle de taille 40
        drawSphere();
    glPopMatrix();
}

void drawWalls() {

	/*
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
    */

	glPushMatrix();

		glColor3f(21/255., 31/255., 66/255.);

		// Pour mettre en haut à gauche (0,0)
		glTranslatef(-0.5, 0.5, 0);

		// Plafond
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(1,0);
			glVertex2f(600./800.,-125./800.);
			glVertex2f(200./800.,-125./800.);
		glEnd();

		// Sol
		glTranslatef(0, -500./800., 0);
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(1,0);
			glVertex2f(600./800.,125./800.);
			glVertex2f(200./800.,125./800.);
		glEnd();

	glPopMatrix();



	glPushMatrix();

		glColor3f(11/255., 56/255., 135/255.);

		// Pour mettre en haut à gauche (0,0)
		glTranslatef(0.5, -0.125, 0);

		// Mur gauche
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(-200./800.,0.);
			glVertex2f(-200./800.,500./800.);
			glVertex2f(0,500./800.);
		glEnd();

		// Mur droit
		glTranslatef(-600./800.,0, 0);
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(-200./800.,0.);
			glVertex2f(-200./800.,500./800.);
			glVertex2f(0,500./800.);
		glEnd();

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



void drawCursor() {

	glPushMatrix();

		glColor3f(1,1,1);

		glBegin(GL_LINE_LOOP);
			glVertex2f(-40./800.,40./800.);
			glVertex2f(40./800.,40./800.);
			glVertex2f(40./800.,-40./800.);
			glVertex2f(-40./800.,-40./800.);
		glEnd();

	glPopMatrix();

}


void drawRectangleMove(float scale) {

	glPushMatrix();

		float color = scale - (1+scale/255);
		glColor3f(color,color,color);
		glTranslatef(0, 150./800., 0.);
		glScalef(scale, scale, scale);

		glBegin(GL_LINE_LOOP);
			glVertex2f(-200./800.,125./800.);
			glVertex2f(200./800.,125./800.);
			glVertex2f(200./800.,-125./800.);
			glVertex2f(-200./800.,-125./800.);
		glEnd();

	glPopMatrix();

}
