const int buttonPin = 2;
const int buzzerPin = 3;
const int potPin = A2;

volatile bool tapDetected = false;
volatile unsigned long tapTime = 0;

unsigned long previousTap = 0;
unsigned long beatTime = 0;

int potBPM = 0;
int tapBPM = 0;
int currentBPM = 0;

int tapCount = 0;
bool tapMode = false;

void buttonISR()
{
  tapTime = millis();
  tapDetected = true;
}

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, RISING);
}

void loop()
{
  int potValue = analogRead(potPin);
  potBPM = map(potValue, 0, 1023, 60, 240);
  if (tapDetected)
  {
    noInterrupts();
    unsigned long currentTap = tapTime;
    tapDetected = false;
    interrupts();
    tapCount++;
    if (tapCount == 1)
    {
      previousTap = currentTap;
      Serial.println("First Tap");
    }
    else if (tapCount == 2)
    {
      unsigned long T_ms = currentTap - previousTap;
      tapBPM = 60000 / T_ms;
      if (tapBPM < 60)
      {
        tapBPM = 60;
      }
      if (tapBPM > 240)
      {
        tapBPM = 240;
      }
      currentBPM = tapBPM;
      tapMode = true;
      previousTap = currentTap;
      tapCount = 0;
      Serial.print("Tap BPM = ");
      Serial.println(currentBPM);
    }
  }
  if (!tapMode)
  {
    currentBPM = potBPM;
  }
  unsigned long interval = 60000 / currentBPM;
  unsigned long now = millis();
  if (now - beatTime >= interval)
  {
    beatTime = now;
    tone(buzzerPin, 1000, 50);
    Serial.print("Current BPM = ");
    Serial.println(currentBPM);
  }
}