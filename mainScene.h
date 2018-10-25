/* Ugao podizanja ruke */
extern float pistolArmPosition;

typedef struct {
	int turn;
	int health;
} Player;

extern Player player1;
extern Player player2;

/* Parametar kretnje (translacije) metka */
extern float bulletMovement;

void drawScene();
void drawGround();
void drawEnvironment();
void drawCowboys();
void drawPlayer1();
void drawPlayer2();
void initializeTextures();

void drawBoots();
void drawLegs();
void drawBody();
void drawLeftArm();
void drawRightArm1();
void drawRightArm2();
void drawPistol1();
void drawPistol2();
void drawBullet1();
void drawBullet2();
void drawHead();
void drawHat();
void set_normal_and_vertex(float u, float v);