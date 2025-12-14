#include "serial_tank.h"
#include "Arduino.h"
#include "main.h"

// ------------------------------------------------------------
// Global variables for serial data reception
// ------------------------------------------------------------
unsigned char value_h, value_l;          // High and low byte from tank controller
unsigned int volume_value_local = 0;     // Combined water volume value

// ------------------------------------------------------------
// Function: init_serial_tank
// Purpose : Initialize serial communication with tank controller
// ------------------------------------------------------------
void init_serial_tank(void)
{
    // Initialize UART communication at 19200 baud rate
    Serial.begin(19200);

    // Send synchronization bytes (device-specific handshake)
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
}

// ------------------------------------------------------------
// Function: read_volume
// Purpose : Read current water volume from tank system
// Returns : Water volume as 16-bit unsigned integer
// ------------------------------------------------------------
unsigned int read_volume(void)
{
    // Request volume data from tank controller
    Serial.write(VOLUME);

    // Wait until high byte is received
    while (!Serial.available());
    value_h = Serial.read();

    // Wait until low byte is received
    while (!Serial.available());
    value_l = Serial.read();

    // Combine high and low bytes into a 16-bit value
    volume_value_local = (value_h << 8) | value_l;

    return volume_value_local;
}

// ------------------------------------------------------------
// Function: enable_inlet
// Purpose : Enable water inlet valve
// ------------------------------------------------------------
void enable_inlet(void)
{
    Serial.write(INLET_VALVE);   // Select inlet valve
    Serial.write(ENABLE);        // Enable command
}

// ------------------------------------------------------------
// Function: disable_inlet
// Purpose : Disable water inlet valve
// ------------------------------------------------------------
void disable_inlet(void)
{
    Serial.write(INLET_VALVE);   // Select inlet valve
    Serial.write(DISABLE);       // Disable command
}

// ------------------------------------------------------------
// Function: enable_outlet
// Purpose : Enable water outlet valve
// ------------------------------------------------------------
void enable_outlet(void)
{
    Serial.write(OUTLET_VALVE);  // Select outlet valve
    Serial.write(ENABLE);        // Enable command
}

// ------------------------------------------------------------
// Function: disable_outlet
// Purpose : Disable water outlet valve
// ------------------------------------------------------------
void disable_outlet(void)
{
    Serial.write(OUTLET_VALVE);  // Select outlet valve
    Serial.write(DISABLE);       // Disable command
}
