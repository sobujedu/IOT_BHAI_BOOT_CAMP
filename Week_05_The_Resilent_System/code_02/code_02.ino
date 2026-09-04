const int buttonPin = 2;
const int buzzerPin = 8;

volatile bool interruptTriggered = false;

void emergencyButtonPressed()
{
  interruptTriggered = true;
  digitalWrite(buzzerPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin,LOW);
  attachInterrupt(
    digitalPinToInterrupt(buttonPin),
    emergencyButtonPressed,
    RISING
  );
}

void loop()
{
  Serial.println("Starting Heavy Calculation : ");
  volatile unsigned long dummy = 0;
  for (unsigned long i = 0; i < 5000; i++)
  {
    dummy += i;
  }
  Serial.println("Loop Finished ");
  if(interruptTriggered)
  {
    Serial.println("Interuppt detected : Buzzer was triggered instantly.");
    delay(1000);
    digitalWrite(buzzerPin,LOW);
    interruptTriggered = false;
  }
}