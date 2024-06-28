#define buzzer 25
#define threshold 3000

const int keys = 12;
const int keyPin[keys] = {36, 39, 34, 35, 32, 33, 15, 26, 27, 14, 12, 13};

int keyPress[keys] = {0};
int keyRelease[keys] = {0};
int keyVoltage[keys] = {0};
int keyPlaying[keys] = {0};

void setup() {
  for(int i = 0; i < keys; i++){
    pinMode(keyPin[keys], INPUT);
  }

 ledcAttach(buzzer, 200000, 8);
  // Frequency * 2^resoultion < 80Mhz

  Serial.begin(9600);
}

void loop() {
  unsigned long time = micros();
  int notes = 0;
  float height = 0;
  for(int i = 0; i < keys; i++){
    keyVoltage[i] = analogRead(keyPin[i]);
    float h = sin(220.0 * pow(2.0, (i + 3)/12.0) * 6.2831855 * time / 1000000.0);
    if(keyVoltage[i] < threshold) {
      notes++;
      if(keyPlaying[i] == 0) keyPress[i] = time;
      keyPlaying[i] = 1;
      
      height += (30 - i)/30.0 * h * envelope(time - keyPress[i], 0);
    } else {
      if(keyPlaying[i] == 1) keyRelease[i] = time;
      keyPlaying[i] = 0;

      height += (30 - i)/30.0 * h * envelope(time - keyRelease[i], 1);
      if(envelope(time - keyRelease[i], 1) != 0) notes++;
    }
  }

  if(notes != 0 ) height /= notes * 12.0;
  height += 0.5;

  int duty = height * 255.0;
  ledcWrite(buzzer, duty);
}

float envelope(int time, int released){
  int attack = 5000;
  int decay = 10000;
  float sustain = .7;
  int release = 200000;

  if(!released){
    if(time < attack){
      return time/ (float) attack;
    } else if(time < attack + decay){
      float k = (sustain - 1.0)/decay;
      return k * time + sustain - (decay + attack) * k;
    } else {
      return sustain;
    }
  } else {
    if(time < release) return sustain - sustain * time/ (float) release;
    else return 0;
  }
}
