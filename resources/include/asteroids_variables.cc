struct TVec2{
  float x,y;
};

struct TBullet{
  TVec2 position;
  bool active;
  float speed;
  float angle;
  bool firstbullet;
  int countForward;
};

struct TPlayer{
  TVec2 position, arrowHead, previousSpeed;
  TBullet bullet;
  bool active;
  TVec2 speed;
  float maxSpeed;
  float angle;
  float rotateSpeed;
  float scale;
  bool immortal;
  float thrust;
};

struct TEnemies{
  TVec2 position, center;
  TBullet bullet;
  bool active;
  int direction;
  float speedX;
  float speedY;
  float angle;
  bool immortal;
  int size;
  int countHit;
  bool hitted;
  int type;
  bool collDetec;
};

struct TUser{
  char *userNameRegister=nullptr,
  *passwordRegister=nullptr,
  *name=nullptr,
  *birthDate=nullptr,
  *province=nullptr,
  *country=nullptr,
  *userNameLogin=nullptr,
  *passwordLogin=nullptr,
  *email=nullptr,
  *email2=nullptr;
  int *userMaxScore=nullptr;
};

struct TOrderedUser{
  char *userNameRegisterOrdered = new char;
  int userMaxScoreOrdered;
};

struct TColor{
	unsigned char r,g,b;
};

struct TBox{                                  
    TVec2 p1,p2;
    TColor color;
};

FILE *fSave;
FILE *fSave_2;
int offsetWide = 10;
int offsetLength = 35;
int score=0, maxScore=0;
bool startWrite = false, validUser = false, validUserAdmin = false;

int numEnemies = 4;
int countWhenDead=0, countimmortal=0, countInitAsteroids=0, countTotalAsteroids=32;
int playerLife = 3;
int countLoad;

int editRecord=0, deleteRecord=0, contEdit=0;

bool hiperspace=false, incrementScale=false, immortalStart=false;
bool collDetec=false, collDetec_2=false;
int contImpact=0, isImpact=false; 
float lastPosX, lastPosY, lastPosX2, lastPosY2, lastPosX3, lastPosY3, lastPosX4, lastPosY4, lastPosX5, lastPosY5;
bool boolLoad=true, showScores=false;
bool DetectSoundAsteroid=false, DetectSoundUFO=false, DetectSoundPlayerDead=false, DetectSoundEndgGame=false, DetectSoundCoin=false, DetectSoundLoad=false;

char *var20 = new char, *var13 = new char, *var14 = new char;
char *oldname = new char, *newname = new char; 

char *adminReg = "LOGADMIN";
char *adminPas = "1234";

float angleBetweenRadians = 6.28f / 5, dotProduct=0;

bool gamestart=false, gameEnd=false, startScreen_=true, identify_=false, adminIdentify_=false, admin_=false, register_=false, registerin=true, identifyin=true, back_=false, play_=false;
bool controlsinfo_=false, deleteText=false, enterReg=false, adminBack=false, adminShow=true;
bool isGamePaused=false, colorMode=false, timerMode=false, MBmode=false, pLifeSetToZero=false, isPlayerDead=false;

float startTime=90, minutes=0, seconds=0;

const int kWindowWidth=1200, kWindowHeight=800;
unsigned char fps=60;
double current_time,last_time;

esat::SpriteHandle space, ship, arrows, g, spacekey, tab, MB, p;

TPlayer *g_Player;
TEnemies g_UFO, g_Asteroid;
TBullet g_Bullet;

TUser g_User;
TOrderedUser g_OrderedUsers[100];
const float kCircunference = PI*2;
float triangle_coords[3 * 2] = { 0.0f };
float circle_coords[30 * 2] = { 0.0f };
float transformed_Triangle[3 * 2] = { 0.0f };
float transformed_Circle[30 * 2] = { 0.0f };
float transformed_Inter[32] = { 0.0f };

//system("asteroids_main.exe&");

//--------------------------------------------------------------------------------------

