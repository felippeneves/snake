// It is assumed that the LCD module is connected to
// the following pins:
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Graph.h>
#define width 43
#define height 22
#define area 500
 
LCD5110 myGLCD(8,9,10,12,11);
 
float y;
uint8_t* bm;
int pacy;
int i;
void setup()
{
 
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  myGLCD.InitLCD();
  //myGLCD.setFont(SmallFont);
  randomSeed(analogRead(7));
  myGLCD.clrScr();
  myGLCD.update();
}
 
int foodx = 0;
int foody = 0;
 
int posx = 0;
int posy = 0;
 
int tailLength = 50;
char tailx[area];
char taily[area];
 
int gameover = 0;
 
char dir;
char key;
char r;
void loop()
{
  if (Serial.available() > 0) {
 
    r = Serial.read();
    if (!(dir == 'w' && r == 's') && !(dir == 's' && r == 'w') && !(dir == 'a' && r == 'd') && !(dir == 'd' && r == 'a')) dir = r;
    if (gameover) {
      gameover = 0;
      tailLength = 5;
      posx = 0;
   
      posy = 0;
    }
  }
 
  if (!gameover) {
  //if (key == 'a' || key == 'd' || key == 's' || key == 'w') dir = key;
    if (dir=='a')
      posx--;
    else if (dir=='d')
      posx++;
    else if (dir=='w')
      posy--;
    else if (dir=='s')
      posy++;
 
  if (posx>=width) posx = 0;
  if (posx<0) posx = width-1;
  if (posy>=height) posy = 0;
  if (posy<0) posy = height-1;
 
  if (posx == foodx && posy == foody) {
    foodx = random(0, width-1);
    foody = random(0, height-1);
    tailLength++;
  }
 
  myGLCD.clrScr();
  myGLCD.update();
 
  for (i = tailLength-1; i >= 0; i--) {
    if (i > 0) {
      tailx[i] = tailx[i-1], taily[i] = taily[i-1];
      if (tailx[i] == posx && taily[i] == posy) gameover = 1;
    } else tailx[i] = posx, taily[i] = posy;
    myGLCD.drawRect(tailx[i]*2, taily[i]*2, tailx[i]*2+2, taily[i]*2+2);
  }
 
  myGLCD.drawRect(foodx*2, foody*2, foodx*2+2, foody*2+2);
  myGLCD.drawRect(posx*2, posy*2, posx*2+2, posy*2+2);
 
  }
 
  if (gameover) {
    for (i = 0; i < tailLength; i++) {
      tailx[i] = 0;
      taily[i] = 0;
    }
  }
 
  myGLCD.update();
  delay(50);
  //myGLCD.drawRect(25, 15, 59, 31);
  //myGLCD.update();
  //delay(1000);
  //x=x+dir_x;
 
  }
 

