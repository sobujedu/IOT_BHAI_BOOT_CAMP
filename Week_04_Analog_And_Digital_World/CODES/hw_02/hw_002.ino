void setup() {

  pinMode(8, INPUT);

  pinMode(6, OUTPUT);

  pinMode(A2, INPUT);

  Serial.begin(9600);

}

bool currentState = false;

bool prevState = false;

bool state = false;

double voltage;

int adc;

void loop() {

  int pinVal = analogRead(2);

  currentState = digitalRead(8);

  if(pinVal<900)

  {

    state = false;

  }

  if (currentState && !prevState && pinVal > 900) 

  {

    state = true;

    if (state && pinVal > 900)

    {

      analogWrite(6, 255);

      Serial.println("Danger Acknowledged");

    }

  }

  if (pinVal <= 511)

    analogWrite(6, 0);

  else if (pinVal > 511 && pinVal <= 900) 

  {

    voltage = ((pinVal-511) * 5.0) / 388.0;

    adc = (voltage * 255.0) / 5.0;

    analogWrite(6, adc);

  } 

  else if (pinVal > 900 && !state)

  {

    Serial.println("Status : Warning");

    analogWrite(6, 255);

    delay(100);

    analogWrite(6, 0);

  } 

  prevState = currentState;

  if(pinVal<900)

  {

  Serial.print("Sensor : ");

  Serial.println(pinVal);

  Serial.print("PWM : ");

  Serial.println(adc);

  }

  delay(1000);

}