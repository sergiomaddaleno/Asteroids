TListEnemies *stackAsteroid; 

void InitAsteroid(){
  srand(time(NULL));

  CreateListEnemies(&stackAsteroid);

  for (int i=0; i<numEnemies; i++) {

    int randPosY = rand()%kWindowHeight;
    int randPosX = rand()%kWindowHeight;
    int randDir = rand()%6;
    int randType = rand()%3;
    
    g_Asteroid.position.x = randPosX;
    g_Asteroid.position.y = randPosY;

    g_Asteroid.active = true;
    g_Asteroid.speedY = 0.5; 
    g_Asteroid.speedX = 0.5; 
    g_Asteroid.angle = 0;
    g_Asteroid.size = 27;
    g_Asteroid.countHit = 0;
    g_Asteroid.hitted = false;
    g_Asteroid.direction = randDir;
    g_Asteroid.type = randType;
    g_Asteroid.collDetec = false;

    InsertListEnemies(&stackAsteroid, g_Asteroid);
  }
}

void DrawDot(TEnemies enemy, bool &collDetec){
  esat::DrawSetStrokeColor(255,255,255); 
  srand(time(NULL));
  int randNum = rand()%5;

  int offset=2;
  int static cont = 0;

  if(collDetec){
    cont++;
    float *p = (float*)malloc(27*sizeof(float));

    lastPosX -= 0.2;  lastPosX2 -= 1;  lastPosX3 -= 0.5;    lastPosX4 -= 1;   lastPosX5 += 1;  
    lastPosY += 1;  lastPosY2 -= 1;  lastPosY3 += 0.5;  lastPosY4 += 0.5; lastPosY5 -= 1;

    *(p+0)=lastPosX2;*(p+1)=lastPosY2;                
    *(p+2)=*(p+0)+offset;            
    *(p+3)=*(p+1);      
    *(p+4)=*(p+0)+offset;                
    *(p+5)=*(p+1)+offset;                  
    *(p+6)=*(p+0);            
    *(p+7)=*(p+1)+offset;            
    *(p+8)=*(p+0);              
    *(p+9)=*(p+1);                  
    esat::DrawPath(p,5);       

    *(p+0)=lastPosX;*(p+1)=lastPosY;
    *(p+2)=*(p+0)+offset;           
    *(p+3)=*(p+1);                  
    *(p+4)=*(p+0)+offset;           
    *(p+5)=*(p+1)+offset;           
    *(p+6)=*(p+0);                  
    *(p+7)=*(p+1)+offset;           
    *(p+8)=*(p+0);                  
    *(p+9)=*(p+1);                  
    esat::DrawPath(p,5);                         

    *(p+0)=lastPosX4;*(p+1)=lastPosY4;          
    *(p+2)=*(p+0)+offset;                      
    *(p+3)=*(p+1);  
    *(p+4)=*(p+0)+offset;                
    *(p+5)=*(p+1)+offset;                
    *(p+6)=*(p+0);    
    *(p+7)=*(p+1)+offset;          
    *(p+8)=*(p+0);  
    *(p+9)=*(p+1);        
    esat::DrawPath(p,5);      

    *(p+0)=lastPosX3;*(p+1)=lastPosY3;    
    *(p+2)=*(p+0)+offset;                 
    *(p+3)=*(p+1);                        
    *(p+4)=*(p+0)+offset;                 
    *(p+5)=*(p+1)+offset;                 
    *(p+6)=*(p+0);                        
    *(p+7)=*(p+1)+offset;                 
    *(p+8)=*(p+0);                        
    *(p+9)=*(p+1);                        
    esat::DrawPath(p,5);                  

    *(p+0)=lastPosX5;*(p+1)=lastPosY5;
    *(p+2)=*(p+0)+offset;           
    *(p+3)=*(p+1);                  
    *(p+4)=*(p+0)+offset;           
    *(p+5)=*(p+1)+offset;           
    *(p+6)=*(p+0);                  
    *(p+7)=*(p+1)+offset;           
    *(p+8)=*(p+0);                  
    *(p+9)=*(p+1);                  
    esat::DrawPath(p,5);                      

    

    if(cont == 60){
      collDetec=false;
      cont=0;
    }

    free(p);
  }  
}

