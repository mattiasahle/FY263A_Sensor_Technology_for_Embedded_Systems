#define POT_PIN A0
#define PWM_PIN 9
#define PWM_MAX 255
#define ADC_MAX 1023

int potValue;
int pwmValue;

void setup() {
  Serial.begin(9600);
  pinMode(POT_PIN, INPUT);
  pinMode(PWM_PIN, OUTPUT);
}

void loop() {
  potValue = analogRead(POT_PIN);
  pwmValue = map(potValue, 0, ADC_MAX, 0, PWM_MAX);
  print();
  analogWrite(PWM_PIN, pwmValue);
  delay(50);
}

void print() {
  Serial.print(potValue);
  Serial.print("\t");
  Serial.println(pwmValue);
}
