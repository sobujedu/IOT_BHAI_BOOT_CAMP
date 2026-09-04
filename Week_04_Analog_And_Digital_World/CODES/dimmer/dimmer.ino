void setup() {
  pinMode(3,OUTPUT);
  analogWrite(3,0);
}

void loop() {
   for(int i=0;i<255;i+=20)
   {
     analogWrite(3,i);
     delay(100);
   }
   delay(10000);
}
