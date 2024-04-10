#include "keymap.h"
#include "app/app.h"
#include "service/service.h"

#define KEY1 14
#define KEY2 27
#define KEY3 26
#define KEY4 25

#define INPUT_DELAY 100

void handleButtonPress1()
{
    JsonDocument &app = app_status();

    static unsigned int last = 0;
    if (millis() - last > 300)
    {
        last = millis();

        app["key1_pressed"] = true;
    }
}

void handleButtonPress2()
{
    JsonDocument &app = app_status();
    static unsigned int last = 0;
    if (millis() - last > 300)
    {
        last = millis();

        app["key2_pressed"] = true;
    }
}

void handleButtonPress3()
{
    JsonDocument &app = app_status();
    static unsigned int last = 0;
    if (millis() - last > 300)
    {
        last = millis();

        app["key3_pressed"] = true;
    }
}

void handleButtonPress4()
{
    JsonDocument &app = app_status();
    static unsigned int last = 0;
    if (millis() - last > 300)
    {
        last = millis();

        app["key4_pressed"] = true;
    }
}

void keymap_setup()
{
    pinMode(KEY1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(KEY1), handleButtonPress1, HIGH);

    pinMode(KEY2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(KEY2), handleButtonPress2, HIGH);

    pinMode(KEY3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(KEY3), handleButtonPress3, HIGH);

    pinMode(KEY4, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(KEY4), handleButtonPress4, HIGH);
}

void keymap_loop()
{
    static unsigned int last = millis();
    if (millis() - last > 100)
    {
        last = millis();

        JsonDocument &app = app_status();
        if (app["key1_pressed"].as<bool>() == true)
        {
            app_log("Key 1 pressed\n");
            app["key1_pressed"] = false;

            app["relay"] = true;
        }
        if (app["key2_pressed"].as<bool>() == true)
        {
            app_log("Key 2 pressed\n");
            app["key2_pressed"] = false;

            app["relay"] = false;
        }
        if (app["key3_pressed"].as<bool>() == true)
        {
            app_log("Key 3 pressed\n");
            app["key3_pressed"] = false;
        }
        if (app["key4_pressed"].as<bool>() == true)
        {
            app_log("Key 4 pressed\n");
            app["key4_pressed"] = false;
        }
    }
}