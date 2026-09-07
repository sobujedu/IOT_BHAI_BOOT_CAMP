// -------------------- Ultrasonic 01 --------------------
// Back Side Sensor

const int trigpin_01 = 10;
const int echopin_01 = 11;

unsigned long duration_01;
int distance_01;


// -------------------- Ultrasonic 02 --------------------
// Front Side Sensor

const int trigpin_02 = 8;
const int echopin_02 = 9;

unsigned long duration_02;
int distance_02;


unsigned long time_01 = 0;

void setup() {

  // Configure Back Sensor pins
  pinMode(trigpin_01, OUTPUT);
  pinMode(echopin_01, INPUT);

  // Configure Front Sensor pins
  pinMode(trigpin_02, OUTPUT);
  pinMode(echopin_02, INPUT);

  digitalWrite(trigpin_01, LOW);
  digitalWrite(trigpin_02, LOW);

 
  Serial.begin(9600);
}

void loop() {

 
  if (millis() - time_01 >= 100) {


    // ========================================================
    // BACK SIDE SENSOR
    // ========================================================

    digitalWrite(trigpin_01, LOW);
    delayMicroseconds(2);

    
    digitalWrite(trigpin_01, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin_01, LOW);

    duration_01 = pulseIn(echopin_01, HIGH, 30000);
    if (duration_01 == 0) {
      distance_01 = -1;
    }
    else {
      distance_01 = duration_01 * 0.0343 / 2;
    }
    delayMicroseconds(100);
    // ========================================================
    // FRONT SIDE SENSOR
    // ========================================================
    digitalWrite(trigpin_02, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigpin_02, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigpin_02, LOW);
    duration_02 = pulseIn(echopin_02, HIGH, 30000);
    if (duration_02 == 0) {
      distance_02 = -1;
    }
    else {
      distance_02 = duration_02 * 0.0343 / 2;
    }
    time_01 = millis();
    // Serial.print("Front : ");
    // Serial.println(distance_02);
    // Serial.print("Back : ");
    // Serial.println(distance_01);
    if(distance_02<=distance_01)
    {
    if(distance_02!=-1 && distance_02<=20)
    {
      Serial.print("Hi,,,this is me balkpakna Robot , Distance : ");
      Serial.println(distance_02);
    }
    }
    else
    {
      if(distance_01!=-1 && distance_01<=15)
      {
        Serial.print("Hi,,,this is me backside Robot, Distance : ");
        Serial.println(distance_01);
      }
    }
  }
}