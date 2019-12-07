// настройки ленты
#define NUM_LEDS 100    // количество светодиодов
#define LED_PIN 13      // пин ленты

// настройки зон
#define ZONE_AMOUNT 4   // количество зон
#define ZONE_K 0.08     // плавность движения зон
#define ZONE_MAX_SHIFT 10

// настройки пламени
#define HUE_START 5     // начальный цвет огня (0 красный, 80 зелёный, 140 молния, 190 розовый)
#define HUE_COEF 0.7    // коэффициент цвета огня (чем больше - тем дальше заброс по цвету)
#define SMOOTH_K 0.15   // коэффициент плавности огня
#define MIN_BRIGHT 90   // мин. яркость огня
#define MAX_BRIGHT 255  // макс. яркость огня
#define MIN_SAT 200     // мин. насыщенность
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

#define ZONE_SIZE NUM_LEDS / ZONE_AMOUNT
float zoneValues[ZONE_AMOUNT];
byte zoneRndValues[ZONE_AMOUNT];
float zoneShift[ZONE_AMOUNT - 1];
int8_t zoneRND[ZONE_AMOUNT - 1];

// ленивая жопа
#define FOR_i(from, to) for(int i = (from); i < (to); i++)
#define FOR_j(from, to) for(int j = (from); j < (to); j++)

void setup() {
  strip.setBrightness(255);
}

void loop() {
  fireTick();
  randomizeZones();
}

void randomizeZones() {
  static uint32_t prevTime, prevTime2;

  // задаёт направление движения зон
  if (millis() - prevTime >= 800) {
    prevTime = millis();
    FOR_i(0, ZONE_AMOUNT - 1) {
      if (abs(zoneShift[i] - zoneRND[i]) < 2)
        zoneRND[i] = random(-ZONE_MAX_SHIFT, ZONE_MAX_SHIFT);
    }
  }

  // движение зон
  if (millis() - prevTime2 >= 50) {
    prevTime2 = millis();
    FOR_i(0, ZONE_AMOUNT - 1) {
      zoneShift[i] += (zoneRND[i] - zoneShift[i]) * ZONE_K;
    }
  }
}

void fireTick() {
  static uint32_t prevTime, prevTime2;

  // задаём направление движения огня
  if (millis() - prevTime > 100) {
    prevTime = millis();
    FOR_i(0, ZONE_AMOUNT) {
      zoneRndValues[i] = random(0, 10);
    }
  }
  
  // двигаем пламя
  if (millis() - prevTime2 > 20) {
    prevTime2 = millis();
    int thisPos = 0, lastPos = 0;
    FOR_i(0, ZONE_AMOUNT) {
      zoneValues[i] = (float)zoneValues[i] * (1 - SMOOTH_K) + (float)zoneRndValues[i] * 10 * SMOOTH_K;
      //zoneValues[i] = (zoneRndValues[i] * 10 - zoneValues[i]) * SMOOTH_K;
      if (i < ZONE_AMOUNT - 1) thisPos += ZONE_SIZE + zoneShift[i];
      else thisPos = NUM_LEDS;
      if (thisPos > NUM_LEDS) break;

      // вывести огонь
      byte zoneHalf = (thisPos - lastPos) / 2;
      float valStep = (float)1 / zoneHalf;
      byte counter = 0;
      FOR_j(lastPos, lastPos + zoneHalf) {
        counter++;
        if (j > NUM_LEDS) break;
        leds[j] = getFireColor((float)zoneValues[i] * counter * valStep);
      }
      counter = 0;
      FOR_j(lastPos + zoneHalf, thisPos) {
        counter++;
        if (j > NUM_LEDS) break;
        leds[j] = getFireColor((float)zoneValues[i] * (zoneHalf - counter) * valStep);
      }

      // вывести цветные полосы
      //FOR_j(lastPos, thisPos) leds[j] = mHSV(i * 70, 255, 150);

      lastPos = thisPos;
    }
    strip.show();
  }
}

// возвращает цвет огня для одного пикселя
LEDdata getFireColor(int val) {
  // чем больше val, тем сильнее сдвигается цвет, падает насыщеность и растёт яркость
  return mHSV(
           HUE_START + val * HUE_COEF,                                  // H
           constrain(map(val, 20, 60, MAX_SAT, MIN_SAT), 0, 255),       // S
           constrain(map(val, 20, 60, MIN_BRIGHT, MAX_BRIGHT), 0, 255)  // V
         );
}
