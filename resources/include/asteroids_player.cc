void InitPlayer(){

  g_Player=(TPlayer*)malloc(1*sizeof(TPlayer));

  g_Player->position.x = 600;
  g_Player->position.y = 439;

  g_Player->active = true;
  g_Player->speed.x = 0;
  g_Player->speed.y = 0.5;
  g_Player->thrust = 0.1;
  g_Player->maxSpeed = 15; 
  g_Player->angle = 4.7; 
  g_Player->rotateSpeed = 5 * PI / 180;
  g_Player->scale = 20;
  g_Player->immortal = false;
  
}

void DrawLines(){
  static int lastPosX = g_Player->position.x;
  static int lastPosY = g_Player->position.y;

  static int lastPosX2 = g_Player->position.x;
  static int lastPosY2 = g_Player->position.y;

  static int lastPosX3 = g_Player->position.x;
  static int lastPosY3 = g_Player->position.y;

  static int cont = 0;
  int offset=15;

  if(g_Player->active){
    lastPosX = g_Player->position.x;
    lastPosY = g_Player->position.y;

    lastPosX2 = g_Player->position.x;
    lastPosY2 = g_Player->position.y;

    lastPosX3 = g_Player->position.x;
    lastPosY3 = g_Player->position.y;
  }

  if(collDetec || collDetec_2){
    cont++;
    esat::DrawSetStrokeColor(255,255,255); 
    if(colorMode){
      esat::DrawSetStrokeColor(255,0,255); 
    }
    float *p = (float*)malloc(14*sizeof(float));

    lastPosX += 1;
    lastPosY -= 1;

    lastPosX2 -= 1;
    lastPosY2 += 1;

    lastPosX3 += 1;
    lastPosY3 += 1;

    *(p+0)=(lastPosX);      *(p+2)=lastPosX+offset+5;
    *(p+1)=(lastPosY);      *(p+3)=lastPosY+offset+2;
    esat::DrawPath(p,2);

    *(p+4)=(lastPosX2);                *(p+6)=lastPosX2-offset+5;
    *(p+5)=(lastPosY2+offset+7);      *(p+7)=lastPosY2+offset-2;
    esat::DrawLine(*(p+4),*(p+5), *(p+6), *(p+7));

    *(p+8)=(lastPosX3-offset+20);      *(p+10)=lastPosX3;
    *(p+9)=(lastPosY3+offset);                *(p+11)=lastPosY3;
    esat::DrawLine(*(p+8),*(p+9), *(p+10), *(p+11));

    if(cont == 60){
      collDetec=false;
      collDetec_2=false;
      cont=0;
      
    }
    free(p);
  }  
}

