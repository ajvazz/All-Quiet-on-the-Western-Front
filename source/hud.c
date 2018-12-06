#include <GL/glut.h>
#include "../headers/scene.h"
#include "../headers/hud.h"

/* Promenljiva koriscena za predstavljanje preostalog zivota */
float remainingHealth = 0.0;

/* Poziva se crtanje bara, indikatora i health-barova */
void drawHUD() {

	/* Bar i indikator */
	glPushMatrix();
		glTranslatef(0, -7, 0);
		drawBar();
		drawPrecisionIndicator();
	glPopMatrix();

	/* Health barovi */
	glPushMatrix();
		drawHealthBar1();
		drawHealthBar2();
	glPopMatrix();
}

/* Racunanje jacine napada */
int getDamage(int indicatorPos) {

	/* Veoma precizan pogodak */
	if (-0.8 < indicatorPos && indicatorPos < 0.8)
		return 20;

	/* Srednje precizan pogodak */
	else if (-1.7 < indicatorPos && indicatorPos < 1.7)
		return 10; 

	/* Neprecizan pogodatk */
	else
		return 3;
}


void drawBar() {

	/* Crna ivica bara */
	glColor3ub(1, 1, 1);
	glBegin(GL_POLYGON);
		glVertex2f (-2.73,  0.35);
		glVertex2f ( 2.73,  0.35);
		glVertex2f ( 2.73, -0.35);
		glVertex2f (-2.73, -0.35);
	glEnd();

	/* Crvena podloga preko koje ce se crtati gradijent */
	glColor3ub(155, 0, 0);
	glBegin(GL_POLYGON);
		glVertex2f (-2.7,  0.3);
		glVertex2f ( 2.7,  0.3);
		glVertex2f ( 2.7, -0.3);
		glVertex2f (-2.7, -0.3);
	glEnd();

	/* Gradijent DO polovine bara */
	glBegin(GL_POLYGON);
		glVertex2f (-2.5,  0.3);
		glVertex2f (-2.5, -0.3);

		glColor3ub(0, 100, 0);

		glVertex2f ( 0.0, -0.3);
		glVertex2f ( 0.0,  0.3);
	glEnd();

	/* Gradijent OD polovine bara */
	glBegin(GL_POLYGON);
		glVertex2f ( 0.0,  0.3);
		glVertex2f ( 0.0, -0.3);

		glColor3ub(155, 0, 0);

		glVertex2f ( 2.5, -0.3);
		glVertex2f ( 2.5,  0.3);
	glEnd();
}

void drawPrecisionIndicator() {

	/* Indikator je obicna linija koja se pomera duz x-ose. */
	glColor3ub(0, 0, 0);

	glLineWidth(5);
	glBegin(GL_LINES);

		glVertex2f(indX1,  0.4);
		glVertex2f(indX2, -0.4);

	glEnd();
}

/* Health bar za prvog igraca */
void drawHealthBar1() {

	glPushMatrix();

		glTranslatef(-8, 9, 0);

		/* Ivica health bara */
		glColor3ub(1, 1, 1);
		glBegin(GL_POLYGON);
			glVertex2f (-1.23,  0.35);
			glVertex2f ( 1.23,  0.35);
			glVertex2f ( 1.23, -0.35);
			glVertex2f (-1.23, -0.35);
		glEnd();

		/* U pocetku je health bar pun - zelena boja */
		glColor3ub(0, 180, 0);

		/* Ako je igracu ostalo malo zivota, health bar postaje crven */
		if (player1.health <= 25)
			glColor3ub(180, 0, 0);

		/* Crta se popunjeni health bar */
		glBegin(GL_POLYGON);
			glVertex2f (-1.2,  0.3);
			glVertex2f (-1.2, -0.3);
			glVertex2f ( 1.2, -0.3);
			glVertex2f ( 1.2,  0.3);
		glEnd();

		/* Popunjenost health bara se racuna na osnovu preostalog zivota prvog igraca */
		remainingHealth = 2.4 * player1.health / 100.0;

		/* Od popunjenog health bara se oduzima onoliko koliko je jak napad */
		glColor3ub(1, 1, 1);
		glBegin(GL_POLYGON);
			glVertex2f (-1.2 + remainingHealth,  0.3);
			glVertex2f (-1.2 + remainingHealth, -0.3);
			glVertex2f ( 1.2, -0.3);
			glVertex2f ( 1.2,  0.3);
		glEnd();

	glPopMatrix();
}

/* Health bar za drugog igraca */
void drawHealthBar2() {

	glPushMatrix();

		glTranslatef(8, 9, 0);
		
		/* Ivica */
		glColor3ub(1, 1, 1);
		glBegin(GL_POLYGON);
			glVertex2f (-1.23,  0.35);
			glVertex2f ( 1.23,  0.35);
			glVertex2f ( 1.23, -0.35);
			glVertex2f (-1.23, -0.35);
		glEnd();

		/* U pocetku je health bar pun - zelena boja */
		glColor3ub(0, 180, 0);

		/* Ako je igracu ostalo malo zivota, health bar postaje crven */
		if (player2.health <= 25)
			glColor3ub(180, 0, 0);

		/* Crta se popunjeni health bar */
		glBegin(GL_POLYGON);
			glVertex2f (-1.2,  0.3);
			glVertex2f (-1.2, -0.3);
			glVertex2f ( 1.2, -0.3);
			glVertex2f ( 1.2,  0.3);
		glEnd();

		/* Popunjenost health bara se racuna na osnovu preostalog zivota drugog igraca */
		remainingHealth = 2.4 * player2.health / 100.0;

		/* Od popunjenog health bara se oduzima onoliko koliko je jak napad */
		glColor3ub(1, 1, 1);
		glBegin(GL_POLYGON);
			glVertex2f (-1.2 + remainingHealth,  0.3);
			glVertex2f (-1.2 + remainingHealth, -0.3);
			glVertex2f ( 1.2, -0.3);
			glVertex2f ( 1.2,  0.3);
		glEnd();

	glPopMatrix();
}