#include <LiquidCrystal_I2C.h>
#define A 0
#define B 1

int LERpins[2] = {A1, A0};
int LEDpins[2] = {13, 12};

int sensorA;
int sensorB;
int umgebung;
int timeSinceGoal;

int counterA;
int counterB;

LiquidCrystal_I2C lcdA(0x27, 16, 2);
LiquidCrystal_I2C lcdB(0x26, 16, 2);

bool Init;
void setup() {
  Init = false;
  for(int i; i<2; i++){pinMode(LERpins[i], INPUT);}
  for(int i; i<2; i++){pinMode(LEDpins[i], OUTPUT);}

  lcdA.init();
  lcdA.backlight();
  lcdB.init();
  lcdB.backlight();
  
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);

  Serial.begin(9600);
  
}

void write(LiquidCrystal_I2C lcd, int cA, int cB, int C) {
  lcd.setCursor(5, 0);
  lcd.print(cA);
  lcd.setCursor(7, 0);
  lcd.print(':');
  lcd.setCursor(9, 0);
  lcd.print(cB);
  lcd.setCursor(6, 1);
  lcd.print(C);
}

int read(int pin, int counter){

    if (analogRead(pin) < umgebung/2) {
      if (timeSinceGoal == 300) {
        timeSinceGoal = 0;
        lcdA.clear();
        lcdB.clear();
       return (counter+1);
       }
    }
  return (counter);
}
// folter für vale


void checkreset(){
  if (counterA > 9) {counterA = 0;}
  if (counterB > 9) {counterB = 0;}
}

void loop() {
  if (!Init) {
    umgebung = analogRead(LERpins[A]);
    Init = true;
  }


  
 counterA = read(LERpins[A], counterA);
 counterB = read(LERpins[B], counterB);
 write(lcdA, counterA, counterB, timeSinceGoal);
 write(lcdB, counterA, counterB, timeSinceGoal);
  checkreset();
  if (timeSinceGoal<300) timeSinceGoal++;
  Serial.println((analogRead(LERpins[A]) < umgebung/2));
}
