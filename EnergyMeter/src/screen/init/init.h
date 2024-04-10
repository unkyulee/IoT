#ifndef init_h
#define init_h

#include <Adafruit_SSD1306.h>

// 
void init_screen_setup(Adafruit_SSD1306* pDisplay);

//
void init_screen_render(Adafruit_SSD1306* pDisplay);
void init_screen_render_SD_error(Adafruit_SSD1306* pDisplay);
void init_screen_render_network_status(Adafruit_SSD1306* pDisplay);

//
void init_screen_keypad(int key);

#endif