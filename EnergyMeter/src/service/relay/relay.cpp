#include "relay.h"
#include "app/app.h"
#include "service/service.h"

#define PIN_RELAY 15

void relay_setup()
{
    // RELAY
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, HIGH);
}

void relay_loop()
{
    static bool last_status = false;
    static unsigned int last = millis();
    if (millis() - last > 1000)
    {
        last = millis();

        //
        JsonDocument &app = app_status();
        bool status = app["relay"].as<bool>();
        if (last_status != status)
        {
            if (status == true)
            {
                // turn on relay
                digitalWrite(PIN_RELAY, LOW);
                app_log("Relay on\n");
            }
            else
            {
                // turn off relay
                digitalWrite(PIN_RELAY, HIGH);
                app_log("Relay off\n");
            }

            last_status = status;
        }
    }
}