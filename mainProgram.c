#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "mainTexture.h"
#include "mainScene.h"
#include "mainHUD.h"

/* Makroi za tajmer */
#define TIME_TO_WAIT 10
#define START_GAME 1
#define ARM_UP 2
#define ARM_DOWN 3
#define UPDATE_INDICATOR 4
#define FIRE_BULLET 5
#define DELAY 500

/* Callback funkcije */
static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int mouseX, int mouseY);
static void on_timer(int value);

/* Osvetljenje */
static void initializeLight(void);

/* Deklaracije promenljivih */
static int bullet_animation;				// Da li se metak krece
static int animation_ongoing;				// Da li je celokupna animacija aktivna
static int pistolHolster;					// Da li je ruka spustena
static int armMovementActive;				// Ogranicava visestruko pritiskanje SPACE-a i 'slamanje' animacije
static int windowWidth, windowHeight;		// Sirina i visina prozora

/* Promenljive za vreme */
time_t currentTime;
struct tm *timeLog;

/* Deklaracija eksternih promenljivih */
float pistolArmPosition;
float bulletMovement;
float indX1, indX2;
int directionVector;
int damageDealt;
Player player1;
Player player2;


int main(int argc, char **argv) {

	/* Inicijalizacija GLUT-a */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	/* Kreiranje prozora koji ce biti prikazan preko celog ekrana */
	glutCreateWindow("Na Zapadu nista novo");
	glutFullScreen();

	/* Registrovanje callback funkcija */
	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);

	/* Nebesko plava boja pozadine */
	glClearColor(0.5, 0.75, 0.93, 1.0);

	/* Inicijalizacija svetla i tekstura */
	initializeLight();						
	initializeTextures();					


	/* Inicijalizacija promenljivih */
	animation_ongoing = 0;					// Animacija neaktivna
	bullet_animation  = 0;					// Animacija metka neaktivna
	bulletMovement 	  = 0;					// Parametar kretnje metka je 0
	pistolArmPosition = 0;					// Pocetni ugao rotacije ruke oko ramena 0
	armMovementActive = 0;					// Animacija spustanja ruke neaktivna
	pistolHolster 	  = 1;					// U pocetku je ruka spustena

	player1.turn   = 1;						// Igra pocinje sa prvim igracem na redu
	player1.health = 100;

	player2.turn   = 0;
	player2.health = 100;

	windowWidth  = 0;
	windowHeight = 0;

	indX1 = 0; indX2 = 0;					// Na pocetku se indikator nalazi na (0,0) - sredina ekrana
	directionVector = 1;					// Na pocetku se indikator krece desno

	/* ***************************** */


	/* Koristi se vreme za ispisivanje izvestaja u terminalu */
	currentTime = time(NULL);
	timeLog = localtime(&currentTime);

	char buffer[64];
	strftime(buffer, 64, "%T" , timeLog);

	fprintf(stdout, "\nLog @%s:\nGame started.\n\n", buffer);

	/* Glavna petlja programa */
	glutMainLoop();
}

static void on_display(void) {


	/******************************************************************************
		Prvo se projekcija podesava na perspektivnu, a nakon crtanja 3D objekata
		se postavlja na ortografsku projekciju za crtanje 2D HUD-a.

		Da se slika nastala ortografskom projekcijom ne bi presecala sa slikom 
		koja je nacrtana pre nje, potrebno je pre ortografske projekcije iskljuciti
		poredjenje poligona prema z-koordinati, tj DEPTH_DEST. Iskljucuje se i 
		osvetljenje, jer nije potrebno.

	*******************************************************************************/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Perspektivna projekcija */
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (float) windowWidth / windowHeight, 1, 100);

	/* Podesavanje kamere */
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0,3,7,  0,1,0,  0,1,0);


	drawScene();
	drawCowboys();

	/*  Privremeno se onemogucava osvetljenje jer bi se
		onda sencile i informacije o igracima */
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
		
	/* Ortografska projekcija */
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10, 10, -10, 10, -10, 10);


	drawHUD();

	/* Vraca se nazad osvetljenje i poredjenje z-buffera */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int mouseX, int mouseY) {

	/* Nepotrebne informacije o poziciji misa */
	(void) mouseX;
	(void) mouseY;

	switch (key) {

		/* ESC - izlaz */
		case 27:
			exit(0);
			break;

		/* Pokretanje igrice na ENTER */
		case 13:
		case 'g':
		case 'G':
			/* Ovim se onemogucuje visestruka inicijalizacija igre */
			if (animation_ongoing == 0) {
				animation_ongoing = 1;
				glutTimerFunc(TIME_TO_WAIT, on_timer, START_GAME);
			}
			break;


		/* SPACE - zaustavlja se indikator, ispaljuje se metak */
		case 32:
			
			/* Onemogucava se reakcija na SPACE ako se ruka dize ili spusta */
			if (armMovementActive)
				break;

			animation_ongoing = 0;

			/* Ispaljuje se metak sa odlaganjem */
			if (bullet_animation == 0) {
				bullet_animation  = 1;
				glutTimerFunc(TIME_TO_WAIT + DELAY*1.5, on_timer, FIRE_BULLET);
			}
			
			break;


		default:
			break;
	}
}



static void on_reshape(int width, int height) {

	/* Potrebno je pamtiti velicinu prozora zbog prebacivanja projekcija */
	windowWidth  = width;
	windowHeight = height;

	glViewport(0, 0, width, height);
}



