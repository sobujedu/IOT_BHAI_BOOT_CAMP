//Seiral print and digital read
// void setup() {
//   // put your setup code here, to run once:
//   pinMode(7,INPUT);
//   pinMode(13,OUTPUT);
//   Serial.begin(9600);

// }
// bool flag = false;
// void loop() {
//   //  int sensor1 = 100;
//   //  int sensor2 = 100;
//   //  int sum = sensor1*sensor2;
//   //  Serial.println(sum);
//   //  delay(5000);
//     flag = digitalRead(7);
//     Serial.print("State : ");
//     Serial.println(flag);

// }

//serial avaialbe

void setup() 
{
  Serial.begin(9600);
  Serial.println("Try Something in Seiral Monitor");
}

void loop() 
{
   if(Serial.available() > 0)
   {
      char incoming_data = Serial.read();
      Serial.print("I recieved : ");
      Serial.println(incoming_data);
   }
}





























