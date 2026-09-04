const int blinkled = 11;
const int buttonled = 2;
const int button = 4;

int prevMillis = 0;
int interval = 500;
bool blinkState = LOW;
void setup() {
  Serial.begin(9600);
  pinMode(blinkled, OUTPUT);
  pinMode(buttonled, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  int currentMillis = millis();
  if (currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;
    blinkState = !blinkState;
    digitalWrite(blinkled, blinkState);
  }
  if (digitalRead(button))
    digitalWrite(buttonled, HIGH);
  else
    digitalWrite(buttonled, LOW);
}
