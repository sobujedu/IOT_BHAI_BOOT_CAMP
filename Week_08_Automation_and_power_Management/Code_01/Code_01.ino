#include <avr/sleep.h>
const byte LDR_DO_PIN = 2;
const byte LED_PIN = 13;
volatile bool wakeup = false;

void wakeupISR()
{
  wakeup = true;
}

void gotoSleep()
{
  wakeup = false;

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  // Dark = HIGH, Light = LOW
  // তাই HIGH -> LOW হলে wake up
  attachInterrupt(
    digitalPinToInterrupt(LDR_DO_PIN),
    wakeupISR,
    FALLING
  );

  delay(50);

  sleep_cpu();

  sleep_disable();

  detachInterrupt(digitalPinToInterrupt(LDR_DO_PIN));
}

void setup()
{
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_DO_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.println("Arduino UNO Wake on Light Ready...");

  delay(1000);
}

void loop()
{
  Serial.println("Going To Sleep...");

  // Sleep যাওয়ার আগে LED 2 বার blink
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(200);

    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  delay(500);

  // Arduino sleep
  gotoSleep();

  // Light আসার পরে এখানে আসবে
  Serial.println("Wake up due to light change!");

  // Wake-up indication
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(150);

    digitalWrite(LED_PIN, LOW);
    delay(150);
  }
}
