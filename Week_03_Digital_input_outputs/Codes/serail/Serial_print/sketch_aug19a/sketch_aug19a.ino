// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   int sensor_01 = 100;
//   int sensor_02 = 100;
//   int sum = sensor_01 + sensor_02;
//   Serial.print("SUM : ");
//   Serial.println(sum);
//   delay(5000);
// }
void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);

}
bool flag = true;
void loop() {
  flag = digitalRead(8);
  if(flag)
    digitalWrite(13,HIGH);
  else
    digitalWrite(13,LOW);
  Serial.print("Current State : ");
  Serial.println(flag);
}
