void setup() {
  pinMode(8, INPUT);
  pinMode(6, OUTPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
}

bool currentState = false;
bool prevState = false;
int state = 0;
double voltage;
int pwm;
int i = 0;

void loop() {

  int pinVal = analogRead(A2);
  currentState = digitalRead(8);
  voltage = (pinVal * 5.0) / 1023.0;
  pwm = (voltage * 255.0) / 5.0;

  if (currentState && !prevState) {

    if (state < 2)
      state++;
    else if (state == 2 && pinVal >= 1000)
      state++;
    else if (state == 3) {
      state = 0;
      i = 0;
    }
    Serial.print("Sensor Val : ");
    Serial.println(pinVal);

    Serial.print("State : ");
    Serial.println(state);
  }

  if (state == 0) {
    analogWrite(6, 0);
  }

  if (state == 1) {
    if (i > 255)
      i = 0;
    if (i < 255)
      analogWrite(6, i);
    i += 20;
  } 

  else if (state == 2) {
    analogWrite(6, pwm);
  } 

  else if (state == 3) {
    pwm = 255 - pwm;
    analogWrite(6, pwm);
  }

  prevState = currentState;
}
