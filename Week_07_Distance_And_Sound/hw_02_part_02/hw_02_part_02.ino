const int trigpin = 9;
const int echopin = 10;

unsigned long duration;
unsigned long time_01 = 0;

int distance;
int arr[5];

double avg;
int sum = 0;

int i = 0;

void sortArray(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void setup()
{
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  if (millis() - time_01 >= 100)
  {
    time_01 = millis();
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echopin, HIGH, 30000);
    distance = duration * 0.0343 / 2;
    arr[i] = distance;
    i++;
    if (i == 5)
    {
      sortArray(arr, 5);
      sum = 0;
      for (int j = 1; j < 4; j++)
      {
        sum += arr[j];
      }
      avg = (double)sum / 3.0;
      Serial.print("Cleaned Average : ");
      Serial.println(avg);
      i = 0;
    }
  }

  if (distance < 20)
  {
    digitalWrite(6, HIGH);
    digitalWrite(3, LOW);
  }
  else
  {
    digitalWrite(6, LOW);
    digitalWrite(3, HIGH);
  }
}