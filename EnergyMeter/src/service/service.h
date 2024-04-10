#ifndef Service_h
#define Service_h

// I2C
#define PIN_SCL 16
#define PIN_SDA 17

//
void service_setup();

///
void service_loop();
void service_loop_sensor();

#endif