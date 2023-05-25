#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
 
#include "smfLibrary.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265

#include "resources/include/asteroids_variables.cc"
#include "resources/include/TLists.cc"
#include "resources/include/TStacks.cc"
#include "resources/include/asteroids_sprites.cc"
#include "resources/include/asteroids_collisions.cc"
#include "resources/include/asteroids_asteroid.cc"
#include "resources/include/asteroids_UFO.cc"
#include "resources/include/asteroids_player.cc"
#include "resources/include/asteroids_interface.cc"

//Sound-----------------------------------------------
#include <esat_extra/soloud/soloud.h>
#include <esat_extra/soloud/soloud_wav.h>
using namespace SoLoud;
SoLoud::Soloud gSoloud;
SoLoud::Wav shootWave;           
SoLoud::Wav DestroyAsteroidWave; 
SoLoud::Wav playerDiesWave;      
SoLoud::Wav endGameWave;         
SoLoud::Wav blipSelect;          
SoLoud::Wav DestroyUFOWave;      
SoLoud::Wav shipWave;            
SoLoud::Wav hyperspaceWav;       

SoLoud::Wav breakBlock;                
SoLoud::Wav coin;                                                                   
SoLoud::Wav MBDies;                      
SoLoud::Wav pipe;   
SoLoud::Wav powerDown;
SoLoud::Wav enterLevel;    

void InitAudio(){
    gSoloud.init();
    shootWave.load("./resources/sound/laserShoot.wav");
    DestroyAsteroidWave.load("./resources/sound/explosion.wav");
    DestroyUFOWave.load("./resources/sound/powerUp.wav");
    playerDiesWave.load("./resources/sound/hitHurt.wav");
    endGameWave.load("./resources/sound/synth.wav");
    blipSelect.load("./resources/sound/blipSelect.wav");
    hyperspaceWav.load("./resources/sound/hyperspace.wav");

    breakBlock.load("./resources/sound/smb_kick.wav");
    coin.load("./resources/sound/smb_coin.wav");
    MBDies.load("./resources/sound/smb_mariodie.wav");
    pipe.load("./resources/sound/smb_pipe.wav");
    powerDown.load("./resources/sound/powerDown.wav");
    enterLevel.load("./resources/sound/enterLevel.wav");
    
}

void SoundGame(){
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space) && g_Player->active && !gameEnd){gSoloud.play((shootWave));}

  if(DetectSoundAsteroid){
    gSoloud.play((DestroyAsteroidWave));
    DetectSoundAsteroid=false;
  }
  if(DetectSoundPlayerDead){
    gSoloud.play((playerDiesWave));
    DetectSoundPlayerDead=false;

    if(gameEnd){
      DetectSoundEndgGame = true;
    }
  }
  if(DetectSoundUFO){
    gSoloud.play((DestroyUFOWave));
    DetectSoundUFO=false;
  }
  if(DetectSoundEndgGame){
    gSoloud.play((endGameWave));
    DetectSoundEndgGame=false;
  }
  if(esat::IsKeyDown('G') && g_Player->scale==20){
    gSoloud.play((hyperspaceWav));
  }
}

//----------------------------------------------------

void InitParts(){
  numEnemies = 4;
  score = 0;
  InitPlayer();
  InitBullet();
  InitBulletUFO();
  InitSprites();
  InitAsteroid();
  InitUFO();
  InitAudio();
  InitShapeCoords(triangle_coords, 3);
  InitShapeCoords(circle_coords, 30);
}

void DrawParts(){ 
  UIGame();
  DrawPlayer();
  DrawBulletSatck(&stackBullet);
  DrawBulletSatck(&stackBulletUFO);
  DrawAsteroidStack(&stackAsteroid);
  DrawUFO();
  SoundGame();
}

void MoveParts(){
  MovePlayer();
  InsertBulletInStack();
  InsertBulletUFOInStack();
  MoveUFO();
  RegenerateAsteroid();
}

