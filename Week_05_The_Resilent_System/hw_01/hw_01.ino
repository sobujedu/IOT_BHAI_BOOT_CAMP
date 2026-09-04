const int greenPin = 9, redPin = 8, yellowPin = 10, buttonPin = 7;
void setup() {
  Serial.begin(9600);

  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

bool currentState = false;
bool prevState = false;
bool ystate = false;
bool gstate = false;
bool state = false;
bool rstate = false;
bool blinkState = false;

unsigned long ymili;
unsigned long gmili;
unsigned long rmili;
unsigned long smili;
unsigned long timeoutMili;
unsigned long blinkMili;

int i = 0;
int cnt = 0;
int dial;

unsigned long sprev = 0;
int blinkCount = 0;

void loop() {

  dial = map(analogRead(A2), 0, 1023, 0, 9);
  currentState = digitalRead(buttonPin);
  state = false;
  smili = millis();

  if (currentState && !prevState && !gstate && !rstate) {

    digitalWrite(yellowPin, HIGH);
    ystate = true;
    ymili = millis();
    state = true;
    i++;
    timeoutMili = millis();
  }

  if (state && i == 1 && dial == 4) {
    cnt++;
  } else if (state && i == 2 && dial == 2) {
    cnt++;
  } else if (state && i == 3 && dial == 7) {
    cnt++;
  } else if (state) {
    i = 0;
    cnt = 0;
    rstate = true;
    rmili = millis();
    digitalWrite(redPin, HIGH);
  }
  if (cnt == 3 && !gstate) {

    gstate = true;
    gmili = millis();
    digitalWrite(greenPin, HIGH);
  }
  if (ystate && millis() - ymili >= 500) {

    digitalWrite(yellowPin, LOW);
    ystate = false;
  }

  if (i > 0 && !gstate && !rstate && millis() - timeoutMili >= 4000) {

    i = 0;
    cnt = 0;
    rstate = true;
    blinkState = false;
    blinkCount = 0;
    blinkMili = millis();
    digitalWrite(redPin, LOW);
  }

  if (rstate) {

    if (millis() - blinkMili >= 200) {
      blinkMili = millis();
      if (blinkState) {
        digitalWrite(redPin, LOW);
        blinkState = false;
        blinkCount++;

      } else {
        if (blinkCount < 3) {
          digitalWrite(redPin, HIGH);
          blinkState = true;
        } else {
          rstate = false;
        }
      }
    }
  }
  if (gstate && millis() - gmili >= 5000) {
    digitalWrite(greenPin, LOW);
    gstate = false;
    cnt = 0;
    i = 0;
  }
  if (smili - sprev >= 1000) {
    Serial.print("Dial Value : ");
    Serial.println(dial);
    Serial.print("Count : ");
    Serial.println(cnt);
    sprev = smili;
  }
  prevState = currentState;
}