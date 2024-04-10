#include "current.h"
#include "app/app.h"

//
#include <EmonLib.h>
EnergyMonitor emon;

#define CT_PIN 34
#define INIT_SIZE 20000
#define SAMPLES 400

// CT sensor
void current_setup()
{
    // Current: input pin, calibration.
    pinMode(CT_PIN, INPUT_PULLUP);
    analogReadResolution(ADC_BITS);
    emon.current(CT_PIN, 30.0);
    emon.calcIrms(INIT_SIZE);

}

void current_loop()
{
    static unsigned int last = 0;
    if (millis() - last > 1000)
    {
        //
        last = millis();

        double Irms = emon.calcIrms(SAMPLES); // Calculate Irms only
        JsonDocument &app = app_status();
        app["Irms"] = Irms;
    }
}