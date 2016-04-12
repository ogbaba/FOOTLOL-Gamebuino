#include <Gamebuino.h>
#include <SPI.h>
#include "Pos.c"

Gamebuino gb;

typedef struct Joueur {
  float x;
  float y;
  float vx = 0;
  float vy = 0;
  char equipe;
} Joueur;

typedef struct Balle {
  float x;
  float y;
  float vx = 0;
  float vy = 0;
} Balle;

typedef struct Pos {
  int x;
  int y;
} Pos;
int ptsB = 0;
int ptsW = 0;
int compteur = 0;
float  Nsel = PI;
float dsel = 0;
char phase = 's'; //t pour tir (j pour jeu)
int phaseJFinie = 1;
int curseur = 3;
char quiJoue = 'w';
Balle balle;

Joueur Joueurs[NJOUEURS];

Pos posInitJ[NJOUEURS];

void resetV();
void initPosJ(int nJoueur);
void phaseTir();
void dBalle();
void dJoueurs();
void phaseJeu();
void initialiser();
void dDecor();
void gPhases();
void phaseTir2();

void setup() {
  // put your setup code here, to run once:
  gb.begin();
  initialiser();
  gb.titleScreen(F("Footuino"));

}

void loop() {
  if(gb.update()){
  // put your main code here, to run repeatedly:
  dDecor();
  dBalle();
  dJoueurs();
  gPhases();
  if (gb.buttons.pressed(BTN_C)) {
    gb.sound.playCancel();
    gb.titleScreen(F("Footuino"));
    initialiser();
    ptsB = ptsW = 0;
    }
  }
}

void dDecor() {
//On dessine les cages de gauche 
gb.display.drawLine(TERRAING,0,TERRAING,CAGESH);
gb.display.drawLine(0,CAGESH,TERRAING,CAGESH);
gb.display.drawLine(TERRAING,LCDHEIGHT-CAGESH,TERRAING,LCDHEIGHT);
gb.display.drawLine(0,LCDHEIGHT - CAGESH,TERRAING,LCDHEIGHT - CAGESH);
//On dessine les cages de droite
gb.display.drawLine(LCDWIDTH - TERRAING,0,LCDWIDTH - TERRAING,CAGESH);
gb.display.drawLine(LCDWIDTH,CAGESH,LCDWIDTH - TERRAING,CAGESH);
gb.display.drawLine(LCDWIDTH - TERRAING,LCDHEIGHT-CAGESH,LCDWIDTH - TERRAING,LCDHEIGHT);
gb.display.drawLine(LCDWIDTH,LCDHEIGHT - CAGESH,LCDWIDTH - TERRAING,LCDHEIGHT - CAGESH);
//Le centre du terrain
gb.display.drawLine(LCDWIDTH/2,0,LCDWIDTH/2,LCDHEIGHT);
// Les scores toussa
gb.display.drawChar(TERRAING/2-2,LCDHEIGHT-12,'B',2);
gb.display.drawChar(LCDWIDTH-TERRAING/2-2,LCDHEIGHT-12,'W',2);
// score B
gb.display.cursorX = TERRAING/2-4;
gb.display.cursorY = 4;
gb.display.print(ptsB);
// score W
gb.display.cursorX = LCDWIDTH - TERRAING/2-4;
gb.display.cursorY = 4;
gb.display.print(ptsW);

}

void dBalle(){
  gb.display.fillCircle(balle.x,balle.y,RBALLE);
  
}
void dJoueurs(){
  for(int i = 0; i < NJOUEURS; i++)
  {
    switch (Joueurs[i].equipe){
      case 'w':
      gb.display.fillCircle(Joueurs[i].x, Joueurs[i].y, RJOUEUR);
      break;
      case 'b':
      gb.display.drawCircle(Joueurs[i].x, Joueurs[i].y, RJOUEUR);
      break;
    }
    
  }
}

void initialiser(){
  balle.x = LCDWIDTH/2;
  balle.y = LCDHEIGHT/2;
  Joueurs[0].x = posInitJ[0].x = J1X;
  Joueurs[0].y = posInitJ[0].y = J1Y;
  Joueurs[0].equipe = 'w';
  Joueurs[1].x = posInitJ[1].x = J2X;
  Joueurs[1].y = posInitJ[1].y = J2Y;
  Joueurs[1].equipe = 'w';
  Joueurs[2].x = posInitJ[2].x = J3X;
  Joueurs[2].y = posInitJ[2].y = J3Y;
  Joueurs[2].equipe = 'w';
  Joueurs[3].x = posInitJ[3].x = J4X;
  Joueurs[3].y = posInitJ[3].y = J4Y;
  Joueurs[3].equipe = 'b';
  Joueurs[4].x = posInitJ[4].x = J5X;
  Joueurs[4].y = posInitJ[4].y = J5Y;
  Joueurs[4].equipe = 'b';
  Joueurs[5].x = posInitJ[5].x = J6X;
  Joueurs[5].y = posInitJ[5].y = J6Y;
  Joueurs[5].equipe = 'b';
  for (int i = 0; i<NJOUEURS; i++)
  {
    Joueurs[i].vx = 0;
    Joueurs[i].vy = 0;
  }
  balle.vx = 0;
  balle.vy = 0;
  if (quiJoue == 'w')
  {
  Nsel = PI;
  }
  else {
  Nsel = 0;
  }
  dsel = 6;
}
void gPhases()
{
  if ((phaseJFinie == 0)&&(compteur > 60))
  {
    resetV();
    phase = 's';
  }
  if (phase == 'j')
  {
    phaseJeu();
  }
  if (phase == 's')
  {
    phaseTir();
  }
    if (phase == 't')
  {
    phaseTir2();
  }
}

