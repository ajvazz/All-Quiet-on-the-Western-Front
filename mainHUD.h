extern float indX1, indX2;			// Predstavljaju x-koord. indikatora preciznosti
extern int directionVector;			// Da li se x-koord. indikatora preciznosti krecu desno ili ne-desno
extern int damageDealt;				// Cuva informaciju o jacini napada

void drawHUD();
void drawBar();
void drawPrecisionIndicator();
void drawHealthBar1();
void drawHealthBar2();
int getDamage(int indicatorPos);