const int trigpin = 9;
const int echopin = 10;

unsigned long duration;
int distance;
int tmp;
void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH, 30000);

  distance = duration * 0.0343 / 2;
  //1st Part
  // if (distance < 10)
  // {
  //   digitalWrite(4, LOW);
  //   digitalWrite(5, HIGH);
  //   digitalWrite(6, LOW);

  //   tone(7, 1000);
  // }
  // else if (distance <= 25)
  // {
  //   digitalWrite(4, LOW);
  //   digitalWrite(5, LOW);
  //   digitalWrite(6, HIGH);

  //   noTone(7);
  // }
  // else
  // {
  //   digitalWrite(4, HIGH);
  //   digitalWrite(5, LOW);
  //   digitalWrite(6, LOW);

  //   noTone(7);
  // }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  //2nd Part
  tmp = map(distance, 5, 40, 200, 1000);
  if (distance < 40)
    tone(7, tmp);
  else
    noTone(7);
  delay(50);
}