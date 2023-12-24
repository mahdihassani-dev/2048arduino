#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);
int m[4][4];
int rotatetext = 1;

//defintions for the direction of movement with jostick
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define BUTTON 8
int direction;
const int xPin = A0;
const int yPin = A1;

void setup() {

  display.begin();

  for (int i; i < 4; i++) {
    for (int j; j < 4; j++) {
      m[i][j] = 0;
    }
  }

  display.setContrast(45);

  display.clearDisplay();
  display.setTextSize(1);
}

//gets direction of movement
void input() {

  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int mappedX = map(xValue, 0, 1023, -100, 100);
  int mappedY = map(yValue, 0, 1023, -100, 100);

  if (mappedY > 10) {  
      direction=UP;
  } else if (mappedY < -10) {
    direction=DOWN;
  } else if (mappedX > 10) {
    direction=RIGHT;
  } else if (mappedX < -10) {
    direction=LEFT;
  }
}

void play(){
  
  
  //action to user movement
  input();
  switch(direction) {
    case RIGHT:
        for (int i = 0; i < 4; ++i)
        {
            Shift(0, i);
        }
        break;
    case LEFT:
        for (int i = 0; i < 4; ++i)
        {
            Shift(2, i);
        }
        break;
    case DOWN:
        for (int i = 0; i < 4; ++i)
        {
            Shift(3, i);
        }
        break;
    case UP:
        for (int i = 0; i < 4; ++i)
        {
            Shift(1, i);
        }
        break;
    default:
        //cout << endl << "null" << endl;  // not arrow
        break;
    }
}

void loop() {

  int x = random(0, 3);
  int y = random(0, 3);

  m[x][y] = 2;


  display.setCursor(0, 0);
  display.print(m[0][0]);

  display.setCursor(20, 0);
  display.print(m[0][1]);

  display.setCursor(40, 0);
  display.print(m[0][2]);

  display.setCursor(60, 0);
  display.print(m[0][3]);

  //-----------------------

  display.setCursor(0, 10);
  display.print(m[1][0]);

  display.setCursor(20, 10);
  display.print(m[1][1]);

  display.setCursor(40, 10);
  display.print(m[1][2]);

  display.setCursor(60, 10);
  display.print(m[1][3]);

  //-----------------------


  display.setCursor(0, 20);
  display.print(m[2][0]);

  display.setCursor(20, 20);
  display.print(m[2][1]);

  display.setCursor(40, 20);
  display.print(m[2][2]);

  display.setCursor(60, 20);
  display.print(m[2][3]);

  //-----------------------

  display.setCursor(0, 30);
  display.print(m[3][0]);

  display.setCursor(20, 30);
  display.print(m[3][1]);

  display.setCursor(40, 30);
  display.print(m[3][2]);

  display.setCursor(60, 30);
  display.print(m[3][3]);

  //-----------------------


  display.display();

  delay(2000);
  display.clearDisplay();
}