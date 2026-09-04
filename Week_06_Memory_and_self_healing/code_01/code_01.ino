// #include<EEPROM.h>
// #define BOOT_COUNT_ADDR 20
// int i = 0;
// void setup()
// {
//   Serial.begin(9600);
//   EEPROM.update(BOOT_COUNT_ADDR,125);
// }
// void loop()
// {
//   uint8_t count = EEPROM.read(BOOT_COUNT_ADDR);
//   Serial.print("Value in EEPROM : ");
//   Serial.println(count);
//   EEPROM.update(BOOT_COUNT_ADDR,count);
//   count++;
//   Serial.print("Value in SRAM : ");
//   Serial.println(i);
//   i++;
//   delay(1000);
// }
#include <avr/wdt.h>
const int ledPin = 9;
const int buttonPin = 2;
bool state = false;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  wdt_enable(WDTO_2S);
}
unsigned long now;
unsigned long prev = 0;
int ans = -1;
void loop() {
  bool buttonState = digitalRead(buttonPin);
  wdt_reset();
  now = millis();
  Serial.print("Button State : ");
  Serial.println(buttonState);
  if (buttonState == HIGH) {
    Serial.println("Enter The loop");
    while (1) {
    }
  }
  if (now - prev >= 1000) {
    state = !state;
    digitalWrite(ledPin, state);
    prev = now;
  }
  
}