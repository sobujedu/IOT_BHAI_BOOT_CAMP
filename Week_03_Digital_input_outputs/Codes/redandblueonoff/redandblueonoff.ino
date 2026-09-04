void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}
bool gstate = false;
bool ystate = false;
void loop() {
  
  if (Serial.available() > 0) {
    char incomingdata = Serial.read();
    if (incomingdata == 'G') {
       gstate = !gstate;
       digitalWrite(8,gstate);
    }
    else if (incomingdata == 'Y') {
       ystate = !ystate;
       digitalWrite(9,ystate);
    }
    //if (incomingdata != '\n' && incomingdata != '\r')
    else  
      Serial.println("Error: Invalid Command");
  }
}
