#include <Gamebuino.h>
#include <SPI.h>

#define TERRAING 12
#define CAGESH 14
#define RBALLE 2
int ballePosX = LCDWIDTH/2;
int ballePosY = LCDHEIGHT/2;


void dDecor();
void balle();
void dJoueurs();
void initialiser();
void collisions();


Gamebuino gb;
void setup() {
  // put your setup code here, to run once:
  gb.begin();
  gb.titleScreen(F("Footlol"));

}

void loop() {
  if(gb.update()){
  // put your main code here, to run repeatedly:
  dDecor();
  balle();
  dJoueurs();
  if (gb.buttons.pressed(BTN_C)) {gb.titleScreen(F("Footlol"));}
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
}

void balle(){
  gb.display.fillCircle(ballePosX,ballePosY,RBALLE);
  
}
void dJoueurs(){
  
}

void initialiser(){
  ballePosX = LCDWIDTH/2;
  ballePosY = LCDHEIGHT/2;
}

void collisions(){
  
}