void InScreen(float &posX, float &posY) {

  if(posX > kWindowWidth){posX = 0;}   if(posX < 0 ){posX = kWindowWidth;} 
  if(posY > kWindowHeight){posY = 0;}  if(posY < 0 ){posY = kWindowHeight;}
}

void MoveEnemy(TEnemies *enemy){
  switch (enemy->direction){
    case 0: // right and down
      enemy->position.x += enemy->speedX;
      enemy->position.y += enemy->speedY;
      break;

    case 1: // right and up
      enemy->position.x += enemy->speedX;
      enemy->position.y -= enemy->speedY;
      break;

    case 2: // left and up
      enemy->position.x -= enemy->speedX;
      enemy->position.y -= enemy->speedY;
      break;

    case 3: // left and down
      enemy->position.x -= enemy->speedX;
      enemy->position.y += enemy->speedY;
      break;

    case 4: // right
      enemy->position.x += enemy->speedX;
      break;

    case 5: // left
      enemy->position.x -= enemy->speedX;
      break;
  }
}

//For geometric shapes
//----------------------------------------------------
void InitShapeCoords(float* shape_coords, const int kNumberPoints) {
	float portion = kCircunference / kNumberPoints;
	for (int i = 0; i < kNumberPoints; ++i) {
		*(shape_coords + i * 2) = cos(portion * i);
		*(shape_coords + i * 2 + 1) = sin(portion * i);
	}
}

void TransformAndDraw(const float* shape_coords, float scale, float angle, float posX, float posY, float* transformed_coords, const int kNumberPoints) {
	esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY), m);

	for (int i = 0; i < kNumberPoints; ++i) {
		esat::Vec3 p = { *(shape_coords + i * 2), *(shape_coords + i * 2 + 1), 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		*(transformed_coords + i * 2) = result.x;
		*(transformed_coords + i * 2 + 1) = result.y;
	}

	esat::DrawSetFillColor(0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints);
	esat::DrawSetFillColor(255, 255, 255);
}
//----------------------------------------------------

void AllocateMemory(){
  g_User.userNameRegister = (char*)malloc(20 * sizeof(char));
  memset(g_User.userNameRegister, 0, 20 * sizeof(char)); 

  g_User.passwordRegister = (char*)malloc(20 * sizeof(char));
  memset(g_User.passwordRegister, 0, 20 * sizeof(char)); 

  g_User.name = (char*)malloc(20 * sizeof(char));
  memset(g_User.name, 0, 20 * sizeof(char)); 

  g_User.birthDate = (char*)malloc(20 * sizeof(char));
  memset(g_User.birthDate, 0, 20 * sizeof(char)); 

  g_User.province = (char*)malloc(20 * sizeof(char));
  memset(g_User.province, 0, 20 * sizeof(char)); 

  g_User.country = (char*)malloc(20 * sizeof(char));
  memset(g_User.country, 0, 20 * sizeof(char)); 

  g_User.userNameLogin = (char*)malloc(20 * sizeof(char));
  memset(g_User.userNameLogin, 0, 20 * sizeof(char)); 

  g_User.passwordLogin = (char*)malloc(20 * sizeof(char));
  memset(g_User.passwordLogin, 0, 20 * sizeof(char)); 

  g_User.email = (char*)malloc(13 * sizeof(char));
  memset(g_User.email, 0, 13 * sizeof(char)); 

  g_User.email2 = (char*)malloc(14 * sizeof(char));
  memset(g_User.email2, 0, 14 * sizeof(char)); 

  g_User.userMaxScore = (int*)malloc(sizeof(int));
  memset(g_User.userMaxScore, 0, sizeof(int)); 

  

}

void FreeParts(){

  free(g_Player);

  free(g_User.userNameLogin);
  free(g_User.passwordLogin);
  free(g_User.name);
  free(g_User.birthDate);
  free(g_User.province);
  free(g_User.country);
  free(g_User.userNameRegister);
  free(g_User.passwordRegister);
  free(g_User.email);
  free(g_User.email2);
  free(g_User.userMaxScore);

  free(var20);
  free(var13);
  free(var14);

  free(oldname);
  free(newname);
  free(adminReg);
  free(adminPas);
}


