#include <GL/glut.h>
#include <math.h>

#include "mainScene.h"
#include "mainTexture.h"

static GLuint names[2];

/* Funkcija koja namesta scenu */
void drawScene() {

	drawGround();
	drawEnvironment();
}

/* Crtaju se igraci */
void drawCowboys(void) {

	drawPlayer1();
	drawPlayer2();
}

/* Crta se pod sa teksturom peska/sljunka */
void drawGround() {

	glBindTexture(GL_TEXTURE_2D, names[0]);

	/* Velika povrsina */
    glBegin(GL_QUADS);

        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(-50.0, 0.0, -50.0);

        glTexCoord2f(25, 0);
        glVertex3f( 50.0, 0.0, -50.0);

        glTexCoord2f(25, 25);
        glVertex3f( 50.0, 0.0,	50.0);

        glTexCoord2f(0, 25);
        glVertex3f(-50.0, 0.0,	50.0);

    glEnd();

    /* Iskljucuje se aktivna tekstura */
    glBindTexture(GL_TEXTURE_2D, 0);

}

void drawEnvironment() {

	/* Crta se pozadina */
	glPushMatrix();

		glTranslatef(13.2, -2.5, 0);
		glRotatef(90, 0, 0, 1);
		glScalef(1.8, 1, 1);
		
		glBindTexture(GL_TEXTURE_2D, names[1]);

		/* Sirok quad */
   		glBegin(GL_QUADS);

	        glNormal3f(0, 1, 0);

	        glTexCoord2f(0, 0);
	        glVertex3f(0, 0, -6);

	        glTexCoord2f(1, 0);
	        glVertex3f(0, 26, -6);

	        glTexCoord2f(1, 1);
	        glVertex3f(6, 26, -6);

	        glTexCoord2f(0, 1);
	        glVertex3f(6, 0, -6);

	    glEnd();

    /* Iskljucuje se aktivna tekstura */
    glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

/* Kreira se prvi igrac */
void drawPlayer1() {

	glPushMatrix();
	
		/* Prvi igrac se nalazi levo od koord. pocetka */
		glTranslatef(-4, 0.5, 2);
		glRotatef(90, 0, 1, 0);

		drawBoots();
		drawLegs();
		drawBody();
		drawLeftArm();
		drawRightArm1();
		drawPistol1();
		drawBullet1();
		drawHead();
		drawHat();

	glPopMatrix();
}

/* Kreira se drugi igrac */
void drawPlayer2() {

	glPushMatrix();

		/* Drugi igrac se nalazi desno od koord. pocetka */
		glTranslatef(4, 0.5, 1.8);
		glRotatef(-90, 0, 1, 0);

		drawBoots();
		drawLegs();
		drawBody();
		drawLeftArm();
		drawRightArm2();
		drawPistol2();
		drawBullet2();
		drawHead();
		drawHat();

	glPopMatrix();
}

void drawBoots() {

	/* Prva cipela */
	glPushMatrix();
		glColor3ub(45, 28, 22);
		glTranslatef(0.0, -0.35, 0);
		glScalef(0.21, 0.5, 0.21);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, -0.45, 0.15);
		glScalef(0.21, 0.1, 0.55);
		glutSolidCube(1);
	glPopMatrix();

	/* Druga cipela */
	glPushMatrix();
		glTranslatef(0.4, -0.35, 0);
		glScalef(0.21, 0.5, 0.21);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.4, -0.45, 0.15);
		glScalef(0.21, 0.1, 0.55);
		glutSolidCube(1);
	glPopMatrix();
}

void drawLegs() {

	/* Leva noga */
	glPushMatrix();
		glColor3ub(15, 74, 139);
		glScalef(0.2, 1.2, 0.2);
		glutSolidCube(1);
	glPopMatrix();

	/* Desna noga */
	glPushMatrix();
		glTranslatef(0.4, 0.0, 0.0);
		glScalef(0.2, 1.2, 0.2);
		glutSolidCube(1);
	glPopMatrix();
}

void drawBody() {

	glPushMatrix();

		glColor3ub(139, 69, 19);
		glTranslatef(0.2, 1.05, 0.0);
		glScalef(0.7, 1.05, 0.3);
		glutSolidCube(1);

	glPopMatrix();
}