float *DrawAsteroidType1(TEnemies *enemy){
  esat::DrawSetStrokeColor(255,255,255); 
  if(colorMode){
    esat::DrawSetStrokeColor(0,150,255);
  }
  float *q=(float*)malloc(24*sizeof(float));
    //points to draw the ship
    *(q+0)=enemy->position.x;              *(q+2)=*(q+0)-enemy->size;                
    *(q+1)=enemy->position.y;              *(q+3)=*(q+1)+enemy->size + enemy->size/2;  
    
    *(q+4)=*(q+2)-enemy->size/2;         *(q+6)=*(q+4)+enemy->size;
    *(q+5)=*(q+3)-enemy->size- enemy->size/2;   *(q+7)=*(q+5)-enemy->size/2;

    *(q+8)=*(q+6)-enemy->size;      *(q+10)=*(q+8)+enemy->size;
    *(q+9)=*(q+7)-enemy->size/3;    *(q+11)=*(q+9)-enemy->size*2;

    *(q+12)=*(q+10)+enemy->size;   *(q+14)=*(q+12)+enemy->size*1.5;                
    *(q+13)=*(q+11);        *(q+15)=*(q+13)+enemy->size+ enemy->size/2;  

    *(q+16)=*(q+14);           *(q+18)=*(q+16)-enemy->size;                
    *(q+17)=*(q+15)+enemy->size/1.1;  *(q+19)=*(q+17)+enemy->size+ enemy->size;

    *(q+20)=*(q+18)-enemy->size;      *(q+22)=*(q+0);                
    *(q+21)=*(q+19);           *(q+23)=*(q+1); 
    
    esat::DrawPath(q,12);


  return q;
}

float *DrawAsteroidType2(TEnemies *enemy){

  float *q=(float*)malloc(28*sizeof(float));
  //points to draw the ship

  *(q+0)=enemy->position.x;           *(q+2)=*(q+0);                        
  *(q+1)=enemy->position.y;           *(q+3)=*(q+1)-enemy->size - enemy->size/3;

  *(q+4)=*(q+2)+enemy->size;     *(q+6)=*(q+4)+enemy->size/1.5;  *(q+8)=*(q+6)-enemy->size/1.5;  *(q+10)=*(q+8)+enemy->size*1.1;               
  *(q+5)=*(q+3)-enemy->size/2*1.5;   *(q+7)=*(q+5)+enemy->size/1.2;  *(q+9)=*(q+7)+enemy->size/3;    *(q+11)=*(q+9)+enemy->size/1.1; 

  *(q+12)=*(q+10)-enemy->size;      *(q+14)=*(q+12)-enemy->size/0.8;  *(q+16)=*(q+14)-enemy->size/1.9;  *(q+18)=*(q+16)-enemy->size/1.1;
  *(q+13)=*(q+11)+enemy->size*1.5;  *(q+15)=*(q+13)-enemy->size/1.3;  *(q+17)=*(q+15)+enemy->size/3;    *(q+19)=*(q+17)-enemy->size/1.3;

  *(q+20)=*(q+18)+enemy->size/2;   *(q+22)=*(q+20)-enemy->size/2;  *(q+24)=*(q+2);
  *(q+21)=*(q+19)-enemy->size/2;   *(q+23)=*(q+21)-enemy->size;    *(q+25)=*(q+3);

  esat::DrawSetStrokeColor(255,255,255); 
  if(colorMode){
    esat::DrawSetStrokeColor(0,150,255);
  }
  esat::DrawPath(q+2,12);

  esat::DrawSetStrokeColor(0,0,0,0); 
  esat::DrawLine(*(q+0),*(q+1), *(q+2), *(q+3));
  esat::DrawSetStrokeColor(255,255,255); 

  return q;
}

