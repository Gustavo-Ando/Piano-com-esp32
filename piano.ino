#define buzzer 25
#define threshold 3000

const int keys = 12;
const int keyPin[keys] = {36, 39, 34, 35, 32, 33, 15, 26, 27, 14, 12, 13};

int keyVoltage[keys] = {0, 0, 0};
int keyPlaying[keys] = {0, 0, 0};

void setup() {
  for(int i = 0; i < keys; i++){
    pinMode(keyPin[keys], INPUT);
  }
  //pinMode(buzzer, OUTPUT);

 ledcAttach(buzzer, 44100, 8);
  // Frequency * 2^resoultion < 80Mhz

  Serial.begin(9600);

}

void loop() {
  unsigned long time = micros();
  float height = 0;
  for(int i = 0; i < keys; i++){
    keyVoltage[i] = analogRead(keyPin[i]);
    //Serial.print(i);
    //Serial.print(": ");
    //Serial.println(keyVoltage[i]);
    if(keyVoltage[i] < threshold) {
      height += sin(220.0 * pow(2.0, i/12.0) * 6.2831855 * time / 1000000.0);
  
    }
  }

  height /= 12.0 + 1;
  height += 0.5;

  int duty = height * 255.0;
  ledcWrite(buzzer, duty);
  //Serial.println(duty);
  //if(anyPlaying == 0) noTone(buzzer);

}

// [TODO]
// poliphonia
// ADSR (?)
