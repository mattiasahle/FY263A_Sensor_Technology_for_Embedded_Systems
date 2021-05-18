#define pwmPin 9
#define pwmMax 255

void setup() {
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, pwmMax * 0.5);
}

void loop() {

}
