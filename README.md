![PROJECT_PHOTO](https://github.com/AlexGyver/FireFX/blob/master/proj_img.jpg)
# Огонь на светодиодной ленте и Arduino
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
Сборник огненных эффектов для адресных светодиодов и матриц
- **RGB лента**
	- **fireRGB** - 0мерный огонь на обычной RGB ленте
- **Адреска**
	- **fireLine**: каждый светодиод - независимый источник огня (мой алгоритм)
	- **fireLinear**: линейный огонь вдоль ленты
	- **fireLineNoise**: каждый светодиод - независимый источник огня (Perlin)
	- **fireLinePerlin**: плавный огонь на шуме Перлина
	- **fireLineZones**: огонь с фиксированным количеством зон
- **Матрица из адрески**
	- **fireMatrixNoise**: 2D огонь (как лава)
	- **fireMatrixReal**: идеальный для матрицы 16х16 огонь
	- **fireMatrixNoiseWave**: мультяшный огонь
- Страница проекта на сайте: https://alexgyver.ru/firefx/

<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **firmware** - прошивки для Arduino
- **schemes** - схемы подключения компонентов

<a id="chapter-2"></a>
## Схемы
![SCHEME](https://github.com/AlexGyver/FireFX/blob/master/schemes/rgbstripDrv.jpg)
![SCHEME](https://github.com/AlexGyver/FireFX/blob/master/schemes/ws5-1.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
- Arduino NANO https://ali.ski/eO-ZIT  https://ali.ski/aZg0m
- Адресная лента https://ali.ski/haLd0T
- Лента на Giant4
	- 60 лед/м
	- 30 лед/м
- Матрица 16×16
	- https://ali.ski/fcjc8
	- https://ali.ski/P3tSQk
	- https://ali.ski/Wf7rG
- БП 5V (брать 3A (15W) минимум)
	- https://ali.ski/27-VxW 
	- https://ali.ski/yBw61
	- https://ali.ski/EkIXu
- RGB лента 
	- Лента Giant4 https://giant4.ru/5050-120.html
	- Лента Али RGB 120 https://ali.ski/NjsMky  https://ali.ski/P1E3kM
- Драйвер для RGB
	- LED amplifier https://ali.ski/nuGa- https://ali.ski/tW5cI https://ali.ski/ihOy9B
	- MOSFET IRF3205 (10 шт) https://ali.ski/MjIa4g https://ali.ski/MhEbD
	- Резисторы (100R и 10k) https://ali.ski/gVTFO https://ali.ski/4f9GN
- БП 12V для RGB 
	- https://ali.ski/VXZvJc 
	- https://ali.ski/ah5DW

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* **Подключить внешнее питание 5 Вольт**
* Подключить плату к компьютеру
* Файл/Настройки, вставить ссылку http://arduino.esp8266.com/stable/package_esp8266com_index.json в в текст-бокс для дополнительных ссылок для менеджера плат
* Открыть Инструменты/Плата/Менеджер плат…, найти esp8266 by ESP8266 Community, установить версию 2.5.0
* Открыть Инструменты, настроить Плату, Порт и другие параметры как на скриншоте
* Загрузить прошивку

## Настройки в коде

	
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)