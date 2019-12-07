#define SMOOTH_K 0.08   // коэффициент плавности огня
float value = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  fireTick();  
}

void fireTick() {
  static uint32_t prevTime, prevTime2;
  static byte rndValue = 0;

  if (millis() - prevTime > 100) {
    prevTime = millis();
    rndValue = random(0, 10);
  }

  if (millis() - prevTime2 > 20) {
    prevTime2 = millis();
    value = (float)value * (1 - SMOOTH_K) + (float)rndValue * 10 * SMOOTH_K;
    Serial.println(value);
  }
}
