void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Try to Write Something in Serial Monitor ");

}

void loop() {
   if(Serial.available()>0)
   {
      // char incomingdata = Serial.read();
      String incomingdata = Serial.readString();
      Serial.print("I received : ");
      Serial.println(incomingdata);
   }
}