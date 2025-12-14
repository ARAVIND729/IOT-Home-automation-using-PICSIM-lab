#ifndef MAIN_H
#define MAIN_H

// ------------------------------------------------------------
// Generic logic level definitions
// ------------------------------------------------------------
#define ON    1      // Logical HIGH / Device ON
#define OFF   0      // Logical LOW  / Device OFF

// ------------------------------------------------------------
// Blynk Virtual Pin Assignments
// ------------------------------------------------------------
// These virtual pins map Blynk widgets (buttons, gauges, terminal)
// to the firmware logic.

#define TEMPERATURE_GAUGE       V1   // Displays temperature value
#define COOLER_V_PIN            V2   // Button widget for cooler control
#define HEATER_V_PIN            V0   // Button widget for heater control
#define WATER_VOL_GAUGE         V3   // Displays water tank volume
#define INLET_V_PIN             V4   // Button widget for inlet valve
#define OUTLET_V_PIN            V5   // Button widget for outlet valve
#define BLYNK_TERMINAL_V_PIN    V6   // Terminal widget for logs/debug

// ------------------------------------------------------------
// LCD Configuration Note
// ------------------------------------------------------------
// I2C LCD address and dimensions are defined in the source file
// (LiquidCrystal_I2C lcd(0x27, 16, 2);)

#endif  // MAIN_H
