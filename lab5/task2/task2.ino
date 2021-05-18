#define pwmPin 9
#define pwmMax 255

void setup() {
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  analogWrite(pwmPin, pwmMax * 0.5);
}
