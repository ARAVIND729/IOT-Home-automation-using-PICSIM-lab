#ifndef SERIAL_TANK_H
#define SERIAL_TANK_H

// ------------------------------------------------------------
// Digital Output Command Codes
// ------------------------------------------------------------
// Used to select and control inlet and outlet valves
#define INLET_VALVE   0x00    // Command identifier for inlet valve
#define OUTLET_VALVE  0x01    // Command identifier for outlet valve

// ------------------------------------------------------------
// Digital Sensor Command Codes
// ------------------------------------------------------------
// Used to read float switch status (not used in current code)
#define HIGH_FLOAT    0x10    // High-level float switch sensor
#define LOW_FLOAT     0x11    // Low-level float switch sensor

// ------------------------------------------------------------
// Analog Sensor Command Codes
// ------------------------------------------------------------
// Used to request water volume data from tank controller
#define VOLUME        0x30    // Water volume request command

// ------------------------------------------------------------
// Control Commands
// ------------------------------------------------------------
#define ENABLE        0x01    // Enable actuator
#define DISABLE       0x00    // Disable actuator

// ------------------------------------------------------------
// Function Prototypes
// ------------------------------------------------------------
void init_serial_tank(void);     // Initialize serial communication
void enable_inlet(void);         // Enable inlet valve
void enable_outlet(void);        // Enable outlet valve
void disable_inlet(void);        // Disable inlet valve
void disable_outlet(void);       // Disable outlet valve
unsigned int read_volume(void);  // Read tank water volume

#endif  // SERIAL_TANK_H
