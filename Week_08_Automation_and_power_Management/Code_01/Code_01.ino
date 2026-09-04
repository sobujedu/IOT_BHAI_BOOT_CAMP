#include<avr/sleep.h>
#include<avr/power.h>

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
  attachInterrupt(digitalPinToInterrupt(LDR_DO_PIN),wakeupISR,LOW);
  delay(50);
  sleep_cpu();
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(LDR_DO_PIN));
}
void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  pinMode(LDR_DO_PIN,INPUT);
  digitalWrite(LED_PIN,LOW);
  Serial.println("Arduino UNO Wake on Light Ready...");
  delay(1000);
}
void loop()
{
  Serial.println("Going To Sleep...");
  for(int i=0;i<2;i++)
  {
    digitalWrite(LED_PIN,HIGH);
    delay(200);
    digitalWrite(LED_PIN,LOW);
    delay(200);
  }

  delay(500);
  gotoSleep();

  Serial.println("Wake up due to light change!");
  for(int i=0;i<5;i++)
  {
    digitalWrite(LED_PIN,HIGH);
    delay(150);
    digitalWrite(LED_PIN,LOW);
    delay(150);
  }
}