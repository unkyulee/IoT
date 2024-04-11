#include "home.h"
#include "app/app.h"
#include "service/service.h"
#include "service/display/display.h"

//
void home_screen_setup(Adafruit_SSD1306 *pDisplay)
{
        // Clear the buffer
        pDisplay->clearDisplay();
        pDisplay->display();
}

//
void home_screen_render(Adafruit_SSD1306 *pDisplay)
{
        //
        JsonDocument &app = app_status();

        //
        pDisplay->clearDisplay();

        // Toolbar
        // ON/OFF
        pDisplay->setTextSize(2);
        pDisplay->setCursor(0, 0);
        pDisplay->setTextColor(SSD1306_WHITE);

        bool relay = app["relay"].as<bool>();
        if (relay)
        {
                pDisplay->print("ON");
        }
        else
        {
                pDisplay->print("OFF");
        }

        // network information
        pDisplay->setTextSize(1);

        const char *ssid = app["network"]["ssid"].as<const char *>();
        String IP = app["network"]["IP"].as<String>();

        pDisplay->setTextWrap(false);
        pDisplay->setCursor(45, 0);
        pDisplay->print(ssid);

        pDisplay->setCursor(45, 8);
        pDisplay->println(IP.c_str());

        // Content

        // Current and Power
        pDisplay->setTextSize(1);
        pDisplay->setCursor(16, 16);
        pDisplay->print("WATT");

        pDisplay->setTextSize(3);
        pDisplay->setCursor(0, 28);
        pDisplay->printf("%.0lf", app["Irms"].as<double>() * 230);

        pDisplay->setTextSize(1);
        pDisplay->setCursor(0, 54);
        pDisplay->printf("%.2lf A", app["Irms"].as<double>());

        // Temperature
        pDisplay->setTextSize(1);
        pDisplay->setCursor(80, 20);
        pDisplay->printf("%.1lf %cC\n", app["Temperature"].as<double>(), 247);
        
        // Pressure
        pDisplay->setCursor(80, 30);
        pDisplay->printf("%.0lf hPa\n", app["Pressure"].as<double>());

        // Humidity
        pDisplay->setCursor(80, 40);
        pDisplay->printf("%.0lf %%", app["Humidity"].as<double>());

        // render
        pDisplay->display();
}

//
void home_screen_keypad(int key) {}