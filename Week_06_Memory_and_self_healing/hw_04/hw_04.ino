unsigned long currentTime;
unsigned long prevTime = 0;

bool prevState = false;
bool currentState = false;
bool state = false;
bool toggle = false;

int arr[10];
int i = 0;
int count = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  currentState = digitalRead(2);
  currentTime = millis();
  if (currentState && !prevState) {
    state = true;
  }
  if (!state && currentTime - prevTime >= 2000) {
    arr[i] = analogRead(A2);
    i++;
    if (i >= 10) {
      i = 0;
    }
    if (count < 10) {
      count++;
    }
    prevTime = currentTime;
    toggle = !toggle;
    digitalWrite(13, toggle);
  }

  if (state) {

    int mx = arr[0];
    int mn = arr[0];
    long sum = 0;
    for (int j = 0; j < count; j++) {
      if (arr[j] > mx) {
        mx = arr[j];
      }
      if (arr[j] < mn) {
        mn = arr[j];
      }
      sum += arr[j];
    }
    double avg = (double)sum / count;
    Serial.println("       CRASH REPORT");
    Serial.print("Maximum Value    : ");
    Serial.println(mx);
    Serial.print("Minimum Value    : ");
    Serial.println(mn);
    Serial.print("Average Value    : ");
    Serial.println(avg);
    while (true) {
    }
  }
  prevState = currentState;
}