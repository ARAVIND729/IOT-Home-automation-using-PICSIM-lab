#include "ldr.h"        // Header file for LDR-related function declarations
#include "Arduino.h"   // Core Arduino definitions (pinMode, analogRead, etc.)
#include "main.h"       // Project-wide pin definitions and macros

// ------------------------------------------------------------
// Function: init_ldr
// Purpose : Initialize hardware required for LDR-based lighting
// ------------------------------------------------------------
void init_ldr(void)
{
    // Configure the garden light pin as OUTPUT (PWM capable pin)
    pinMode(GARDEN_LIGHT, OUTPUT);
}

// Global variables
unsigned int Light_intensity;   // Stores raw LDR ADC value (0–1023)
unsigned int duty;              // Stores PWM duty cycle value (0–255)

// ------------------------------------------------------------
// Function: brightness_control
// Purpose : Automatically control LED brightness based on ambient light
// ------------------------------------------------------------
void brightness_control(void)
{
    // Read light intensity from LDR sensor
    // ADC range: 0 (dark) to 1023 (bright)
    Light_intensity = analogRead(LDR_SENSOR);

    // Convert ADC value (0–1023) to PWM range (0–255)
    // Inverted logic:
    //   - High ambient light  -> lower LED brightness
    //   - Low ambient light   -> higher LED brightness
    duty = 255 - (Light_intensity / 4);

    // Apply PWM signal to garden light to control brightness
    analogWrite(GARDEN_LIGHT, duty);

    // Delay to reduce rapid brightness fluctuation
    // NOTE: This blocks execution and is not ideal for real-time systems
    delay(100);
}
