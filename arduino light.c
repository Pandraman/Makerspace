#include <LiquidCrystal_I2C.h>
#define A 0
#define B 1

int LERpins[2] = {A1, A0};
int LEDpins[2] = {13, 12};

int counterA;
int counterB;

int sensorA;
int sensorB;
int umgebung;
int timeSinceGoal;

LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup() {
  for(int i; i<*(&LERpins+1)-LERpins; i++){pinMode(LERpins[i], INPUT);}
  for(int i; i<*(&LEDpins+1)-LEDpins; i++){pinMode(LEDpins[i], OUTPUT);}

  lcd.init();
  lcd.backlight();

  digitalWrite(13, HIGH);

  Serial.begin(9600);
  umgebung = digitalRead(LERpins[A];
}

void read(){
  if (LERpins[A] < umgebung/3) {
    if (timeSinceGoal > 1000) {
      counterA += 1; timeSinceGoal = 0;
      lcd.clear();
      write(counterA, counterB);
    }
  }
}

void write(int cA, int cB) {
  lcd.setCursor(5, 0);
  lcd.print(cA);
  lcd.setCursor(7, 0);
  lcd.print(':');
  lcd.setCursor(9, 0);
  lcd.print(cB);
}

void checkreset(){
  if (counterA > 9) {counterA = 0;}
  if (counterB > 9) {counterB = 0;}
}

void loop() {
  read();
  checkreset();
  timeSinceGoal++;
  Serial.println(analogRead(LERpins[A]));
}
