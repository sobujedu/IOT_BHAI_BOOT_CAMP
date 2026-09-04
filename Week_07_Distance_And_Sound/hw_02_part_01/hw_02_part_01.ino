const int trigpin = 9;
const int echopin = 10;

unsigned long duration;

unsigned long time_01 = 0;
unsigned long time_02 = 0;
unsigned long time_03 = 0;

int distance;
int tmp;

bool state = false;

int i = 0;

void setup()
{
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  
  if (i > 255)
    i = 0;
  if (millis() - time_01 >= 100)
  {
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echopin, HIGH, 30000);
    distance = duration * 0.0343 / 2;
    time_01 = millis();
    Serial.print("Distance : ");
    Serial.println(distance);
  }
  if (millis() - time_02 >= 50)
  {
    i += 5;
    time_02 = millis();
  }
  if (distance >= 20)
  {
    analogWrite(3, i);
    digitalWrite(6, LOW);
  }
  else
  {
    analogWrite(3, 0);
    if (millis() - time_03 >= 50)
    {
      state = !state;
      digitalWrite(6, state);
      time_03 = millis();
    }
  }
}