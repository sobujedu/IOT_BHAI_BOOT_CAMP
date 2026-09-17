#include <Arduino.h>

const uint8_t SENSOR_PIN = 3;
const uint8_t INDICATOR_PIN = 9;

unsigned long last_sample_time = 0;
unsigned long last_alert_time = 0;

int last_debounced_state = LOW;
bool state = false;
void checkVibrationSensor();

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(INDICATOR_PIN, OUTPUT);
  digitalWrite(INDICATOR_PIN, state);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - last_sample_time >= 20) {
    last_sample_time = currentTime;
    checkVibrationSensor();
  }
}

void checkVibrationSensor() {
  unsigned long currentTime = millis();
  int currentState = digitalRead(SENSOR_PIN);
  if (currentState == HIGH && last_debounced_state == LOW) {

    if (currentTime - last_alert_time >= 150) {
      last_alert_time = currentTime;

      state = !state;
      digitalWrite(INDICATOR_PIN, state);
    }
  }
  last_debounced_state = currentState;
}