void drawLeftArm() {

	glPushMatrix();

		glColor3ub(139, 69, 19);
		glTranslatef(0.63, 1.1, 0.0);
		glScalef(0.15, 0.85, 0.15);
		glutSolidCube(1);

	glPopMatrix();
}

void drawRightArm1() {

	glColor3ub(139, 69, 19);
	
	glPushMatrix();

		/* Ako je prvi igrac na redu, potrebno je na nacrtanu ruku izvrsiti rotaciju oko ramena */
		if (player1.turn == 1) {
			glTranslatef(0, 1.5, 0);
			glRotatef(-pistolArmPosition, 1, 0, 0);
			glTranslatef(0, -1.5, 0);
		}

		glPushMatrix();

			glTranslatef(-0.23, 1.1, 0);
			glScalef(0.15, 0.85, 0.15);
			glutSolidCube(1);

		glPopMatrix();

	glPopMatrix();
}

void drawRightArm2() {

	glColor3ub(139, 69, 19);

	glPushMatrix();

		/* Ako je drugi igrac na redu, potrebno je na nacrtanu ruku izvrsiti rotaciju oko ramena */
		if (player2.turn == 1) {
			glTranslatef(0, 1.5, 0);
			glRotatef(-pistolArmPosition, 1, 0, 0);
			glTranslatef(0, -1.5, 0);
		}

		glPushMatrix();

			glTranslatef(-0.23, 1.1, 0);
			glScalef(0.15, 0.85, 0.15);
			glutSolidCube(1);

		glPopMatrix();

	glPopMatrix();
}

void drawPistol1() {

	glPushMatrix();

		/* Isto vazi i za pistolj, posto treba da prati ruku u kojoj se nalazi */
		if (player1.turn == 1) {
			glTranslatef(0, 1.5, 0);
			glRotatef(-pistolArmPosition, 1, 0, 0);
			glTranslatef(0, -1.5, 0);
		}

		/* Cev pistolja */
		glPushMatrix();
			glTranslatef(-0.23, 0.52, 0.1);
			/* Sa glScalef(0.1, 2.35, 0.1), kauboji bi se pucali bazukama :) */
			glScalef(0.1, 0.35, 0.1);
			glColor3ub(10, 10, 10);
			glutSolidCube(1);
		glPopMatrix();

		/* Drska pistolja */
		glPushMatrix();
			glTranslatef(-0.23, 0.63, 0.02);
			glRotatef(90, 1, 0, 0);
			glScalef(0.08, 0.15, 0.08);
			glColor3ub(10, 10, 10);
			glutSolidCube(1);
		glPopMatrix();

	glPopMatrix();
}

void drawPistol2() {

	glPushMatrix();

		/* Isto vazi i za pistolj, posto treba da prati ruku u kojoj se nalazi */
		if (player2.turn == 1) {
			glTranslatef(0, 1.5, 0);
			glRotatef(-pistolArmPosition, 1, 0, 0);
			glTranslatef(0, -1.5, 0);
		}

		/* Cev pistolja */
		glPushMatrix();
			glTranslatef(-0.23, 0.52, 0.1);
			/* Sa glScalef(0.1, 2.35, 0.1), kauboji bi se pucali bazukama :) */
			glScalef(0.1, 0.35, 0.1);
			glColor3ub(10, 10, 10);
			glutSolidCube(1);
		glPopMatrix();

		/* Drska pistolja */
		glPushMatrix();
			glTranslatef(-0.23, 0.63, 0.02);
			glRotatef(90, 1, 0, 0);
			glScalef(0.08, 0.15, 0.08);
			glColor3ub(10, 10, 10);
			glutSolidCube(1);
		glPopMatrix();

		glPopMatrix();
}


