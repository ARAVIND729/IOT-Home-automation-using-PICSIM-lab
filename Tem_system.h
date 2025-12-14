#include "temperature_system.h"
#include "Arduino.h"
#include "main.h"

// ------------------------------------------------------------
// Global variable to store temperature value
// ------------------------------------------------------------
float temperature;

// ------------------------------------------------------------
// Function: init_temperature_system
// Purpose : Initialize GPIO pins for heater and cooler control
// ------------------------------------------------------------
void init_temperature_system(void)
{
    // Configure heater and cooler control pins as OUTPUT
    pinMode(HEATER, OUTPUT);
    pinMode(COOLER, OUTPUT);
}

// ------------------------------------------------------------
// Function: read_temperature
// Purpose : Read analog temperature sensor and return temperature
// Returns : Temperature value in degree Celsius
// ------------------------------------------------------------
float read_temperature(void)
{
    // Read ADC value from temperature sensor connected to A0
    // ADC range: 0–1023 (0–5V)
    // Conversion logic:
    //   Voltage = (ADC * 5.0) / 1024
    //   Sensor scale = 10 mV per °C (LM35 type)
    temperature = (((analogRead(A0) * (float)5 / 1024)) / (float)0.01);

    return temperature;
}

// ------------------------------------------------------------
// Function: cooler_control
// Purpose : Turn cooler ON or OFF
// ------------------------------------------------------------
void cooler_control(bool control)
{
    if (control)
    {
        digitalWrite(COOLER, HIGH);   // Turn cooler ON
    }
    else
    {
        digitalWrite(COOLER, LOW);    // Turn cooler OFF
    }
}

// ------------------------------------------------------------
// Function: heater_control
// Purpose : Turn heater ON or OFF
// ------------------------------------------------------------
void heater_control(bool control)
{
    if (control)
    {
        digitalWrite(HEATER, HIGH);   // Turn heater ON
    }
    else
    {
        digitalWrite(HEATER, LOW);    // Turn heater OFF
    }
}
