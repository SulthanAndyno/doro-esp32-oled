#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "anim.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // ESP32 default I2C pins: SDA=21, SCL=22
  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true) {
      delay(100);
    }
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  for (uint8_t i = 0; i < BITMAP_ANIM_FRAME_COUNT; i++) {
    const unsigned char *frame = (const unsigned char *)pgm_read_ptr(&bitmap_anim_frames[i]);

    display.clearDisplay();
    display.drawBitmap(0, 0, frame, BITMAP_ANIM_WIDTH, BITMAP_ANIM_HEIGHT, SSD1306_WHITE);
    display.display();

    delay(pgm_read_word(&bitmap_anim_delays[i]));
  }
}
