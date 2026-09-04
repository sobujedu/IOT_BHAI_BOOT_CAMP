const int trigpin = 9;
const int echopin = 10;
int dis_01 = 0;
int dis_02 = 0;
unsigned long time_01 = 0;
unsigned long currentTime = 0;
double speed;
bool flag = true;
unsigned long duration;
int distance;
void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH, 30000);
  distance = duration * 0.0343 / 2;
  if (flag) {
    dis_01 = distance;
    flag = false;
  }
  if (!flag && currentTime - time_01 >= 250) {
    dis_02 = distance;
    flag = true;
    time_01 = currentTime;
    speed = (double)(dis_01 - dis_02) / 0.250;
    Serial.print("Distance_01 : ");
    Serial.println(dis_01);
    Serial.print("Distanc_02 : ");
    Serial.println(dis_02);
    Serial.print("Speed : ");
    Serial.println(speed);
    Serial.println(" cm/s");
    Serial.println("--------------------");
  }

  if (speed < -15) {
    digitalWrite(12, HIGH);
    tone(13, 1000);
  } else {
    digitalWrite(12, LOW);
    noTone(13);
  }
}
