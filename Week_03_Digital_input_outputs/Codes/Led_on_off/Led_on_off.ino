void setup() {
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

bool currentButtonState = false;
bool previousButtonState = false;
bool ledState = false;

void loop() {
  currentButtonState = digitalRead(8);
  if (currentButtonState && !previousButtonState) {
    ledState = !ledState;
    digitalWrite(13, ledState);
  }
  previousButtonState = currentButtonState;
 
}