void StartScreen(){
  
  if(gamestart==false && startScreen_ && identify_==false && admin_==false && register_==false){
    DrawAsteroidStack(&stackAsteroid);
    SetScreen();

    if(esat::MouseButtonDown(0) && (ControlMouse(box1) || ControlMouse(box2) || ControlMouse(bControls) || ControlMouse(bAdmin))){
      gSoloud.play((blipSelect));
    }
  }

  //--------------------------------------
  if(identify_){ 
    IdentifyUserScreen();
    ValidateUser();

    if(back_){ 
      identify_=false; 
      back_=false; 
      SetScreen();
    }

    if(esat::MouseButtonDown(0) && (ControlMouse(boxLeftBot) ||
       ControlMouse(boxRightBot))){
       gSoloud.play((blipSelect));
    }

    if(esat::MouseButtonDown(0) && ControlMouse(boxRightBot) && gamestart){DetectSoundLoad=true;}
  }

  //--------------------------------------
  if(adminIdentify_){ 
    adminIdent();
    ValidateUser();

    if(back_){ 
      adminIdentify_=false; 
      back_=false; 
      RegisterUser();
    }

    if(esat::MouseButtonDown(0) && (ControlMouse(boxLeftBot) ||
       ControlMouse(boxRightBot))){
       gSoloud.play((blipSelect));
    }
  }

  //--------------------------------------
  if(admin_){
    ListUsers();
    DeleteUser();
    LoadEditUser();

    if(back_){ 
      admin_=false; 
      back_=false; 
      SetScreen();
    }

    if(esat::MouseButtonDown(0) && (ControlMouse(boxLeftBot) || ControlMouse(boxMiddleBot))){
      gSoloud.play((blipSelect));
    }
  }
  //--------------------------------------
  if(register_){
    RegisterUser();
    
    if(contEdit == 0){
      WriteNewUser();
    }else{
      UpdateUser();
    }

    if(esat::MouseButtonDown(0) && (ControlMouse(boxLeftBot) || ControlMouse(boxMiddleBot) || ControlMouse(bClear))){
      gSoloud.play((blipSelect));
    }
  }

  //--------------------------------------
  if(controlsinfo_){
    ControlsInfo();
    ColorMode();
    TimeMode();
    MarioMode();
    DrawAsteroidStack(&stackAsteroid);
    startScreen_=false;

    if(back_){ 
      controlsinfo_=false; 
      startScreen_=true;
      back_=false; 
      SetScreen();
    }

    if(esat::MouseButtonDown(0) && ControlMouse(boxLeftBot)){
      gSoloud.play((blipSelect));
    }
  }

  //--------------------------------------
  if(gamestart){ 
    PauseGame();
    
    countLoad++;

    if(showScores){ShowHighScores();}

    identify_=false;
    register_=false;

    if(countLoad==250){ boolLoad=false; showScores=false; immortalStart=true;}

    if(boolLoad==false){
      if(!isGamePaused){
        DrawParts();
        MoveParts();
        countLoad=0;
      }
    }
  }

  //To show the highest scores any time in the menu
  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Tab) && !gamestart){startScreen_=false; controlsinfo_=false; register_=false; 
                              admin_=false; adminIdentify_=false; identify_=false; ShowHighScores(); DrawAsteroidStack(&stackAsteroid);}
  if(esat::IsSpecialKeyUp(esat::kSpecialKey_Tab)){startScreen_ = true;}

  if(DetectSoundCoin){
    gSoloud.play((coin));
    DetectSoundCoin=false;
  }

  if(DetectSoundLoad){gSoloud.play((powerDown));DetectSoundLoad=false;}
  
}

void FinishedGame(){

  //When player dies, game ends. 2 options appear in screen, play again or main menu
  if(gameEnd){

    if(ControlMouse(box2) && esat::MouseButtonDown(0)){
      esat::ResetBufferdKeyInput();
      InitParts();
      g_UFO.active = false;
      gamestart = false;
      gameEnd = false;
      identify_=false;
      register_ = false;
      registerin = true; 
      identifyin = true; 
      back_ = false; 
      play_ = false;
      controlsinfo_ = false;
      immortalStart = true;
      boolLoad=true;
      countLoad=0;
      playerLife = 3;
      numEnemies = 4;
      score = 0;
      maxScore = maxScore;
      countInitAsteroids = 4;

      if(timerMode){
          startTime = 90;  
          minutes=0;
          seconds=0;
          isPlayerDead=false;
      }
    } 

    if(ControlMouse(box1) && esat::MouseButtonDown(0)){
      esat::ResetBufferdKeyInput();
      InitParts();
      g_UFO.active = false;
      gameEnd = false;
      playerLife = 3;
      numEnemies = 4;
      countLoad=0;
      score = 0;
      immortalStart = true;
      boolLoad=false;
      countInitAsteroids = 4;
      
      if(timerMode){
          startTime = 90;  
          minutes=0;
          seconds=0;
          isPlayerDead=false;
      }
    } 
  }
}


int esat::main(int argc, char **argv) {
 
  esat::WindowInit(kWindowWidth,kWindowHeight);
  WindowSetMouseVisibility(true);

  InitParts();
  AllocateMemory();

  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
    
    StartScreen();
    FinishedGame();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }
  
  ReleaseSprites();
  FreeParts();

  esat::WindowDestroy();

  return 0;
}

