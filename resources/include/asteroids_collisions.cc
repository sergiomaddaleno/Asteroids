TStack *stackBullet, *stackBulletUFO; 

bool CollisionListBullet(float *q, int points, int posX, int posY, TNode **list){

  esat::Vec2 bulletToCenter;
  esat::Vec2 bulletToVertex;

  int dotProduct=0;
  bool isCollision=false;

  TNode *p = SearchList(stackBullet, actual);
  if(!IsemptyList(*list)){
    for(p=*list;p!=nullptr;p=p->prox){
      bulletToCenter.x = 0;
      bulletToCenter.y = 0;

      bulletToCenter.x = p->info.position.x - posX;
      bulletToCenter.y = p->info.position.y - posY;

      for(int i=0; i<points*2; i+=2){
        bulletToVertex.x = *(q+i)   - p->info.position.x;
        bulletToVertex.y = *(q+i+1) - p->info.position.y;

          dotProduct = (bulletToVertex.x * bulletToCenter.x) + 
                       (bulletToVertex.y * bulletToCenter.y);

          //printf("Bullet to center: %f %f ", bulletToCenter.x, bulletToCenter.y);
          //printf("Bullet: %f %f ", p->info.position.x, p->info.position.y);
          //printf("Dot: %d\n", dotProduct);
          
          if(dotProduct > 0){
            isCollision=true;
            p->info.countForward=80;
            DeleteFromListBullet(&stackBullet,80); //To delete the bullet after collision
            return true;
          }
      }
    }
    //printf("\n");
  }
  return false;
}

bool CollisionObjetcToList(float *q, int points, float posX, float posY, TNodeEnemies **list, float objectPosX, float objectPosY){

  esat::Vec2 objectToCenter;
  esat::Vec2 objectToVertex;

  int dotProduct=0;
  bool isCollision=false;

  objectToCenter.x = 0;
  objectToCenter.y = 0;

  objectToCenter.x = objectPosX - posX;
  objectToCenter.y = objectPosY - posY;

  for(int i=0; i<points*2; i+=2){
    objectToVertex.x = *(q+i)   - objectPosX;
    objectToVertex.y = *(q+i+1) - objectPosY;

      dotProduct = (objectToVertex.x * objectToCenter.x) + 
                   (objectToVertex.y * objectToCenter.y);

      if(dotProduct > 0){
        isCollision=true;
        return true;
      }
  }
  return false;
}

bool CollisionPlayerToUFO(float *q, int points, int posX, int posY, TEnemies enemy){

  esat::Vec2 playerToCenter;
  esat::Vec2 playerToVertex;

  int dotProduct=0;
  bool isCollision=false;

  playerToCenter.x = 0;
  playerToCenter.y = 0;

  playerToCenter.x = g_Player->position.x - posX;
  playerToCenter.y = g_Player->position.y - posY;

  for(int i=0; i<points*2; i+=2){
    playerToVertex.x = *(q+i)   - g_Player->position.x;
    playerToVertex.y = *(q+i+1) - g_Player->position.y;

      dotProduct = (playerToVertex.x * playerToCenter.x) + 
                   (playerToVertex.y * playerToCenter.y);

      if(dotProduct > 0){
        collDetec=true;
        isCollision=true;
        return true;
      }
  }
  return false;
}

