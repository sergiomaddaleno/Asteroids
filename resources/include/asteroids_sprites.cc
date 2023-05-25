

void InitSprites(){

  space=esat::SpriteFromFile("./resources/img/space.png");
  ship=esat::SpriteFromFile("./resources/img/ship.png");
  arrows=esat::SpriteFromFile("./resources/img/arrows.png");
  g=esat::SpriteFromFile("./resources/img/g.png");
  spacekey=esat::SpriteFromFile("./resources/img/spacekey.png");
  tab=esat::SpriteFromFile("./resources/img/tab.png");
  MB=esat::SpriteFromFile("./resources/img/MB.png");
  p=esat::SpriteFromFile("./resources/img/p.png");
}


void ReleaseSprites(){

  esat::SpriteRelease(space);
  esat::SpriteRelease(ship);
  esat::SpriteRelease(arrows);
  esat::SpriteRelease(g);
  esat::SpriteRelease(spacekey);
  esat::SpriteRelease(tab);
  esat::SpriteRelease(MB);
  esat::SpriteRelease(p);
}