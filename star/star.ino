#include "application.h"
#include "neopixel.h"

#define PIXEL_PIN    D5
#define PIXEL_COUNT  50
#define PIXEL_OFFSET 8
#define PIXEL_TYPE   WS2812B
#define LIGHT_WHITE  0x555555
#define RED          0xFF0000
#define GREEN        0x00FF00
#define BLUE         0x0000FF
#define RED_GREEN    0xFFFF00
#define RED_BLUE     0xFF00FF
#define GREEN_BLUE   0x00FFFF

bool automatic = true;
int  counter   = 0;

Adafruit_NeoPixel leds = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

bool connectedToInternet = false;
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  leds.begin();
  leds.setBrightness(150); // 60% brightness (out of 255)
  setAll(0);
  leds.show();

  attemptConnection("white");

  RGB.control(true);
  RGB.color(0, 0, 0);
}

void attemptConnection(String delayMethod) {
  for (int i=0; i<2; i++) {
    if (!Spark.connected()) {
      Spark.connect();

      turnAll(LIGHT_WHITE);
      delay(5000);
    }
  }

  if (Spark.connected()) {
    connectedToInternet = true;

    Spark.function("setColor", setColor);
  }
}

void loop() {
  if (automatic) {
    if (counter < (350 - 192)) {
      turnAll(GREEN);
    } else {
      rainbow(counter);
    }

    counter = (counter + 1) % 350;
    delay(50);
  }
}

void wrap(int count) {
  for (int i=0; i<5*count; i++) {

    setAll(0);
    setStarPoint(i, GREEN);
    leds.show();

    delay(300);
  }
}

void setStarPoint(int point, unsigned long color) {
  for (int i=0; i<PIXEL_COUNT; i++) {
    if (point % 5 == ((i + PIXEL_OFFSET) % PIXEL_COUNT) / (PIXEL_COUNT / 5)) {
      leds.setPixelColor(i, color);
    }
  }
}

void turnAll(unsigned long color) {
  setAll(color);
  leds.show();
}

void setAll(unsigned long color){
  for (int i=0; i<PIXEL_COUNT; i++) {
    leds.setPixelColor(i, color);
  }
}

void rainbow(int step) {
  setStarPoint(0, rainbowOrder((step + 0)   % 191));
  setStarPoint(1, rainbowOrder((step + 38)  % 191));
  setStarPoint(2, rainbowOrder((step + 76)  % 191));
  setStarPoint(3, rainbowOrder((step + 115) % 191));
  setStarPoint(4, rainbowOrder((step + 153) % 191));
  leds.show();
}

uint32_t rainbowOrder(byte position) {
  if (position < 31)  {
    return leds.Color(0xFF, position * 8, 0);
  }
  else if (position < 63) {
    position -= 31;
    return leds.Color(0xFF - position * 8, 0xFF, 0);
  }
  else if (position < 95) {
    position -= 63;
    return leds.Color(0, 0xFF, position * 8);
  }
  else if (position < 127) {
    position -= 95;
    return leds.Color(0, 0xFF - position * 8, 0xFF);
  }
  else if (position < 159) {
    position -= 127;
    return leds.Color(position * 8, 0, 0xFF);
  }
  else {
    position -= 159;
    return leds.Color(0xFF, 0x00, 0xFF - position * 8);
  }
}

int setColor(String command) {
  if (command == "auto" || command == "off") {
    automatic = true;
    counter   = 0;
  }
  else {
    automatic = false;
    if (command == "red")        turnAll(RED);
    if (command == "green")      turnAll(GREEN);
    if (command == "blue")       turnAll(BLUE);
    if (command == "red_green")  turnAll(RED_GREEN);
    if (command == "red_blue")   turnAll(RED_BLUE);
    if (command == "green_blue") turnAll(GREEN_BLUE);
  }

  return 1;
}
