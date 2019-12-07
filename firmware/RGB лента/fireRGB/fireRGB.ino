// настройки ленты
#include <GyverRGB.h>
GRGB strip(3, 5, 6);  // куда подключены цвета (R, G, B)

// настройки пламени
#define HUE_START 0     // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define HUE_GAP 10      // коэффициент цвета огня (чем больше - тем дальше заброс по цвету)
#define SMOOTH_K 0.15   // коэффициент плавности огня
#define MIN_BRIGHT 80   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 255     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность

void setup() {
  strip.setBrightness(255);
  strip.setDirection(REVERSE);
}

void loop() {
  fireTick();
}

void fireTick() {
  static uint32_t prevTime, prevTime2;
  static byte fireRnd = 0;
  static float fireValue = 0;

  // задаём направление движения огня
  if (millis() - prevTime > 100) {
    prevTime = millis();
    fireRnd = random(0, 10);
  }
  // двигаем пламя
  if (millis() - prevTime2 > 20) {
    prevTime2 = millis();
    fireValue = (float)fireValue * (1 - SMOOTH_K) + (float)fireRnd * 10 * SMOOTH_K;
    strip.setHSV(
      constrain(map(fireValue, 20, 60, HUE_START, HUE_START + HUE_GAP), 0, 255),   // H
      constrain(map(fireValue, 20, 60, MAX_SAT, MIN_SAT), 0, 255),       // S
      constrain(map(fireValue, 20, 60, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
    );
  }
}
