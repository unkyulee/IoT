#include "sd.h"
#include "app/app.h"
//
#include <SPI.h>
#include <FS.h>
#include <SD.h>

#define SD_CS 21
#define SPI_MOSI      23 
#define SPI_MISO      19
#define SPI_SCK       18

//
void SD_setup()
{
    // Initialize SPI bus for microSD Card
    //SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

    if (!SD.begin(SD_CS))
    {
        Serial.println("Card Mount Failed");
        return;
    }
    Serial.println("SD Device Initialized");
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }
    Serial.println("SD Card detected");

    // mark the status that SD card is ready
    JsonDocument &app = app_status();
    app["SD"] = true;
}

///
void SD_loop() {}
