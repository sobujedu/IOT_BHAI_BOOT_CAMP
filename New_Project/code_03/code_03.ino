const uint8_t PIR_PIN = 2;
const uint8_t LED_PIN = A0;

bool pirState = LOW;
bool previousPirState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println(F("Trigger Mode: H"));
}

void loop() {

  pirState = digitalRead(PIR_PIN);
  if (pirState == HIGH && previousPirState == LOW) {
    Serial.println(F("[MOTION DETECTED]"));
  }
  digitalWrite(LED_PIN, pirState);
  previousPirState = pirState;
}