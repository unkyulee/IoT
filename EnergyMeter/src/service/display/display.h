#ifndef display_h
#define display_h

//
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

// 
#define INIT_SCREEN 0
#define HOME_SCREEN 1

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// display
void ssd1306_setup();
void ssd1306_loop();

#endif