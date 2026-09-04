void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
bool currentButtonState = false;
bool previousButtonState = false;
bool ledState = false;
int cnt = 0;
void loop() {
  currentButtonState = digitalRead(2);
  if (currentButtonState && !previousButtonState) {
    ledState = !ledState;
    cnt++;
    digitalWrite(13, ledState);
    Serial.print("Total Pressed: ");
    Serial.println(cnt);
  }
  previousButtonState = currentButtonState;
  if (Serial.available() > 0) {
    char incomingdata = Serial.read();
    if (incomingdata == '0') {
      cnt = 0;
      Serial.println("Counter Reset.");
    }
  }
}