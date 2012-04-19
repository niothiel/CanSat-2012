#define BUZZER_PIN 10
#define FREQUENCY 2000

void initBuzzer() {
  //pinMode(BUZZER_PIN, OUTPUT);
}

void turnBuzzerOn() {
  tone(BUZZER_PIN, FREQUENCY);
}

void turnBuzzerOff() {
  noTone(BUZZER_PIN);
}
