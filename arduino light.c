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

LiquidCrystal_I2C lcd(0x27, 16, 2);


bool Init;
void setup() {
  Init = false;
  for(int i; i<*(&LERpins+1)-LERpins; i++){pinMode(LERpins[i], INPUT);}
  for(int i; i<*(&LEDpins+1)-LEDpins; i++){pinMode(LEDpins[i], OUTPUT);}

  lcd.init();
  lcd.backlight();

  digitalWrite(13, HIGH);

  Serial.begin(9600);
  
}

void write(int cA, int cB) {
  lcd.setCursor(5, 0);
  lcd.print(cA);
  lcd.setCursor(7, 0);
  lcd.print(':');
  lcd.setCursor(9, 0);
  lcd.print(cB);
}

int read(int pin, int counter){

    if (analogRead(pin) < umgebung/2) {
      if (timeSinceGoal > 500) {
        timeSinceGoal = 0;
        lcd.clear();
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
 write(counterA, counterB);
  checkreset();
  timeSinceGoal++;
  Serial.println((analogRead(LERpins[A]) < umgebung/2));
}