void DrawPlayer(){

  DrawLines();

  if(g_Player->active){

    float *p=(float*)malloc(14*sizeof(float));
    //Points to draw the ship
    *(p+0)=(g_Player->position.x + cos(0 + g_Player->angle) * g_Player->scale); //x                            
    *(p+1)=(g_Player->position.y + sin(0 + g_Player->angle) * g_Player->scale); //y
    g_Player->arrowHead.x = *(p+0);
    g_Player->arrowHead.y = *(p+1);
    
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Rotate(angleBetweenRadians * 2 - g_Player->angle), m);
    *(p+2)=(g_Player->position.x + m.d[0] * g_Player->scale);      
    *(p+3)=(g_Player->position.y - m.d[1] * g_Player->scale);

    *(p+4)=(g_Player->position.x + cos(angleBetweenRadians * 2 + g_Player->angle) * g_Player->scale); 
    *(p+5)=(g_Player->position.y + sin(angleBetweenRadians * 2 + g_Player->angle) * g_Player->scale);

    *(p+6)=(g_Player->position.x + cos(0 + g_Player->angle)*g_Player->scale);                            
    *(p+7)=(g_Player->position.y + sin(0 + g_Player->angle)*g_Player->scale);

    *(p+8)=(g_Player->position.x + cos(0 + g_Player->angle)*g_Player->scale*-0.5);                            
    *(p+9)=(g_Player->position.y + sin(0 + g_Player->angle)*g_Player->scale*-0.5);

    if(g_Player->immortal){

      if(colorMode){
        esat::DrawSetStrokeColor(255, 0, 0, 90);
        esat::DrawSetFillColor(255, 0, 0);
      }else{
        esat::DrawSetStrokeColor(255, 255, 255, 90);
      }
    }else{

      if(colorMode){
        esat::DrawSetStrokeColor(255, 0, 0);
      }else{
        esat::DrawSetStrokeColor(255, 255, 255);
      } 
    }
    
    esat::DrawLine(*(p+0),*(p+1), *(p+2), *(p+3));
    esat::DrawLine(*(p+4),*(p+5), *(p+6), *(p+7));

    esat::DrawLine(*(p+4),*(p+5), *(p+8), *(p+9));
    esat::DrawLine(*(p+2),*(p+3), *(p+8), *(p+9));

    //Draw fire of ship
    if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Up) && (int)esat::Time()%4 == 0){ 
    
      *(p+10)=(g_Player->position.x + cos(0 + g_Player->angle)*-g_Player->scale);                            
      *(p+11)=(g_Player->position.y + sin(0 + g_Player->angle)*-g_Player->scale);

      *(p+12)=(g_Player->position.x + cos(0 + g_Player->angle)*-g_Player->scale);                            
      *(p+13)=(g_Player->position.y + sin(0 + g_Player->angle)*-g_Player->scale);

      esat::DrawSetStrokeColor(0,255,0);  
      if(colorMode){
        esat::DrawSetStrokeColor(255,255,0);
      }
      esat::DrawLine(*(p+4),*(p+5), *(p+10), *(p+11));
      esat::DrawLine(*(p+2),*(p+3), *(p+12), *(p+13));
    }

    //Collision of UFO bullet to Player
    if (g_Player->immortal == false){
      if(CollisionListBullet(p, 5, g_Player->position.x, g_Player->position.y, &stackBulletUFO)){
        g_Player->active=false;
        g_Player->immortal = true;
        collDetec_2 = true;
      }
    }

    free(p);
  }
}

void MovePlayer(){

  //Player is inside the screen
  InScreen(g_Player->position.x, g_Player->position.y);

  //Rotate
  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)){
    g_Player->angle = g_Player->angle + g_Player->rotateSpeed;
  }
  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)){
    g_Player->angle = g_Player->angle - g_Player->rotateSpeed;
  }

  //Thrust
  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Up)){
    g_Player->speed.x += g_Player->thrust * cos(g_Player->angle);
    g_Player->speed.y += g_Player->thrust * sin(g_Player->angle);

    //Limit the maximum speed
    if(g_Player->speed.x > g_Player->maxSpeed){g_Player->speed.x = g_Player->maxSpeed;}
    if(g_Player->speed.x < (0 - g_Player->maxSpeed)){g_Player->speed.x = (0 -g_Player->maxSpeed);}

    if(g_Player->speed.y > g_Player->maxSpeed){g_Player->speed.y = g_Player->maxSpeed;}
    if(g_Player->speed.y < (0 - g_Player->maxSpeed)){g_Player->speed.y = (0 -g_Player->maxSpeed);}
    
  }else{
    g_Player->speed.x *= 0.99;
    g_Player->speed.y *= 0.99;
  }

  g_Player->position.x += g_Player->speed.x;
  g_Player->position.y += g_Player->speed.y;


  //-------------------------------------------------

  //Hiperspace (random position when pressed)
  if(esat::IsKeyDown('G')){hiperspace=true;}
  if(hiperspace){g_Player->scale = g_Player->scale - 0.5;}

  if(g_Player->scale==0){
    incrementScale=true; 
    g_Player->position.x = rand()%kWindowWidth;
    g_Player->position.y = rand()%kWindowHeight;
  }
  if(incrementScale){hiperspace=false; g_Player->scale++;}
  if(g_Player->scale >= 20){incrementScale=false;}

  //Reactivate player when eliminated
  if(g_Player->active == false){
    countWhenDead++;

    if(countWhenDead == 75){
      g_Player->position.x = 600;
      g_Player->position.y = 439;
      g_Player->speed.x = 0;
      g_Player->speed.y = 0.5;
      g_Player->angle = 4.7;
      g_Player->active = true;
      DetectSoundPlayerDead = true;

      //In timerMode, the player has unlimited lifes
      if(!timerMode){playerLife = playerLife - 1;}
      if(timerMode){score = score - 500;}
      countWhenDead = 0;
    }
  }

  //Player is immortal for a few seconds when it has died or at the start of the game
  if(immortalStart){
    g_Player->immortal=true;
  }
  if(g_Player->immortal){
    countimmortal++;

    if(timerMode && countimmortal >= 50 && !immortalStart){
      esat::DrawSetFillColor(255, 255, 0);
      esat::DrawSetTextFont("./resources/font/font.ttf"); 
      esat::DrawSetTextSize(25.0f);
      esat::DrawText(130, 80, "-500 pts");
      esat::DrawText(130, 80, "-500 pts");
      esat::DrawText(130, 80, "-500 pts");
    }

    if(countimmortal == 160){
      g_Player->immortal = false;
      countimmortal = 0;
      immortalStart=false;
    }
  }
}