float *DrawAsteroidType3(TEnemies *enemy){
  esat::DrawSetStrokeColor(255,255,255); 
  float *q=(float*)malloc(28*sizeof(float));
  //points to draw the ship
  *(q+0)=enemy->position.x;    *(q+2)=*(q+0);                 *(q+4)=*(q+2)+enemy->size*1.2;  *(q+6)=*(q+4)+enemy->size*1.4;                                    
  *(q+1)=enemy->position.y;    *(q+3)=*(q+1)-enemy->size*2.4;  *(q+5)=*(q+3)-enemy->size*1.2;  *(q+7)=*(q+5)+enemy->size/1.1;

  *(q+8)=*(q+6)-enemy->size/1.1;   *(q+10)=*(q+8)+enemy->size/2;  *(q+12)=*(q+10)-enemy->size*1.8;    *(q+14)=*(q+12)-enemy->size*1.5;
  *(q+9)=*(q+7)+enemy->size*2;   *(q+11)=*(q+9)+enemy->size*2;    *(q+13)=*(q+11)+enemy->size/1.1;  *(q+15)=*(q+13);

  *(q+16)=*(q+14)-(enemy->size*2)/2;  *(q+18)=*(q+16);               *(q+20)=*(q+18)+enemy->size*1.1;  *(q+22)=*(q+2);
  *(q+17)=*(q+15)-enemy->size/0.8;    *(q+19)=*(q+17)-enemy->size*3;  *(q+21)=*(q+19)-enemy->size/0.8;  *(q+23)=*(q+3);

  esat::DrawSetStrokeColor(255,255,255); 
  if(colorMode){
    esat::DrawSetStrokeColor(0,150,255);
  }
  esat::DrawPath(q+2,11);

  esat::DrawSetStrokeColor(0,0,0,0); 
  esat::DrawLine(*(q+0),*(q+1), *(q+2), *(q+3));
  esat::DrawSetStrokeColor(255,255,255); 

  return q;
}

void CollisionAsteroidScript(TEnemies *p, int &countHit){
  //To draw the explosion dots
  lastPosY = p->position.y; lastPosX2 = p->position.x;  lastPosX3 = p->position.x;  lastPosX4 = p->position.x; lastPosX5 = p->position.x;
  lastPosX = p->position.x; lastPosY2 = p->position.y;  lastPosY3 = p->position.y;  lastPosY4 = p->position.y; lastPosY5 = p->position.y;
  
  p->collDetec=true;
  p->size = p->size/2;
  p->speedX = p->speedX + 1;
  p->speedY = p->speedY + 1;
  countHit = countHit + 1;
  
  //Create a new asteroid
  TEnemies newAsteroid;
  newAsteroid.position.x = p->position.x;
  newAsteroid.position.y = p->position.y;
  newAsteroid.active = true;
  newAsteroid.speedX = 2;
  newAsteroid.speedY = 3;
  newAsteroid.angle = 0;
  newAsteroid.size = p->size;
  newAsteroid.countHit = countHit;
  newAsteroid.type = rand()%3;
  newAsteroid.collDetec = false;
  newAsteroid.direction = rand()%6;
  
  //Add the new asteroid to the stack
  InsertListEnemies(&stackAsteroid, newAsteroid);
  
  p->hitted = false; //Reset the hitted flag
  DetectSoundAsteroid = true; //Sound of asteroid explosion
}

