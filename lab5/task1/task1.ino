#define POT_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  Serial.println(analogRead(POT_PIN));
  delay(100);
}
