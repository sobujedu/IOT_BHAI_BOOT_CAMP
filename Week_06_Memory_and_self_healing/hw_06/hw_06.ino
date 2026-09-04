bool state = false;
bool tmp = true;
void buttonISR() {
  state = true;
}

unsigned long currentTime;
unsigned long prevTime;
unsigned long beepTime = 0;

void setup() {

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), buttonISR, RISING);
}

int i = 0;
int cnt = 1;
int ans = 0;
int timer = 0;

bool pin_04;
bool pin_05;
bool pin_06;

bool boom = false;
bool freezeUsed = false;
bool locked = false;

void loop() {

  currentTime = millis();
  pin_04 = !digitalRead(4);
  pin_05 = !digitalRead(5);
  pin_06 = !digitalRead(6);

  if (pin_05 == 0 && ans == 0)
    ans++;
  if (pin_04 == 0 && ans == 1)
    ans++;
  if (pin_06 == 0 && ans == 2)
    ans++;
  if (ans == 3 && timer < 30)
    locked = true;
  
  if (state && !freezeUsed) {

    delay(3000);
    freezeUsed = true;
  }
  if ((pin_05 && !pin_04) || (pin_05 && !pin_06))
    boom = true;
  else if (pin_04 && !pin_06)
    boom = true;
  if (currentTime - prevTime >= 5000) {

    cnt += 5;
    prevTime = currentTime;
    timer += 5;
  }
  if ((timer >= 30 || boom) && !locked) {

    digitalWrite(9, HIGH);
    tmp = false;
  }
  if (i > 255)
    i = 0;
  if (tmp && !locked) {
    analogWrite(3, i);
    if (currentTime - beepTime >= 500) {
      tone(9, 1000, 100);
      beepTime = currentTime;
    }
  }
  if(locked)
  {
    analogWrite(3,0);
    digitalWrite(9,0);
  }
  i += cnt;
}