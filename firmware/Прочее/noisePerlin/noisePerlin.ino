#include <FastLED.h>
#define SMOOTH_K 0.05   // коэффициент плавности огня

void setup() {
  Serial.begin(9600);
}

float zoneValues = 0;
void loop() {
  static int counter = 0;
  Serial.println(inoise8(counter, counter));
  counter += 15;
  delay(100);
}
