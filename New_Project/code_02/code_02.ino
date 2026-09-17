#include <Arduino.h>

const uint8_t SENSOR_PIN = 2;
unsigned long last_window_time = 0;

volatile int g_pulse_count = 0;

void countPulseISR();
void calculateIntensity(int totalPulses);

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countPulseISR, RISING);
}
void loop() {
  unsigned long current_time = millis();
  if (current_time - last_window_time >= 1000) {
    last_window_time = current_time;
    noInterrupts();
    int safe_pulse_count = g_pulse_count;
    g_pulse_count = 0;
    interrupts();
    calculateIntensity(safe_pulse_count);
  }
}
void countPulseISR() {
  g_pulse_count++;
}
void calculateIntensity(int totalPulses) {

  if (totalPulses == 0) {
    Serial.println(F("STABLE ⚪ (No Motion)"));
  } else if (totalPulses > 0 && totalPulses <= 5) {
    Serial.println(F("LOW 🟢 (Slight Shake / Footstep)"));
  } else if (totalPulses > 5 && totalPulses <= 20) {
    Serial.println(F("MEDIUM 🟡 (Normal Vibration / Engine Running)"));
  } else {
    Serial.println(F("HIGH 🔥 (Strong Impact / Sudden Shock!)"));
  }
}
