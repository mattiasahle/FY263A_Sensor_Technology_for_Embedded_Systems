#define potPin A0
#define pwmPin 9
#define pwmMax 255

int potValue;
int pwmValue;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  potValue = analogRead(potPin);
  pwmValue = map(potValue, 0, 1023, 0, pwmMax);
  print();
  analogWrite(pwmPin, 255);
}

void print() {
  Serial.print(potValue);
  Serial.print("\t");
  Serial.println(pwmValue);
}
