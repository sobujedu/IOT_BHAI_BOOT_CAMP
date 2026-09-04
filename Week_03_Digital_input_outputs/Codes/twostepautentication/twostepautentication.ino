void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
bool buttonState = false;
bool unlocked = false;
void loop() {
  buttonState = digitalRead(2);
  if (Serial.available() > 0) {
    char incomingdata = Serial.read();
    if (incomingdata == 'U') {
      if (buttonState) {
        unlocked = true;
      } else {
        unlocked = false;
        Serial.println("Access Denied: Physical Presence Required.");
      }
    }
  }
  if (buttonState && unlocked)
    digitalWrite(13, HIGH);
  else {
    if (!buttonState && unlocked)
      Serial.println("Vault Locked.");
    unlocked = false;
    digitalWrite(13, LOW);
  }
}