void drawBullet1() {

	/* Ako prvi igrac nije na redu, uopste se ne iscrtava metak */
	if (player1.turn == 0) {
		return ;
	}

	glPushMatrix();

		glColor3ub(35, 15, 0);

		/* Ako je na redu prvi igrac, metak je potrebno 'uperiti' ka protivniku zajedno za rukom i pistoljem */
		if (player1.turn == 1) {
			glTranslatef(0, 1.5, 0);
			glRotatef(-pistolArmPosition, 1, 0, 0);
			glTranslatef(0, -1.5, 0);
		}

		/* Ako su ruka i metak na poziciji, metak se translira ka protivniku za parametar kretnje metka */
		if (pistolArmPosition == 90) {

			glPushMatrix();

				glTranslatef(-0.23, 0.52 - bulletMovement, 0.1);
				glScalef(0.1, 0.3, 0.1);
				glutSolidCube(0.3);

			glPopMatrix();
		}

	glPopMatrix();
}

void drawBullet2() {

	/* Ako drugi igrac nije na redu, uopste se ne iscrtava metak */
	if (player2.turn == 0) {
		return ;
	}

	glPushMatrix();

		glColor3ub(35, 15, 0);

		/* Ako je na redu drugi igrac, metak je potrebno 'uperiti' ka protivniku zajedno za rukom i pistoljem */
		if (player2.turn == 1) {
			glTranslatef(0, 1.5, 0);
			glRotatef(-pistolArmPosition, 1, 0, 0);
			glTranslatef(0, -1.5, 0);
		}

		/* Ako su ruka i metak na poziciji, metak se translira ka protivniku za parametar kretnje metka */
		if (pistolArmPosition == 90) {

			glPushMatrix();

				glTranslatef(-0.23, 0.52 - bulletMovement, 0.1);
				glScalef(0.1, 0.3, 0.1);
				glutSolidCube(0.3);

			glPopMatrix();
		}

	glPopMatrix();
}


void drawHead() {

	glPushMatrix();

		glTranslatef(0.17, 1.85, 0);
		glScalef(0.4, 0.4, 0.4);

		/* Priblizna boja koze */
		glColor3ub(255, 227, 159);
		glutSolidSphere(0.6, 10, 10);

		/* Vrat */
		glTranslatef(0, -0.5, 0);
		glScalef(0.8, 1, 0.8);
		glutSolidCube(0.5);

	glPopMatrix();
}

void drawHat() {

	glPushMatrix();

		glTranslatef(0.17, 1.95, 0);
		glRotatef(-5, 1, 0, 0);
		glScalef(0.7, 0.4, 0.7);
		
		glColor3ub(139, 69, 19);

		glPushMatrix();

			/* Osnova sesira je cilindar male visine */
			float u, v, PI = 3.14159265359;
	    	for (u = 0; u < PI; u += PI / 20) {

	        	glBegin(GL_TRIANGLE_STRIP);

	        	for (v = 0; v <= 2*PI + 0.01; v += PI / 20) {

	            	set_normal_and_vertex(u, v);
	            	set_normal_and_vertex(u + PI / 20, v);
	        	}

	        	glEnd();
	    	}

	    glPopMatrix();
		
	    glTranslatef(0, 0.35, 0);
		glutSolidCube(0.5);    	

	glPopMatrix();
}

void set_normal_and_vertex(float u, float v) {

	/* Parametarska jednacina cilindra */
    glNormal3f( sin(v), 0, cos(v) );
    glVertex3f( 0.6*sin(v), 0.05*u, 0.6*cos(v) );
}


void initializeTextures()
{
    /* Ucitavanje tekstura radjeno prema kodovima asis. Ivana Cukica */
 
    glEnable(GL_TEXTURE_2D);

    /* Postavljaju se parametri okruzenja tekstura */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    Image *image;
    image = image_init(0, 0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(2, names);

    /* Cita se tekstura */
    image_read(image, "ground.bmp");

    /* Povezuje se ime sa prvom teksturom */
    glBindTexture(GL_TEXTURE_2D, names[0]);

    /* Postavljanje parametara za prvu teksturu */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Cita se druga tekstura */
    image_read(image, "wild_west_town.bmp");

    /* Povezuje se ime sa drugom teksturom */
    glBindTexture(GL_TEXTURE_2D, names[1]);

    /* Postavljanje parametara za drugu teksturu*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucuje se aktivna tekstura */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}