void phaseTir()
{
  compteur = 0;
  if (quiJoue == 'b')
  {
  if (gb.buttons.pressed(BTN_RIGHT))
  {
    curseur += 1;
    if (curseur >= 3)
    {
      curseur = 0;
    }
    gb.sound.playTick(); 

  }  
  if (gb.buttons.pressed(BTN_LEFT))
  {
    curseur -= 1;
    if (curseur < 0)
    {
      curseur = 2;
    } 
    gb.sound.playTick(); 
  }
}
  if (quiJoue == 'w')
  {
  if (gb.buttons.pressed(BTN_RIGHT))
  {
    curseur += 1;
    if (curseur >= NJOUEURS)
    {
      curseur = 3;
    }
        gb.sound.playTick(); 

  }  
  if (gb.buttons.pressed(BTN_LEFT))
  {
    curseur -= 1;
    if (curseur < 3)
    {
      curseur = 5;
    }
        gb.sound.playTick(); 

  }
}
gb.display.drawCircle(Joueurs[curseur].x,Joueurs[curseur].y,RJOUEUR + 1);
if (gb.buttons.pressed(BTN_A))
{
  phase = 't';  

}
//gb.display.println(phase);
}


void phaseTir2()
{
  //gb.display.println(phase);
  float posCx = Joueurs[curseur].x;
  float posCy = Joueurs[curseur].y;


   if (gb.buttons.repeat(BTN_RIGHT,1))
   {
     Nsel += PI/64;
   }
     if (gb.buttons.repeat(BTN_LEFT,1))
    {
      Nsel -= PI/64;
    }
    if (gb.buttons.repeat(BTN_UP,1))
    {
      dsel += 1;
    }
    if (gb.buttons.repeat(BTN_DOWN,1))
    {
      dsel -= 1;
    }
    if (dsel > 20)
    {
      dsel -= 1;
    }
    if (dsel < 5)
    {
      dsel += 1;
    }
    posCx = Joueurs[curseur].x + dsel * cos(Nsel);
    posCy = Joueurs[curseur].y + dsel * sin(Nsel);
    gb.display.drawLine(Joueurs[curseur].x,Joueurs[curseur].y,posCx,posCy);  
    Joueurs[curseur].vx = (dsel * cos(Nsel)) / 6 ;
    Joueurs[curseur].vy = (dsel * sin(Nsel)) / 6 ;
    //gb.display.println(posCx);
if (gb.buttons.pressed(BTN_B))
{
phase = 'j';
if (quiJoue == 'w')
{
  quiJoue = 'b';
  curseur = 0;
}
else {
  quiJoue = 'w';
  curseur = 3;
}
Nsel += PI;
  
}
if (gb.buttons.pressed(BTN_A))
{
phase = 't';
  
}
}

void initPosJ(int nJoueur){
  Joueurs[nJoueur].x = posInitJ[nJoueur].x;
  Joueurs[nJoueur].y = posInitJ[nJoueur].y;
}

