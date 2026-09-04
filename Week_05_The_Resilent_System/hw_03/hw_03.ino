const int buttonPin = 2;

bool currentState = false;
bool previousState = false;
bool led_01 = false;
bool led_02 = false;
bool state = true;
bool actionDone = false;

unsigned long pressStartTime = 0;
unsigned long singlePress = 0;
unsigned long doublePress = 0;

int tapcount = 0;
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();
  currentState = digitalRead(buttonPin);
  if (currentState && !previousState) {
    pressStartTime = now;
    actionDone = false;
    tapcount++;
    if (tapcount == 1)
      singlePress = now;
    else if(tapcount == 2)
      doublePress =  singlePress;
  }

  if (currentState && now - pressStartTime >= 2000 && !actionDone) {
    state = !state;
    actionDone = true;
    tapcount = 0;
    Serial.println("Button held for 2 seconds");
    if (!state) {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }
  }
  if (state) {
    if (now - singlePress >= 400 && tapcount == 1) {
      led_01 = !led_01;
      digitalWrite(8, led_01);
      tapcount = 0;
    } else if (now - doublePress <= 400 && tapcount == 2) {
      led_02 = !led_02;
      digitalWrite(9, led_02);
      tapcount = 0;
    }
  }
  previousState = currentState;
}
