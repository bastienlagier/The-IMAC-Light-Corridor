#include "game.h"

static float CENTI = 1./800.;

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
		glTranslatef(-400.*CENTI,400.*CENTI, 0);

		// Plafond
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(800.*CENTI,0.);
			glVertex2f(700.*CENTI,-80.*CENTI);
			glVertex2f(100.*CENTI,-80.*CENTI);
		glEnd();

		// Sol
		glTranslatef(0, -380.*CENTI, 0);
		glBegin(GL_POLYGON);
			glVertex2f(100*CENTI,0);
			glVertex2f(700.*CENTI,0.);
			glVertex2f(800.*CENTI,-80.*CENTI);
			glVertex2f(0.*CENTI,-80.*CENTI);
		glEnd();

	glPopMatrix();



	glPushMatrix();

		glColor3f(11/255., 56/255., 135/255.);

		// Pour placer mur à gauche (700,0)
		glTranslatef(-400.*CENTI,-60.*CENTI, 0);

		// Mur gauche
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(100.*CENTI,0.);
			glVertex2f(100.*CENTI,460.*CENTI);
			glVertex2f(0,460.*CENTI);
		glEnd();

		// Mur droit
		glTranslatef(700.*CENTI,0, 0);
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(100.*CENTI,0.);
			glVertex2f(100.*CENTI,460.*CENTI);
			glVertex2f(0,460.*CENTI);
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

	glColor3f(1,1,1);

	glBegin(GL_LINE_LOOP);
		glVertex2f(-40.*CENTI,40.*CENTI);
		glVertex2f(40.*CENTI,40.*CENTI);
		glVertex2f(40.*CENTI,-40.*CENTI);
		glVertex2f(-40.*CENTI,-40.*CENTI);
	glEnd();

}