void phaseJeu() {
  compteur += 1;
  phaseJFinie = 0;
  float d = 0;
  float dx = 0;
  float dy = 0;
  float Vin, Vinx, Viny, Vjn, Vjnx, Vjny;
  Vin = Vinx = Viny = Vjn = Vjnx = Vjny = 0;
  balle.x += balle.vx;
  balle.y += balle.vy;
 // FRICTION BALLE
  if ((balle.vx < -LFRICTION) || (balle.vx > LFRICTION)||(balle.vy < -LFRICTION)||(balle.vy > LFRICTION))
  {
         phaseJFinie += 1;
  }

    balle.vx *= FRICTION;
    balle.vy *= FRICTION;


  // COLLISION BALLE GAUCHE
    if ((balle.x - RBALLE) < TERRAING)
    {
      if ((balle.y < CAGESH)||(balle.y > LCDHEIGHT - CAGESH))
      { 
        balle.x += 1;
      }
      else {
        initialiser();
        ptsW += 1;
        gb.sound.playOK() ;


      }
      balle.vx *= -1;
    }
    //COLLISION BALLE DROITE   
    if ((balle.x + RBALLE) > (LCDWIDTH - TERRAING))
    {
    if ((balle.y < CAGESH)||(balle.y > LCDHEIGHT - CAGESH))
    { 
      balle.x -= 1;
    }
    else {
      initialiser();
      ptsB += 1;
      gb.sound.playOK() ;
    }
      balle.vx *= -1;
    }
    if ((balle.y + RBALLE > LCDHEIGHT))
    {
      balle.y -= 1;
      balle.vy *= -1;
    }
    if (balle.y - RBALLE< 0)
    {
      balle.y += 1;
      balle.vy *= -1;

    }

  for (int i=0;i<NJOUEURS;i++)
  {  
  //FRICTION JOUEUR
 if ((Joueurs[i].vx < -LFRICTION)||(Joueurs[i].vx > LFRICTION)||(Joueurs[i].vy < -LFRICTION)||(Joueurs[i].vy > LFRICTION))
  {

         phaseJFinie += 1;
  }
    Joueurs[i].vx *= FRICTION;
    Joueurs[i].vy *= FRICTION;


    //COLLISION JOUEURS GAUCHE
    if ((Joueurs[i].x - RJOUEUR) < TERRAING)
    {
      if ((Joueurs[i].y > CAGESH)||(Joueurs[i].y < LCDHEIGHT - CAGESH))
      { 
        Joueurs[i].x += 1;
        Joueurs[i].vx *= -1;
      }
      else {
        initPosJ[i];
      }
    }
    //COLLISION JOUEURS DROITE 
    if ((Joueurs[i].x + RJOUEUR )> (LCDWIDTH - TERRAING))
    {
      if ((Joueurs[i].y > CAGESH)||(Joueurs[i].y < LCDHEIGHT - CAGESH))
      { 
        Joueurs[i].x -= 1;
        Joueurs[i].vx *= -1;
      }
      else {
        initPosJ[i];
      }
    }
    if (Joueurs[i].y + RJOUEUR > LCDHEIGHT)
    {
      Joueurs[i].y -= 1;
      Joueurs[i].vy *= -1;
    }
    if (Joueurs[i].y - RJOUEUR < 0)
    {
      Joueurs[i].y += 1;
      Joueurs[i].vy *= -1;
    }
    Joueurs[i].x += Joueurs[i].vx;
    Joueurs[i].y += Joueurs[i].vy;
  
    for (int j=0; j<NJOUEURS;j++)
    {
    //COLLISIONS ENTRE JOUEURS
      if (j == i) {j++;}
      if (j >= NJOUEURS) {break;}

      dx = Joueurs[i].x - Joueurs[j].x;
      dy = Joueurs[i].y - Joueurs[j].y;
      if ((dx*dx + dy*dy) < ((RJOUEUR * 2)*(RJOUEUR * 2))) {
        
        float N = atan(dy/dx);
        if(dx < 0){
          N += PI;
        }
        //JOUEUR I
        Vin = Joueurs[i].vx * cos(N) + Joueurs[j].vy * sin(N);
        Vinx = Vin * cos(N);
        Viny = Vin * sin(N);
        //JOUEUR  J
        Vjn = Joueurs[j].vx * cos(N) + Joueurs[j].vy * sin(N);
        //the composant of Vin on x and y
        Vjnx = Vjn * cos(N);
        Vjny = Vjn * sin(N);
        
        //JOUEUR I
        Joueurs[i].vx += - Vinx + Vjnx;
        Joueurs[i].vy += - Viny + Vjny;

        //JOUEUR J
        Joueurs[j].vx += - Vjnx + Vinx;
        Joueurs[j].vy += - Vjny + Viny;
        // eviter coincements
        
        Joueurs[i].x = Joueurs[j].x + cos(N) * (RJOUEUR+RJOUEUR);
        Joueurs[i].y = Joueurs[j].y + sin(N) * (RJOUEUR+RJOUEUR) ;
        
        
        
      }
    }
    //COLLISIONS JOUEURS/BALLE
    dx = Joueurs[i].x - balle.x;
    dy = Joueurs[i].y - balle.y;

    if ((dx*dx + dy*dy) < ((RJOUEUR + RBALLE)*(RJOUEUR + RBALLE))) {
      
      float N = atan(dy/dx);
      if(dx < 0){
        N += PI;
      }
              //JOUEUR I
        Vin = Joueurs[i].vx * cos(N) + balle.vy * sin(N);
        Vinx = Vin * cos(N);
        Viny = Vin * sin(N);
        //BALLE
        Vjn = balle.vx * cos(N) + balle.vy * sin(N);
        //the composant of Vin on x and y
        Vjnx = Vjn * cos(N);
        Vjny = Vjn * sin(N);
        
        //JOUEUR I
        Joueurs[i].vx += - Vinx + Vjnx;
        Joueurs[i].vy += - Viny + Vjny;

        //BALLE
        balle.vx += - Vjnx + Vinx;
        balle.vy += - Vjny + Viny;
        
  //EVITER LES COINCEMENTS Joueurs Balle:
      Joueurs[i].x = balle.x + cos(N) * (RJOUEUR+RBALLE);
      Joueurs[i].y = balle.y + sin(N) * (RJOUEUR+RBALLE);
        
  }
}
}
void resetV()
{
  for (int i=0 ; i<NJOUEURS; i++)
  {
    Joueurs[i].vx = Joueurs[i].vy = 0;
  }
      balle.vx = balle.vy = 0;

}

