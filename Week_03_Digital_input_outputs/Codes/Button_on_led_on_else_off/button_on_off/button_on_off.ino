void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT);
  pinMode(13,OUTPUT);

}
bool flag = true;
void loop() {
  flag = digitalRead(8);
  if(flag)
    digitalWrite(13,HIGH);
  else
    digitalWrite(13,LOW);
}
