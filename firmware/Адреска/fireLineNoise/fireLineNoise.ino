// настройки ленты
#define NUM_LEDS 30    // количество светодиодов
#define LED_PIN 13      // пин ленты

// настройки пламени
#define HUE_GAP 40      // заброс по hue
#define FIRE_STEP 25    // шаг изменения "языков" пламени
#define HUE_START 5     // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define HUE_COEF 0.7    // коэффициент цвета огня (чем больше - тем дальше заброс по цвету)
#define SMOOTH_K 0.15   // коэффициент плавности огня
#define MIN_BRIGHT 50   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 180     // мин. насыщенность
#define MAX_SAT 255     // макс. насыщенность

// для разработчиков
#include <FastLED.h>
#define ORDER_GRB       // порядок цветов ORDER_GRB / ORDER_RGB / ORDER_BRG
#define COLOR_DEBTH 3   // цветовая глубина: 1, 2, 3 (в байтах)
// на меньшем цветовом разрешении скетч будет занимать в разы меньше места,
// но уменьшится и количество оттенков и уровней яркости!

// ВНИМАНИЕ! define настройки (ORDER_GRB и COLOR_DEBTH) делаются до подключения библиотеки!
#include <microLED.h>

LEDdata leds[NUM_LEDS];  // буфер ленты типа LEDdata (размер зависит от COLOR_DEBTH)
microLED strip(leds, NUM_LEDS, LED_PIN);  // объект лента

#define ZONE_AMOUNT NUM_LEDS   // количество зон
byte zoneValues[ZONE_AMOUNT];
byte zoneRndValues[ZONE_AMOUNT];
int counter = 0;

CRGBPalette16 firePalette;

// ленивая жопа
#define FOR_i(from, to) for(int i = (from); i < (to); i++)
#define FOR_j(from, to) for(int j = (from); j < (to); j++)

void setup() {
  strip.setBrightness(255);
  randomSeed(analogRead(0));
  counter = random(0, 30000);

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
}

void loop() {
  fireTick();
}

void fireTick() {
  static uint32_t prevTime;

  // задаём направление движения огня
  if (millis() - prevTime > 30) {
    prevTime = millis();
    FOR_i(0, NUM_LEDS) {
      //leds[i] = getFireColor(inoise8(i * FIRE_STEP, i * FIRE_STEP, counter));
      strip.setHEX(i, getPixColor(ColorFromPalette(firePalette, (inoise8(i * 15, counter)), 255, LINEARBLEND)));
    }
    counter += 20;
    strip.show();
  }
}

CRGB getFireColor(int val) {
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return CHSV(
           HUE_START + map(val, 0, 255, 0, HUE_GAP),                                  // H
           constrain(map(val, 0, 255, MAX_SAT, MIN_SAT), 0, 255),       // S
           constrain(map(val, 0, 255, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}

uint32_t getPixColor(CRGB thisPixel) {
  return (((uint32_t)thisPixel.r << 16) | (thisPixel.g << 8) | thisPixel.b);
}
