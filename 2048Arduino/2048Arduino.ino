#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <EEPROM.h>

#define BUTTON_PIN 12



Adafruit_PCD8544 display = Adafruit_PCD8544(4, 5, 6, 10, 11);
int selection[4];
int m[4][4];
// int mShow[4][4];
int rotatetext = 1;
bool moved = false;
bool joystickMove = false;

//defintions for the direction of movement with jostick
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define BUTTON 8
int direction;
const int xPin = A0;
const int yPin = A1;

void initializeMatrix() {
  for (int i; i < 4; i++) {
    for (int j; j < 4; j++) {
      m[i][j] = 0;
    }
  }

  int x1 = random(4);
  int y1 = random(4);

  int x2 = random(4);
  int y2 = random(4);

  while (x1 == x2 && y1 == y2) {
    int x2 = random(4);
    int y2 = random(4);
  }

  m[x1][y1] = 2;
  m[x2][y2] = 2;

  // for (int i; i < 4; i++) {
  //   for (int j; j < 4; j++) {
  //     mShow[i][j] = m[i][j];
  //   }
  // }
}

void addRandomNum() {

  int x, y;

  do {
    x = random(4);
    y = random(4);
  } while (m[x][y] != 0);

  m[x][y] = 2;
}

//gets direction of movement
void input() {

  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int mappedX = map(xValue, 0, 1023, -100, 100);
  int mappedY = map(yValue, 0, 1023, -100, 100);


  if (joystickMove == false) {
    if (mappedY > 10) {
      direction = UP;
      joystickMove = true;
    } else if (mappedY < -10) {
      direction = DOWN;
      joystickMove = true;
    } else if (mappedX > 10) {
      direction = RIGHT;
      joystickMove = true;
    } else if (mappedX < -10) {
      direction = LEFT;
      joystickMove = true;
    } else {
      direction = 5;
    }
  } else if (-10 <= mappedY && mappedY <= 10 && -10 <= mappedX && mappedX <= 10)
    joystickMove = false;
}

void play() {


  //action to user movement
  input();
  switch (direction) {
    case RIGHT:
      for (int i = 0; i < 4; ++i) {
        Shift(0, i);
      }
      break;
    case LEFT:
      for (int i = 0; i < 4; ++i) {
        Shift(2, i);
      }

      break;
    case DOWN:
      for (int i = 0; i < 4; ++i) {
        Shift(3, i);
      }
      break;
    case UP:
      for (int i = 0; i < 4; ++i) {
        Shift(1, i);
      }
      break;
    default:
      //cout << endl << "null" << endl;  // not arrow
      break;
  }

  direction = 5;
}

void displayTable() {
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
  display.clearDisplay();
}

int ParseTheMatrix(int par, int num)  // Change line and column to a, b, c and d
{
  int i = 0;
  int j = 0;
  int k1 = 0;
  int k2 = 0;

  switch (par) {
    case 0:
      selection[0] = m[0][num];
      selection[1] = m[1][num];
      selection[2] = m[2][num];
      selection[3] = m[3][num];
      break;
    case 1:
      selection[0] = m[num][3];
      selection[1] = m[num][2];
      selection[2] = m[num][1];
      selection[3] = m[num][0];
      break;
    case 2:
      selection[0] = m[3][num];
      selection[1] = m[2][num];
      selection[2] = m[1][num];
      selection[3] = m[0][num];
      break;
    case 3:
      selection[0] = m[num][0];
      selection[1] = m[num][1];
      selection[2] = m[num][2];
      selection[3] = m[num][3];
      break;
  }

  return selection[4];
}

void PassToMatrix(int par, int num, int a, int b, int c, int d)  // This function save our a, b, c and d at list m.
{
  int i, j, k1, k2;
  k1 = 0;
  k2 = 0;

  switch (par) {
    case 0:
      m[0][num] = a;
      m[1][num] = b;
      m[2][num] = c;
      m[3][num] = d;
      break;
    case 1:
      m[num][3] = a;
      m[num][2] = b;
      m[num][1] = c;
      m[num][0] = d;
      break;
    case 2:
      m[3][num] = a;
      m[2][num] = b;
      m[1][num] = c;
      m[0][num] = d;
      break;
    case 3:
      m[num][0] = a;
      m[num][1] = b;
      m[num][2] = c;
      m[num][3] = d;
      break;
  }
}

void Sum(int par, int num, int a, int b, int c, int d)  // For sum a, b, c and d.
{
  if (a == b && a != 0) {
    a += b;
    b = c;
    c = d;
    d = 0;
    moved = true;
  }

  if (b == c && b != 0) {
    b += c;
    c = d;
    d = 0;
    moved = true;
  }

  if (c == d && c != 0) {
    c += d;
    d = 0;
    moved = true;
  }

  PassToMatrix(par, num, a, b, c, d);
}

void Shift(int par, int num)  // Shift a, b, c and d.
{
  ParseTheMatrix(par, num);
  int a, b, c, d;
  a = selection[0];
  b = selection[1];
  c = selection[2];
  d = selection[3];

  for (int i = 0; i < 3; ++i) {
    if (a == 0) {
      if (!(b == 0 && c == 0 && d == 0)) {
        a = b;
        b = c;
        c = d;
        d = 0;
        moved = true;
      }
    }

    if (b == 0) {
      if (!(c == 0 && d == 0)) {
        b = c;
        c = d;
        d = 0;
        moved = true;
      }
    }

    if (c == 0) {
      if (d != 0) {
        c = d;
        d = 0;
        moved = true;
      }
    }
  }

  Sum(par, num, a, b, c, d);
}

// int getPower(int num) {
//   int counter = 0;

//   while (num > 1) {
//     num = num / 2;
//     counter++;
//   }

//   return counter;
// }

// void convertToPower() {

//   for (int i = 0; i < 4; ++i) {
//     for (int j = 0; j < 4; ++j) {
//       mShow[i][j] = getPower(m[i][j]);
//     }
//   }
// }

bool isLoser() {

  // zero exist
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (m[i][j] == 0) {
        return false;
      }
    }
  }

  // can move horizentally
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (m[i][j] == m[i][j + 1]) {
        return false;
      }
    }
  }

  // can move vertically
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      if (m[j][i] == m[j + 1][i]) {
        return false;
      }
    }
  }

  return true;
}

void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  size_t const address{ 0 };
  unsigned int seed{};
  EEPROM.get(address, seed);
  randomSeed(seed);
  EEPROM.put(address, seed + 1);


  display.begin();

  initializeMatrix();

  display.setContrast(45);

  display.clearDisplay();
  display.setTextSize(1);
}

void loop() {

  if (isLoser()) {

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("You Loosed");
    display.display();

    while (digitalRead(BUTTON_PIN)) {
    }

  }

  // convertToPower();
  displayTable();
  play();


  if (moved) {
    addRandomNum();
    moved = false;
  }
}
