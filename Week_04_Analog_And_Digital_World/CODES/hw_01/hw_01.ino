void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, INPUT);
  pinMode(3, OUTPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
}

bool currentState = false;
bool prevState = false;
bool state = false;
int prev = 0;
double voltage;
int adc;
void loop() {

  currentState = digitalRead(8);
  if (currentState && !prevState) {

    state = !state;
    digitalWrite(13, state);
    if (!state) {
      Serial.println("System is Off");
      analogWrite(3, 0);
    }
  }

  if (state) {

    int pinVal = analogRead(A2);
    voltage = (pinVal * 5.0) / 1023.0;
    adc = (voltage * 255.0) / 5.0;
    analogWrite(3, adc);
    if (abs(pinVal - prev) > 20) {
      Serial.print("Brightness Level : ");
      Serial.println(adc);
      prev = pinVal;
    }
  }

  prevState = currentState;
}
