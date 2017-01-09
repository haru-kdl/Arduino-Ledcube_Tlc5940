#include "Tlc5940.h"

#define CHANGE_SPEED 10
#define MAX_BRIGHTNESS 4095 // 0-4095




void setup() {
  Tlc.init();
  Tlc.clear();
  Tlc.setAll(MAX_BRIGHTNESS);
  Tlc.update ();
  pinMode( 14, OUTPUT );
  pinMode( 15, OUTPUT );
  pinMode( 16, OUTPUT );
  pinMode( 17, OUTPUT );
  RowClear(0);
}
void RowClear(boolean val) {
  digitalWrite( 14, val ? HIGH : LOW ); // 1 段目
  digitalWrite( 15, val ? HIGH : LOW ); // 2 段目
  digitalWrite( 16, val ? HIGH : LOW ); // 3 段目
  digitalWrite( 17, val ? HIGH : LOW ); // 4 段目
}



void loop() {

  //CubeFlash(300);
  //CubeFlash(300);
  //CubeFlash(300);



  CubeBowan(300);
  for (int x = 1; x <= 3; x++) CubeBowan(300);
  for (int x = 1; x <= 3; x++) CubeStep(300);
  for (int x = 1; x <= 5; x++)  CubeStep(50);
  for (int x = 1; x <= 10; x++)  CubeStep(30);
  for (int x = 1; x <= 10; x++)  CubeStep(10);
  for (int x = 1; x <= 10; x++)  CubeStep(10);
  for (int x = 1; x <= 3; x++) CubeBord(300);
  for (int x = 1; x <= 10; x++) CubeBord(50);
  for (int x = 1; x <= 10; x++) CubeBord(30);
  for (int x = 1; x <= 10; x++) CubeBord(10);
  for (int x = 1; x <= 20; x++) CubeBord(1);
  CubeBowan(200);
  CubeReturn(100);
  for (int x = 1; x <= 3; x++) CubeReturn(10);



}

void CubeBord(int ChangeSpped) {
  //全階層ONに
  RowClear(1);
  for (int y = 0; y <= 3; y++) {
    Tlc.clear();
    for (int x = 0; x <= 3; x++) Tlc.set((4 * y) + x , MAX_BRIGHTNESS);
    Tlc.update();
    delay(ChangeSpped);
  }
}

void CubeStep(int ChangeSpped) {
  //全階層OFFに
  RowClear(0);

  for (int x = 0; x < 4; x++) {
    RowClear(0);
    digitalWrite( 14 + x, HIGH );
    Tlc.clear();
    Tlc.setAll(MAX_BRIGHTNESS);
    Tlc.update();

    delay(ChangeSpped);
  }
}

void CubeBowan(int ChangeSpped) {

  int curBr; // current brightness

  //全階層ONに
  RowClear(1);

  //最大値まで明るくする
  for ( curBr = 0; curBr < MAX_BRIGHTNESS; curBr++) {
    Tlc.setAll(curBr);
    Tlc.update ();
    delayMicroseconds(ChangeSpped);
    //Serial.println (curBr);
  }

  //最大値から暗くする
  for (curBr = MAX_BRIGHTNESS; curBr >= 0 ; curBr--) {
    Tlc.setAll(curBr);
    Tlc.update();
    delayMicroseconds(ChangeSpped);
  }
}

void CubeReturn(int ChangeSpped) {
  //1-15へ＋戻ってくる
  for (int x = 0; x < 4; x++) {
    RowClear(0);
    digitalWrite( 14 + x, HIGH );
    for (int i = 0; i <= 16; i++) {
      Tlc.clear();
      Tlc.set(i, MAX_BRIGHTNESS);
      delay(ChangeSpped);
      Tlc.update();
    }
  }
  delay(ChangeSpped);

  for (int x = 4 - 1; x >= 0; x--) {
    RowClear(0);
    digitalWrite( 14 + x, HIGH );
    for (int i = 16 - 1; i >= 0; i--) {
      Tlc.clear();
      Tlc.set(i, MAX_BRIGHTNESS);
      Tlc.update();
      delay(ChangeSpped);
    }
  }
  delay(ChangeSpped);
}



