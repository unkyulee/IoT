#include "init.h"
#include "app/app.h"
#include "service/service.h"
#include "service/display/display.h"

//
void init_screen_setup(Adafruit_SSD1306 *pDisplay)
{
    // Clear the buffer
    pDisplay->clearDisplay();
    pDisplay->display();
}

//
void init_screen_keypad(int key)
{
}

//
void init_screen_render(Adafruit_SSD1306 *pDisplay)
{
    //
    JsonDocument &app = app_status();

    // check SD card status
    if (app["SD"].as<bool>() != true)
    {
        // SD CARD NOT LOADED
        init_screen_render_SD_error(pDisplay);
        return;
    }

    // display network status
    int network_status = app["network"]["status"].as<int>();
    if (network_status != 1)
    {
        // network is not connected (yet)
        init_screen_render_network_status(pDisplay);
        return;
    }

    else
    {
        // network is connected
        // move to home screen
        app["screen"] = HOME_SCREEN;
    }
}

void init_screen_render_SD_error(Adafruit_SSD1306 *pDisplay)
{
    //
    pDisplay->clearDisplay();

    //
    pDisplay->setTextSize(1);
    pDisplay->setCursor(0, 0);
    pDisplay->setTextColor(SSD1306_WHITE);
    pDisplay->println("SD CARD MISSING");

    // render
    pDisplay->display();
}

void init_screen_render_network_status(Adafruit_SSD1306 *pDisplay)
{
    //
    pDisplay->clearDisplay();

    //
    JsonDocument &app = app_status();
    int network_status = app["network"]["status"].as<int>();

    if (network_status == 0)
    {
        //
        // network is trying to connect
        //
        pDisplay->setTextSize(1);
        pDisplay->setCursor(0, 8);
        pDisplay->setTextColor(SSD1306_WHITE);

        static int progress = 1;
        pDisplay->print("Connecting ");
        for (int i = 0; i < progress; i++)
        {
            pDisplay->print(".");
        }
        progress++;
        if (progress > 6)
            progress = 1;
        pDisplay->println();

        // SSID
        const char *ssid = app["network"]["ssid"].as<const char *>();
        if (ssid != NULL)
        {
            pDisplay->println();
            pDisplay->println(ssid);
        }
    }

    else if (network_status == 2)
    {
        // soft AP is active
    }

    // render
    pDisplay->display();
}