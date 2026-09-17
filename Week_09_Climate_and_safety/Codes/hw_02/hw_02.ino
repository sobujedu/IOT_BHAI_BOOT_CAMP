#include <avr/wdt.h>
#include <dht.h>
#include <EEPROM.h>

#define outPin 9
#define ADDRESS 20

const int green_led = 4;
const int yellow_led = 3;
const int red_led = 6;
const int buzzer_pin = 5;
const int ldr_pin = 10;
const int trigPin = 11;
const int echoPin = 12;
const int button_pin = 2;

bool r_state = false;
bool plus = true;

long duration;
int distance;
int pot_val;
int i = 0;
float t;

dht DHT;

bool interruptTriggered = false;
volatile bool buttonPressed = false;

unsigned long now;
unsigned long g_prev = 0;
unsigned long t_prev = 0;
unsigned long buzzer_prev = 0;
unsigned long r_prev = 0;
unsigned long a_prev = 0;
unsigned long b_prev = 0;

bool state = false;

void emergencyButtonPressed() {
  buttonPressed = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(ldr_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button_pin, INPUT);

  digitalWrite(trigPin, LOW);
  digitalWrite(buzzer_pin, LOW);

  interruptTriggered = EEPROM.read(ADDRESS);

  attachInterrupt(
    digitalPinToInterrupt(button_pin),
    emergencyButtonPressed,
    RISING
  );

  wdt_enable(WDTO_2S);
}

void loop() {
  wdt_reset();

  now = millis();
  pot_val = analogRead(A1);

  // Green LED Blink
  if (now - g_prev >= 1000 && !interruptTriggered) {
    state = !state;
    digitalWrite(green_led, state);
    g_prev = now;
  }

  // DHT11
  if (now - t_prev >= 2000) {
    DHT.read11(outPin);
    t = DHT.temperature;

    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.println(" C | ");

    Serial.print("Pot Value : ");
    Serial.println(pot_val);

    t_prev = now;
  }

  // LDR
  int ldrVal = digitalRead(ldr_pin);

  if (ldrVal == LOW)
    digitalWrite(yellow_led, HIGH);
  else
    digitalWrite(yellow_led, LOW);

  // Distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2;

  if (distance < 30 && distance != 0 && !interruptTriggered) {

    int beep_interval = map(distance, 1, 30, 80, 600);

    tone(buzzer_pin, 1000, beep_interval);

    if (distance < 15) {

      for (int i = 1; i <= 255; i++) {
        analogWrite(red_led, i);
      }

      for (int i = 255; i >= 0; i--) {
        analogWrite(red_led, i);
      }

    }

  } else {
    analogWrite(red_led, 0);
    i = 0;
    noTone(buzzer_pin);
  }

  // Button Pressed
  if (buttonPressed) {

    buttonPressed = false;

    EEPROM.update(ADDRESS, true);

    if (pot_val >= 600 && pot_val <= 650) {

      EEPROM.update(ADDRESS, false);

      digitalWrite(buzzer_pin, LOW);
      digitalWrite(red_led, LOW);

      r_state = false;
    }

    interruptTriggered = EEPROM.read(ADDRESS);
  }

  // Critical LockDown
  if (t > 30 || interruptTriggered) {

    tone(buzzer_pin, 1000, 100);
    digitalWrite(green_led, LOW);

    if (now - r_prev >= 200) {
      r_state = !r_state;
      digitalWrite(red_led, r_state);
      r_prev = now;
    }
  }
}