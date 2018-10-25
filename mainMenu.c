#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "mainTexture.h"

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

/* Inicijalizacija tekstura */
static void initialize(void);

/* Identifikator teksture */
static GLuint name;

static int window_width, window_height;


int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutCreateWindow("Main Menu");
    glutFullScreen();

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    initialize();

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void initialize(void)
{
    glClearColor(0, 0, 0, 0);

    /* Ucitavanje tekstura radjeno prema kodovima asis. Ivana Cukica */
    glEnable(GL_TEXTURE_2D);

    /* Postavljaju se parametri okruzenja tekstura */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    Image *image;
    image = image_init(0, 0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(1, &name);

    /* Cita se tekstura */
    image_read(image, "cover.bmp");

    /* Povezuje se ime sa teksturom */
    glBindTexture(GL_TEXTURE_2D, name);

    /* Postavljanje parametara */
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

static void on_display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);

    /* Centriranje slike */
    glTranslatef(0, -10, 0);

    glBindTexture(GL_TEXTURE_2D, name);

    /* Pravi se quad preko celog ekrana */
    glBegin(GL_QUADS);

        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex2f(-10, 0);

        glTexCoord2f(1, 0);
        glVertex2f(10, 0);

        glTexCoord2f(1, 1);
        glVertex2f(10, 20);

        glTexCoord2f(0, 1);
        glVertex2f(-10, 20);

    glEnd();

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

static void on_keyboard(unsigned char key, int mouseX, int mousY) {

    /* Nepotrebne informacije o poziciji misa */
    (void) mouseX;
    (void) mousY;

    switch (key) {

        /* ESC - izlaz */
        case 27:
            /* Oslobadjaju se korisceni resursi i zavrsava se program. */
            glDeleteTextures(1, &name);
            exit(0);
            break;

        /* Na ENTER se pokrece glavni program i igra pocinje */
        case 13:
            system("./mainProgram");
            exit(0);
            break;

        default:
            break;
    }
}


static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-10, 10, -10, 10, -10, 10);
}