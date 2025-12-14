#ifndef TEMPERATURE_SYSTEM_H
#define TEMPERATURE_SYSTEM_H

// ------------------------------------------------------------
// GPIO Pin Definitions
// ------------------------------------------------------------
// Digital output pins used to control heater and cooler relays
#define HEATER                 5     // Heater control pin
#define COOLER                 4     // Cooler control pin

// ------------------------------------------------------------
// Analog Sensor Pin Definition
// ------------------------------------------------------------
// Analog input pin connected to temperature sensor (LM35 assumed)
#define TEMPERATURE_SENSOR     A0

// ------------------------------------------------------------
// Function Prototypes
// ------------------------------------------------------------
// Reads temperature sensor and returns temperature in degree Celsius
float read_temperature(void);

// Initializes GPIO pins for heater and cooler
void init_temperature_system(void);

// Turns cooler ON or OFF
void cooler_control(bool control);

// Turns heater ON or OFF
void heater_control(bool control);

#endif  // TEMPERATURE_SYSTEM_H