static void on_timer(int value) {

	/* Event handler za startovanje igre - pomeranje ruke i indikatora */
	if (value == START_GAME) {

		/* Uperi pistolj */
		glutTimerFunc(TIME_TO_WAIT, on_timer, ARM_UP);

		/* Azuriraj indikator */
		glutTimerFunc(TIME_TO_WAIT, on_timer, UPDATE_INDICATOR);

		/* Iscrtaj */
		glutPostRedisplay();

		/* Ponavlja se ovaj proces ako animacija nije gotova */
		if (animation_ongoing == 1) {
			glutTimerFunc(TIME_TO_WAIT, on_timer, START_GAME);
		}
	}


	/* Event handler za ispaljivanja metka */
	if (value == FIRE_BULLET) {

		/* Translacija metka */
		bulletMovement += 0.5;

		/* Da li metak pogadja drugog igraca? */
		if (bulletMovement >= 7) {

			/* Vraca se metak u cev (na pocetak); animacija gotova */
			bulletMovement = 0;
			bullet_animation = 0;

			/*  U odnosu na poziciju indikatora, racuna se jacina napada */
			damageDealt = getDamage(indX1);

			/* Ako je pucao prvi igrac, skida se health drugom igracu, i obrnuto */
			if (player1.turn) {
				player2.health -= damageDealt;
				fprintf(stdout, "Player 1 dealt %d damage.\n\n", damageDealt);
			}

			if (player2.turn) {
				player1.health -= damageDealt;
				fprintf(stdout, "Player 2 dealt %d damage.\n\n", damageDealt);
			}


			/* Ako je jedan od igraca izgubio, zavrsi program */
			if (player1.health <= 0 || player2.health <= 0) {

				animation_ongoing = 0;
				fprintf(stdout, "Game ended: Player %d won!\n", player1.health <= 0 ? 2 : 1);
				sleep(1);
				exit(0);
			}

			/* Metak je stigao do drugog igraca i pogodio ga, spusti ruku */
			pistolHolster = 0;		
			glutTimerFunc(TIME_TO_WAIT + DELAY, on_timer, ARM_DOWN);		
		}

		/* Iscrtava se scena ponovo */
		glutPostRedisplay();

		/* Ako metak nije stigao do mete, ponavlja se ovaj proces */
		if (bullet_animation == 1) {
			glutTimerFunc(TIME_TO_WAIT, on_timer, FIRE_BULLET);
		}
	}


	/* Event handler za dizanje ruke */
	if (value == ARM_UP) {
		
		/* Povecava se ugao rotacije ruke; animacija podizanja je aktivna*/
		pistolArmPosition += 3.0;
		armMovementActive = 1;

		/* Ako je ruka uperena ka igracu, zaustavlja se u tom polozaju; kraj animacije */
		if (pistolArmPosition >= 90) {
			pistolArmPosition = 90;
			armMovementActive = 0;
		}
	}


	/* Event handler za spustanje ruke */
	if (value == ARM_DOWN) {
		
		/* Smanjuje se ugao rotacije ruke; animacija spustanja je aktivna*/
		pistolArmPosition -= 3.0;
		armMovementActive = 1;

		/* Ako je ruka spustena, zaustavlja se; kraj animacije */
		if (pistolArmPosition <= 0) {

			pistolArmPosition = 0;
			armMovementActive = 0;
			pistolHolster = 1;					// Ruka je spustena

			/* Menja se ko je na redu */
			player1.turn = !player1.turn;
			player2.turn = !player2.turn;

			/* Nakon spustene ruke, pokrece se ponovo igra */
			animation_ongoing = 1;
			glutTimerFunc(TIME_TO_WAIT + DELAY, on_timer, START_GAME);
		}

		/* Iscrtava se scena ponovo */
		glutPostRedisplay();

		/* Ako ruka nije spustena, ponavlja se ovaj proces */
		if (pistolHolster == 0) {
			glutTimerFunc(TIME_TO_WAIT, on_timer, ARM_DOWN);
		}
	}

	/* Event handler za azuriranje indikatora */
	if (value == UPDATE_INDICATOR) {

		/* U zavisnosti koji igrac je na redu i koliko zivota mu je preostalo, menja se brzina indikatora */

		if (player1.turn) {
			/* Pomeraju se x-koord. indikatora levo-desno uvecane za koeficijent preostalog zivota prvog igraca */
			indX1 += (0.3 + 3.0 / player1.health) * directionVector;
			indX2 += (0.3 + 3.0 / player1.health) * directionVector;
		}

		if (player2.turn) {
			/* Pomeraju se x-koord. indikatora levo-desno uvecane za koeficijent preostalog zivota drugog igraca */
			indX1 += (0.3 + 3.0 / player2.health) * directionVector;
			indX2 += (0.3 + 3.0 / player2.health) * directionVector;
		}

		/* Obrce se smer kretnje indikatora ako je stigao do ivice */
		if (indX1 >= 2.4 || indX1 <= -2.4) {
			directionVector *= -1;
		}
	}

}


static void initializeLight(void) {

	/* Omogucavanje osvetljenja i da materijal prati trenutnu boju. */

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	/* Podesavanje svetla */
	GLfloat lightPosition[] = {0.0, 0.0, 5.0, 0.0};
	GLfloat ambient_light[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat diffuse_light[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat specula_light[] = {1.0, 1.0, 1.0, 1.0};

	/* Podesavanje materijala */
	GLfloat ambient_coeff[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat diffuse_coeff[] = {0.8, 0.8, 0.8, 1.0};
	GLfloat specula_coeff[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat shininess[]		= {20};

	glLightfv( GL_LIGHT0, GL_AMBIENT,  ambient_light);
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  diffuse_light);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specula_light);
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);

	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,   ambient_coeff );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,   diffuse_coeff );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,  specula_coeff );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, shininess 	 );

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}