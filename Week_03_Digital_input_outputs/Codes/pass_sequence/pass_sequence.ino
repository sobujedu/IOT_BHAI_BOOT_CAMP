void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
int passcodeStep = 0;
void loop() {
  // put your main code here, to run repeatedly
  if (Serial.available() > 0) {
    char incomingdata = Serial.read();
    if (passcodeStep == 0 && incomingdata == 'A') { 
      passcodeStep = 1;
    } else if (passcodeStep == 1 && incomingdata == 'B') {
      passcodeStep = 2;
    } else if (passcodeStep == 2 && incomingdata == 'C') {
      passcodeStep = 3;
    } else if (incomingdata == 'L') {
      digitalWrite(13, LOW);
      Serial.println("LED LOCKED");
      passcodeStep = 0;
    } else {
      passcodeStep = 0;
      digitalWrite(13, LOW);
      Serial.println("Error: Sequence Broken. Rebooting.");
    }
  }
  if (passcodeStep == 3)
    digitalWrite(13, HIGH);
}