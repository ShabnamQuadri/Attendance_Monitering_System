#define BUZZER_PIN 8

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
  delay(500);
}
