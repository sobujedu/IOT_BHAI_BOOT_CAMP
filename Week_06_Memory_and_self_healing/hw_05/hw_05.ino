void setup() {
  pinMode(8, INPUT);
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}
bool pinState = false;
bool high = false;
bool low = true;

unsigned long currentTime;
unsigned long prevTime;

int i = 0;
void loop() {

  pinState = digitalRead(8);
  currentTime = millis();
  if (pinState)
  {
    digitalWrite(9, HIGH);
    analogWrite(3, 0);
  }
  if (!pinState) {
    digitalWrite(9, LOW);
    analogWrite(3, i);
    if (currentTime - prevTime >= 30) {
      if (high && !low) {
        i -= 20;
        if (i < 0) {
          i=0;
          high = false;
          low = true;
        }
      }
      if (!high && low) {
        i += 20;
        if (i > 255) {
          i=255;
          low = false;
          high = true;
        }
      }
      prevTime = currentTime;
    }
  }
}
