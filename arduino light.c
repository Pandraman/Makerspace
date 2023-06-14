int counter; 
int now;
void setup() {
  pinMode(A1, INPUT);
  pinMode (A5, OUTPUT);
  Serial.begin(9600);
}
int val;

unsigned long eptm;
void loop() {
  digitalWrite(A5, HIGH);
  if (analogRead(A1)>40) {
    val=0;

  }
  else {
    val=1;
    if (now>1000) {
      counter += 1; now = 0;
    }
  }
  now += 1;
  

  if (counter>9) {
    counter = 0;
  }
  Serial.println(counter);


}
