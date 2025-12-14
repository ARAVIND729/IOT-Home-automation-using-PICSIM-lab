/*************************************************************
 Title         : Home Automation using Blynk
 Description   : 
   - Control light brightness using LDR
   - Monitor temperature
   - Monitor water level in tank
   - Control heater, cooler, inlet and outlet via Blynk App
 Hardware      :
   - Arduino UNO
   - Temperature sensor
   - LED + LDR module
   - Serial water tank level sensor
   - Ethernet module
   - I2C LCD
 Platform      :
   - Blynk Cloud + Blynk Mobile App
*************************************************************/

// -------- Blynk Cloud Credentials --------
#define BLYNK_TEMPLATE_ID "TMPL3Yu2svG31"
#define BLYNK_TEMPLATE_NAME "HOME AUTOMATION"
#define BLYNK_AUTH_TOKEN "tUOeDiDs2ojvb-che9DapOvjReDRaICq"

// -------- Required Libraries --------
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#include "main.h"                 // Pin definitions and macros
#include "temperature_system.h"   // Temperature sensor functions
#include "ldr.h"                  // Brightness control using LDR
#include "serial_tank.h"          // Water tank volume measurement

#include <Wire.h>
#include <LiquidCrystal_I2C.h>    // I2C LCD library

// -------- LCD Configuration --------
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16x2 LCD at I2C address 0x27

// -------- System State Variables --------
bool heater_sw, inlet_sw, outlet_sw, cooler_sw; // Device ON/OFF states
unsigned int volume_tank_value;                // Tank water volume

BlynkTimer timer;   // Non-blocking timer for periodic tasks

// ============================================================
//                  BLYNK VIRTUAL PIN HANDLERS
// ============================================================

// ---- Cooler Control ----
BLYNK_WRITE(COOLER_V_PIN)
{
    cooler_sw = param.asInt();     // Read switch value from Blynk
    cooler_control(cooler_sw);     // Control cooler hardware

    lcd.setCursor(8, 0);
    if (cooler_sw)
        lcd.print("CLR_ON ");
    else
        lcd.print("CLR_OFF");
}

// ---- Heater Control ----
BLYNK_WRITE(HEATER_V_PIN)
{
    heater_sw = param.asInt();     // Read heater switch state
    heater_control(heater_sw);     // Control heater relay

    lcd.setCursor(8, 0);
    if (heater_sw)
        lcd.print("HTR_ON ");
    else
        lcd.print("HTR_OFF");
}

// ---- Water Inlet Control ----
BLYNK_WRITE(INLET_V_PIN)
{
    inlet_sw = param.asInt();

    if (inlet_sw)
    {
        enable_inlet();            // Open inlet valve
        lcd.setCursor(8, 1);
        lcd.print("IN_FL_ON ");
    }
    else
    {
        disable_inlet();           // Close inlet valve
        lcd.setCursor(8, 1);
        lcd.print("IN_FL_OFF");
    }
}

// ---- Water Outlet Control ----
BLYNK_WRITE(OUTLET_V_PIN)
{
    outlet_sw = param.asInt();

    if (outlet_sw)
    {
        enable_outlet();           // Open outlet valve
        lcd.setCursor(8, 1);
        lcd.print("OT_FL_ON ");
    }
    else
    {
        disable_outlet();          // Close outlet valve
        lcd.setCursor(8, 1);
        lcd.print("OT_FL_OFF");
    }
}

// ============================================================
//                      SUPPORT FUNCTIONS
// ============================================================

// ---- Send Sensor Data to Blynk ----
void update_temperature_reading()
{
    Blynk.virtualWrite(TEMPERATURE_GAUGE, read_temperature());
    Blynk.virtualWrite(WATER_VOL_GAUGE, volume_tank_value);
}

// ---- Automatic Heater Safety ----
// Turns OFF heater if temperature exceeds threshold
void handle_temp(void)
{
    if (read_temperature() > 35 && heater_sw)
    {
        heater_sw = 0;
        heater_control(0);
        Blynk.virtualWrite(HEATER_V_PIN, 0);

        lcd.setCursor(8, 0);
        lcd.print("HTR_OFF");
    }
}

// ---- Automatic Tank Management ----
// Turns ON inlet when tank volume exceeds limit
void handle_tank(void)
{
    if (volume_tank_value > 2000 && inlet_sw == 0)
    {
        inlet_sw = 1;
        enable_inlet();
        Blynk.virtualWrite(INLET_V_PIN, 1);

        lcd.setCursor(8, 1);
        lcd.print("IN_FL_ON ");
    }
}

// ============================================================
//                          SETUP
// ============================================================
void setup(void)
{
    // Initialize all subsystems
    init_ldr();
    init_temperature_system();
    init_serial_tank();

    // Connect to Blynk Cloud
    Blynk.begin(BLYNK_AUTH_TOKEN);

    // LCD Initialization
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.home();
    lcd.setCursor(0, 0);
    lcd.print("HOME AUTOMATION");
    delay(1000);
    lcd.clear();

    // Periodic sensor update every 1 second
    timer.setInterval(1000, update_temperature_reading);
}

// ============================================================
//                          LOOP
// ============================================================
float temp;

void loop(void)
{
    Blynk.run();        // Handle Blynk communication
    timer.run();        // Handle scheduled tasks

    brightness_control();   // Adjust LED brightness using LDR

    // Read temperature and apply protection logic
    temp = read_temperature();
    handle_temp();

    // Read water volume and manage inlet
    volume_tank_value = read_volume();
    handle_tank();

    // Display temperature on LCD
    lcd.setCursor(0, 0);
    lcd.print("T=");
    lcd.print(temp);

    // Display tank volume on LCD
    lcd.setCursor(0, 1);
    lcd.print("V=");
    lcd.print(volume_tank_value);
}
