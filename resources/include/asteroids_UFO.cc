
void InitUFO(){
  srand(time(NULL));

  int randDir = rand()%6;
  int offset = rand()%3;
  int randPosY = rand()%kWindowHeight;

  switch(offset){
    case 0: offset = 10; break;
    case 1: offset = 15; break;
    case 2: offset = 20; break;
  }

  g_UFO.position.x = 0;
  g_UFO.position.y = randPosY;

  g_UFO.direction = randDir;
  g_UFO.active = false;
  g_UFO.speedX = 1; 
  g_UFO.speedY = 2;
  g_UFO.angle = 0.0f;
  g_UFO.size = offset;

}

void DrawUFO(){
  srand(time(NULL));
  
  int startRandUFO = rand()%40;

  if(startRandUFO==2){g_UFO.active=true;}

  if(g_UFO.active){
    esat::DrawSetStrokeColor(255,255,255); 
    float *p=(float*)malloc(30*sizeof(float));
    //Points to draw the ship
    *(p+0)=g_UFO.position.x;        *(p+2)=*(p+0)+g_UFO.size/15; //x  
    *(p+1)=g_UFO.position.y;        *(p+3)=*(p+1);               //y

    *(p+4)=*(p+2)+g_UFO.size*2;     *(p+6)=*(p+4)-g_UFO.size;  
    *(p+5)=*(p+3);                  *(p+7)=*(p+5)-g_UFO.size/2;

    *(p+8)=*(p+6)-g_UFO.size*2;     *(p+10)=*(p+8)-g_UFO.size;  
    *(p+9)=*(p+7);                  *(p+11)=*(p+9)+g_UFO.size/2;

    *(p+12)=*(p+10)+g_UFO.size;     *(p+14)=*(p+12)+g_UFO.size/2;  
    *(p+13)=*(p+11)-g_UFO.size/2;   *(p+15)=*(p+13)-g_UFO.size/1.3;

    *(p+16)=*(p+14)+g_UFO.size;     *(p+18)=*(p+16)+g_UFO.size/2;  
    *(p+17)=*(p+15);                *(p+19)=*(p+17)+g_UFO.size/1.3;

    *(p+20)=*(p+18)+g_UFO.size;     *(p+22)=*(p+20)-g_UFO.size;   
    *(p+21)=*(p+19)+g_UFO.size/2;   *(p+23)=*(p+21)+g_UFO.size/2;

    *(p+24)=*(p+22)-g_UFO.size*2;   *(p+26)=*(p+24)-g_UFO.size;  
    *(p+25)=*(p+23);                *(p+27)=*(p+25)-g_UFO.size/2;

    *(p+28)=g_UFO.position.x;
    *(p+29)=g_UFO.position.y;

    esat::DrawSetStrokeColor(255,255,255); 
    if(colorMode){
    esat::DrawSetStrokeColor(0,255,0); 
    }
    esat::DrawPath(p,15);

    //Collision of player bullet to UFO
    if(CollisionListBullet(p, 15, g_UFO.position.x, g_UFO.position.y, &stackBullet)){
      g_UFO.active = false;
      DetectSoundUFO = true;

      lastPosX = g_UFO.position.x; lastPosX2 = g_UFO.position.x;  lastPosX3 = g_UFO.position.x;  lastPosX4 = g_UFO.position.x; lastPosX5 = g_UFO.position.x;
      lastPosY = g_UFO.position.y; lastPosY2 = g_UFO.position.y;  lastPosY3 = g_UFO.position.y;  lastPosY4 = g_UFO.position.y; lastPosY5 = g_UFO.position.y;
      g_UFO.collDetec=true;

      switch(g_UFO.size){ //points earned when hittedlastPosY = p->info.position.y;
          case 10: score = score + 500; break;
          case 12: score = score + 200; break;
          case 20: score = score + 200; break;
        }
    }

    //Collision player with UFO
    if (g_Player->immortal == false){
      if(CollisionPlayerToUFO(p, 15, g_UFO.position.x, g_UFO.position.y, g_UFO)){
        g_Player->active = false;
        g_Player->immortal = true;
      }
    }
    free(p);
  }
}

void MoveUFO(){
  srand(time(NULL));
  
  int randDir = rand()%6;
  int offset = rand()%3;
  int randPosY = rand()%kWindowHeight;

  switch(offset){
    case 0: offset = 10; break;
    case 1: offset = 15; break;
    case 2: offset = 20; break;
  }

  //Draw dots when UFO eliminated
  DrawDot(g_UFO, g_UFO.collDetec);

  //UFO is inside the screen
  InScreen(g_UFO.position.x, g_UFO.position.y);

  MoveEnemy(&g_UFO);

  if((int)esat::Time()%4 == 0){
    g_UFO.direction = randDir;
  }

  if(g_UFO.active==false){ //Change values when UFO is eliminated
    g_UFO.size = offset;
    g_UFO.position.x=0;
  }
}

//------------------------------------------------------------------------------------------------------------------------------------
//Bullet

void InitBulletUFO(){

  CreateStack(&stackBulletUFO);

  esat::Vec2 playerToUFO;
  playerToUFO.x = g_Player->position.x - g_UFO.position.x;
  playerToUFO.y = g_Player->position.y - g_UFO.position.y;
  g_Bullet.angle = atan2(playerToUFO.y, playerToUFO.x) * 180.0f / PI;
 
  g_Bullet.position.x = g_UFO.position.x;
  g_Bullet.position.y = g_UFO.position.y;
  g_Bullet.active = false;
  g_Bullet.speed = 9;
  g_Bullet.countForward = 0;
}

void InsertBulletUFOInStack(){

  //Activate bullet
  if((int)esat::Time()%140 == 0 && g_UFO.active){
      g_Bullet.active=true;

    esat::Vec2 playerToUFO;
    playerToUFO.x = g_Player->position.x - g_UFO.position.x;
    playerToUFO.y = g_Player->position.y - g_UFO.position.y;
    g_Bullet.angle = atan2(playerToUFO.y, playerToUFO.x) * 180.0f / PI;

    g_Bullet.position.x = g_UFO.position.x;
    g_Bullet.position.y = g_UFO.position.y;

    InsertStack(&stackBulletUFO, g_Bullet); 
  }

}