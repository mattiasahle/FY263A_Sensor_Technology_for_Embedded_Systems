#define PWM_PIN 9
#define PWM_MAX 255

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  analogWrite(PWM_PIN, PWM_MAX * 0.5);
}

void loop() {

}
