#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

Servo myServo_01;
Servo myServo_02;


// ========================================================
// Ultrasonic 01
// Back Side Sensor
// ========================================================

const int trigpin_01 = 2;
const int echopin_01 = 5;

unsigned long duration_01;
int distance_01;


// ========================================================
// Ultrasonic 02
// Front Side Sensor
// ========================================================

const int trigpin_02 = 4;
const int echopin_02 = 3;

unsigned long duration_02;
int distance_02;


// ========================================================
// Timing
// ========================================================

unsigned long time_01 = 0;


// ========================================================
// Speaker
// ========================================================

SoftwareSerial dfSerial(10, 9);  // Arduino RX, TX
DFRobotDFPlayerMini dfPlayer;


// ========================================================
// Speaker Function
// ========================================================

void speaker() {

  Serial.println("SPEAKER PLAYING");
  dfPlayer.play(1);
}


// ========================================================
// Servo 01 Function
// Front Servo
// ========================================================

void servo_01() {

  Serial.println("FRONT DETECTED - Servo 01");

  for (int i = 0; i <= 180; i++) {
    myServo_01.write(i);
    delay(5);
  }

  int x = 2;

  delay(400);

  while (x--) {

    for (int i = 180; i >= 150; i--) {
      myServo_01.write(i);
      delay(5);
    }

    delay(200);

    for (int i = 150; i <= 180; i++) {
      myServo_01.write(i);
      delay(5);
    }

    delay(200);
  }

  for (int i = 180; i >= 0; i--) {
    myServo_01.write(i);
    delay(5);
  }
}


// ========================================================
// Servo 02 Function
// Back Servo
// ========================================================

void servo_02() {

  Serial.println("BACK DETECTED - Servo 02");

  for (int i = 0; i <= 180; i++) {
    myServo_02.write(i);
    delay(5);
  }

  delay(300);

  servo_01();

  for (int i = 180; i >= 0; i--) {

    myServo_02.write(i);
    delay(5);
  }

  myServo_02.write(0);
}


// ========================================================
// Setup
// ========================================================

void setup() {

  // -------------------- Back Sensor --------------------

  pinMode(trigpin_01, OUTPUT);
  pinMode(echopin_01, INPUT);


  // -------------------- Front Sensor --------------------

  pinMode(trigpin_02, OUTPUT);
  pinMode(echopin_02, INPUT);


  digitalWrite(trigpin_01, LOW);
  digitalWrite(trigpin_02, LOW);


  // -------------------- Servo --------------------

  myServo_01.attach(6);
  myServo_02.attach(7);


  // Initial position

  myServo_01.write(0);
  myServo_02.write(0);


  // -------------------- Serial --------------------

  Serial.begin(9600);

  dfSerial.begin(9600);


  // -------------------- DFPlayer --------------------

  if (!dfPlayer.begin(dfSerial)) {

    Serial.println("DFPlayer NOT FOUND");

  } else {

    Serial.println("DFPlayer READY");

    dfPlayer.volume(100);
  }
}


// ========================================================
// Loop
// ========================================================

void loop() {

  if (millis() - time_01 >= 100) {


    // ====================================================
    // BACK SIDE SENSOR
    // ====================================================

    digitalWrite(trigpin_01, LOW);
    delayMicroseconds(2);

    digitalWrite(trigpin_01, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigpin_01, LOW);

    duration_01 = pulseIn(echopin_01, HIGH, 30000);

    if (duration_01 == 0) {

      distance_01 = -1;

    } else {

      distance_01 = duration_01 * 0.0343 / 2;
    }


    delayMicroseconds(100);


    // ====================================================
    // FRONT SIDE SENSOR
    // ====================================================

    digitalWrite(trigpin_02, LOW);
    delayMicroseconds(2);

    digitalWrite(trigpin_02, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigpin_02, LOW);

    duration_02 = pulseIn(echopin_02, HIGH, 30000);

    if (duration_02 == 0) {

      distance_02 = -1;

    } else {

      distance_02 = duration_02 * 0.0343 / 2;
    }


    time_01 = millis();


    // ====================================================
    // PRINT DISTANCES
    // ====================================================

    Serial.print("Front: ");

    if (distance_02 == -1) {

      Serial.print("No Echo");

    } else {

      Serial.print(distance_02);
      Serial.print(" cm");
    }


    Serial.print("    Back: ");


    if (distance_01 == -1) {

      Serial.println("No Echo");

    } else {

      Serial.print(distance_01);
      Serial.println(" cm");
    }


    // ====================================================
    // DETECTION LOGIC
    // ====================================================

    bool frontDetected = false;
    bool backDetected = false;


    // -------------------- Front Detection --------------------

    if (distance_02 != -1 && distance_02 <= 20) {

      frontDetected = true;
    }



    // -------------------- Back Detection --------------------

    if (distance_01 != -1 && distance_01 <= 15) {

      backDetected = true;
    }


    // ====================================================
    // ACTION
    // ====================================================

    if (backDetected) {
      speaker();
      servo_02();

    }

    else if (frontDetected) {

      speaker();
      servo_01();
    }
  }
}