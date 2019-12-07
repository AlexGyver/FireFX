// настройки ленты
#define M_WIDTH 42      // ширина матрицы
#define M_HEIGHT 8      // высота матрицы
#define LED_PIN 4       // пин ленты
#define LED_BRIGHT 200  // яркость

// настройки пламени
#define FIRE_SCALE 35   // масштаб огня
#define HUE_GAP 40      // заброс по hue
#define FIRE_STEP 15    // шаг изменения "языков" пламени
#define HUE_START 5     // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define HUE_COEF 0.7    // коэффициент цвета огня (чем больше - тем дальше заброс по цвету)
#define SMOOTH_K 0.15   // коэффициент плавности огня
#define MIN_BRIGHT 50   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 180     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность

#define ORDER_GRB       // порядок цветов ORDER_GRB / ORDER_RGB / ORDER_BRG
#define COLOR_DEBTH 3   // цветовая глубина: 1, 2, 3 (в байтах)

#include <microLED.h>

#define NUM_LEDS M_WIDTH * M_HEIGHT
LEDdata leds[NUM_LEDS];  // буфер ленты типа LEDdata

microLED matrix(leds, LED_PIN, M_WIDTH, M_HEIGHT, ZIGZAG, LEFT_BOTTOM, DIR_RIGHT);  // объект матрица
// тип матрицы: ZIGZAG - зигзаг, PARALLEL - параллельная
// угол подключения: LEFT_BOTTOM - левый нижний, LEFT_TOP - левый верхний, RIGHT_TOP - правый верхний, RIGHT_BOTTOM - правый нижний
// направление ленты из угла подключения: DIR_RIGHT - вправо, DIR_UP - вверх, DIR_LEFT - влево, DIR_DOWN - вниз
// шпаргалка по настройке матрицы в папке docs в библиотеке

#define NUM_LEDS M_WIDTH*M_HEIGHT

#include <FastLED.h>
int counter = 0;
CRGBPalette16 firePalette;
byte fireVals[NUM_LEDS];

// ленивая жопа
#define FOR_i(from, to) for(int i = (from); i < (to); i++)
#define FOR_j(from, to) for(int j = (from); j < (to); j++)

void setup() {
  matrix.setBrightness(LED_BRIGHT);  // яркость (0-255)
  firePalette = CRGBPalette16(
                  getFireColor(0 * 16),
                  getFireColor(1 * 16),
                  getFireColor(2 * 16),
                  getFireColor(3 * 16),
                  getFireColor(4 * 16),
                  getFireColor(5 * 16),
                  getFireColor(6 * 16),
                  getFireColor(7 * 16),
                  getFireColor(8 * 16),
                  getFireColor(9 * 16),
                  getFireColor(10 * 16),
                  getFireColor(11 * 16),
                  getFireColor(12 * 16),
                  getFireColor(13 * 16),
                  getFireColor(14 * 16),
                  getFireColor(15 * 16)
                );
  FOR_i(0, NUM_LEDS) {
    fireVals[i] = random(0, 255);
  }
}

void loop() {
  fireTick();
}

void fireTick() {
  static uint32_t prevTime = 0;
  if (millis() - prevTime > 30) {
    prevTime = millis();
    FOR_i(0, NUM_LEDS) {
      matrix.setHEX(i, getPixColor(ColorFromPalette(
                                     firePalette,
                                     fireVals[i],
                                     255,
                                     LINEARBLEND
                                   )));
      if (fireVals[i] > 5) fireVals[i] -= 5;
      else fireVals[i] = 255;
    }
    matrix.show();
  }
}

uint32_t getPixColor(CRGB thisPixel) {
  return (((uint32_t)thisPixel.r << 16) | (thisPixel.g << 8) | thisPixel.b);
}

CRGB getFireColor(int val) {
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return CHSV(
           HUE_START + map(val, 0, 255, 0, HUE_GAP),                    // H
           constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
           constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}
