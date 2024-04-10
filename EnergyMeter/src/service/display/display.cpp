#include "display.h"
#include "app/app.h"
#include "service/service.h"

// screens
#include "screen/init/init.h"
#include "screen/home/home.h"

//
#include <SPI.h>
#include <Wire.h>

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

//
Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET);

//
void ssd1306_setup()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        app_log("SSD1306 allocation failed\n");
        return;
    }
    app_log("SSD1306 display ok\n");

    //
    JsonDocument &app = app_status();
    app["screen"] = INIT_SCREEN;
}

//
void ssd1306_loop()
{
    static int screen_prev = -1;
    static unsigned int last = 0;
    if (millis() - last > 1000)
    {
        //
        last = millis();

        JsonDocument &app = app_status();
        int screen = app["screen"].as<int>();

        // INIT SCREEN
        if (screen == INIT_SCREEN)
        {
            // setup only once
            if (screen != screen_prev)
                init_screen_setup(&display);

            // loop
            init_screen_render(&display);
            //
        }
        else if (screen == HOME_SCREEN)
        {
            // setup only once
            if (screen != screen_prev)
                home_screen_setup(&display);

            // loop
            home_screen_render(&display);
            //
        }

        //
        screen_prev = screen;
    }
}
