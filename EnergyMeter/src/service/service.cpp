#include "service.h"
#include "display/display.h"
#include "current/current.h"
#include "temperature/temperature.h"
#include "keymap/keymap.h"
#include "relay/relay.h"

#include <Wire.h>

void service_setup()
{
    // I2C
    Wire.begin(PIN_SDA, PIN_SCL);

    //
    ssd1306_setup();
    current_setup();
    temp_setup();
    keymap_setup();
    relay_setup();
}

void service_loop()
{    
    keymap_loop();
    relay_loop();
}

void service_loop_sensor()
{
    // sensor readings are blocking operation 
    // so separate it from the rest
    current_loop();
    temp_loop();

    //
    ssd1306_loop();
}