//------------------------------------------------------------------------------------------------------------------------------------
//Bullet

void InitBullet(){

  CreateStack(&stackBullet);
 
  g_Bullet.position.x = g_Player->arrowHead.x;
  g_Bullet.position.y = g_Player->arrowHead.y;
  g_Bullet.active = false;
  g_Bullet.speed = 9;
  g_Bullet.angle = g_Player->angle;
  g_Bullet.countForward = 0;
}

void DrawBulletSatck(TNode **list){
  srand(time(NULL));
  int ranColor=200 + rand()%50, ranColor2=200 + rand()%50, ranColor3=200 + rand()%50;

  float offset=1; 
  TNode *p = SearchList(stackBullet, actual);
  if(!IsemptyList(*list)){
    float *q=(float*)malloc(10*sizeof(float));
    esat::DrawSetStrokeColor(255,255,255); 
    if(colorMode){
      esat::DrawSetStrokeColor(ranColor,ranColor,ranColor3); 
    }
      for(p=*list;p!=nullptr;p=p->prox){

        //Bullet is inside the screen
        InScreen(p->info.position.x, p->info.position.y);

        p->info.position.x += p->info.speed * cos(p->info.angle);
        p->info.position.y += p->info.speed * sin(p->info.angle);
        p->info.countForward++;

        *(q+0)=p->info.position.x;*(q+1)=p->info.position.y;
        *(q+2)=*(q+0)+offset;
        *(q+3)=*(q+1);
        *(q+4)=*(q+0)+offset;
        *(q+5)=*(q+1)+offset;
        *(q+6)=*(q+0);
        *(q+7)=*(q+1)+offset;
        *(q+8)=*(q+0);
        *(q+9)=*(q+1);
        esat::DrawPath(q,5);
    
        if(p!=nullptr && (p->info.countForward>=80)){ 
          DeleteFromListBullet(&stackBullet,80);
          DeleteFromListBullet(&stackBulletUFO,80);
          p->info.countForward = 0;
        }
      }
    free(q);
  }
}

void InsertBulletInStack(){

  //Activate bullet
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space) && g_Player->active && !gameEnd){
    g_Bullet.active=true;
    g_Bullet.angle = g_Player->angle;

    g_Bullet.position.x = g_Player->arrowHead.x;
    g_Bullet.position.y = g_Player->arrowHead.y;

    InsertStack(&stackBullet, g_Bullet); 
  }
}