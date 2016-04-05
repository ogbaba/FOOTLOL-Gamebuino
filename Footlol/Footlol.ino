#include <Gamebuino.h>
#include <SPI.h>
#include "Pos.c"

Gamebuino gb;

typedef struct Joueur {
  int x;
  int y;
  char equipe;
} Joueur;

Joueur Joueurs[NJOUEURS];

int ballePosX = LCDWIDTH/2;
int ballePosY = LCDHEIGHT/2;


void balle();
void dJoueurs();
void collisions();
void initialiser();
void dDecor();


void setup() {
  // put your setup code here, to run once:
  gb.begin();
  initialiser();
  gb.titleScreen(F("Footlol"));

}

void loop() {
  if(gb.update()){
  // put your main code here, to run repeatedly:
  dDecor();
  balle();
  dJoueurs();
  if (gb.buttons.pressed(BTN_C)) {
    gb.titleScreen(F("Footlol"));
    initialiser();
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
gb.display.drawChar(0,LCDHEIGHT-gb.display.10,'B',10);
gb.display.drawChar(0,LCDHEIGHT-gb.display.10,'B',10);
}

void balle(){
  gb.display.fillCircle(ballePosX,ballePosY,RBALLE);
  
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
  ballePosX = LCDWIDTH/2;
  ballePosY = LCDHEIGHT/2;
  Joueurs[0].x = J1X;
  Joueurs[0].y = J1Y;
  Joueurs[0].equipe = 'w';
  Joueurs[1].x = J2X;
  Joueurs[1].y = J2Y;
  Joueurs[1].equipe = 'w';
  Joueurs[2].x = J3X;
  Joueurs[2].y = J3Y;
  Joueurs[2].equipe = 'w';
  Joueurs[3].x = J4X;
  Joueurs[3].y = J4Y;
  Joueurs[3].equipe = 'b';
  Joueurs[4].x = J5X;
  Joueurs[4].y = J5Y;
  Joueurs[4].equipe = 'b';
  Joueurs[5].x = J6X;
  Joueurs[5].y = J6Y;
  Joueurs[5].equipe = 'b';
}

void collisions(){
  
}

