#include "temperature.h"
#include "app/app.h"
#include "service/service.h"

//
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // I2C
#define SEALEVELPRESSURE_HPA (1013.25)

void temp_setup()
{
    unsigned status;
    status = bme.begin(0x76, &Wire);
    if (!status)
    {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x");
        Serial.println(bme.sensorID(), 16);
        Serial.print("   ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("   ID of 0x60 represents a BME 280.\n");
        Serial.print("   ID of 0x61 represents a BME 680.\n");
    }
}

void temp_loop()
{
    static unsigned int last = 0;
    if (millis() - last > 1000)
    {
        //
        last = millis();

        //
        JsonDocument &app = app_status();
        app["Temperature"] = bme.readTemperature();
        app["Pressure"] = bme.readPressure() / 100.0F;
        app["Humidity"] = bme.readHumidity();
    }
}