void DrawAsteroidStack(TNodeEnemies **list){
  srand(time(NULL));
  
  TNodeEnemies *p;
  if(!IsemptyListEnemies(*list)){
    for(p=*list;p!=nullptr;p=p->prox){
      float *q=nullptr; //pointer used for drawing the asteroids

      //Draw dots when asteroid eliminated
      DrawDot(p->info, p->info.collDetec);

      if(p->info.active){
        //Asteroid is inside screen
        InScreen(p->info.position.x, p->info.position.y);

        //Draw Asteroid
        switch(p->info.type){
          case 0: q = DrawAsteroidType1(&p->info); break;
          case 1: q = DrawAsteroidType2(&p->info); break;
          case 2: q = DrawAsteroidType3(&p->info); break;
        }
        
        //Possible movements of the UFO
        MoveEnemy(&p->info);

        //----------------------------------------------------------------------------------------------------------
        //Collision of bullets to Asteroid AND player to asteroids
        if(gamestart && (CollisionListBullet(q, 12, p->info.position.x, p->info.position.y, &stackBullet) || (CollisionObjetcToList(q, 12, p->info.position.x, p->info.position.y, &stackAsteroid, g_Player->position.x, g_Player->position.y) && g_Player->immortal==false))){
            CollisionAsteroidScript(&p->info, p->info.countHit);
        }

        //Collision of UFO to asteroids
        if(gamestart && CollisionObjetcToList(q, 12, p->info.position.x, p->info.position.y, &stackAsteroid, g_UFO.position.x, g_UFO.position.y)){
          CollisionAsteroidScript(&p->info, p->info.countHit);
          g_UFO.active=false;
        }

        //Collision of UFO bullet to asteroids
        if(gamestart && CollisionListBullet(q, 12, p->info.position.x, p->info.position.y, &stackBulletUFO)){
          CollisionAsteroidScript(&p->info, p->info.countHit);
          DeleteFromListBullet(&stackBulletUFO,80); //To delete the bullet after collision
        }
        //----------------------------------------------------------------------------------------------------------
        //Delete asteroid when there has been 3 hits or when size is small
        if(p->info.countHit>=3){DeleteFromListEnemy(&stackAsteroid, 3);}
        if(p->info.size < 2){DeleteFromListEnemy(&stackAsteroid, 3); p->info.active=false;}

        //Collision of Asteroid with player
        if (g_Player->immortal == false){
          if(gamestart && CollisionObjetcToList(q, 12, p->info.position.x, p->info.position.y, &stackAsteroid, g_Player->position.x, g_Player->position.y)){
            g_Player->active = false;
            g_Player->immortal = true;
            collDetec=true;
          }
        }

        //Score points depending of the size of the asteroid
        switch(p->info.countHit){
          case 1: 
            if(!p->info.hitted){
              score = score + 20; 
              p->info.hitted = true;
          } break;

          case 2: 
            if(!p->info.hitted){
              score = score + 50; 
              p->info.hitted = true;
          } break;

          case 3: 
            if(!p->info.hitted){
              score = score + 100; 
              p->info.hitted = true;
          } break;
        }
        free(q);
      }
    }
  }
}

void RegenerateAsteroid(){

  bool allAsteroidsDestroyed = true;
  TNodeEnemies *p = stackAsteroid;

  while (p != nullptr){
    if(p->info.active){
      allAsteroidsDestroyed = false;
      break;
    }
    p = p->prox;
  }

  if(allAsteroidsDestroyed) {
    countInitAsteroids++;

    if(timerMode && (countInitAsteroids >= 75)){
      esat::DrawSetFillColor(255, 255, 0);
      esat::DrawSetTextFont("./resources/font/font.ttf"); 
      esat::DrawSetTextSize(40.0f);
      esat::DrawText(900, 100, "+20 secs!");
      esat::DrawText(900, 100, "+20 secs!");
      esat::DrawText(900, 100, "+20 secs!");
    }

    if (countInitAsteroids == 200) {

      numEnemies += 2;
      countTotalAsteroids += 16;
      InitAsteroid();
      immortalStart = true;

      if(timerMode){
          startTime = startTime + 20;
      }
      countInitAsteroids = 0;
    }
  }
}
