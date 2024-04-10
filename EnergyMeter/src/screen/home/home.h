#ifndef home_h
#define home_h

#include <Adafruit_SSD1306.h>

// 
void home_screen_setup(Adafruit_SSD1306* pDisplay);

//
void home_screen_render(Adafruit_SSD1306* pDisplay);

//
void home_screen_keypad(int key);

#endif