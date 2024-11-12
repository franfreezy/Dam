#include <HX711_ADC.h>
#if defined(ESP8266) || defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

// pins:
const int HX711_dout = 4; // mcu > HX711 dout pin
const int HX711_sck = 5;  // mcu > HX711 sck pin
#include <HX711_ADC.h>
#if defined(ESP8266) || defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;
unsigned long t = 0;

String damMass()
{
    static boolean newDataReady = 0;
    const int serialPrintInterval = 3000;
    static unsigned long t = 0;

    if (LoadCell.update())
        newDataReady = true;

    if (newDataReady)
    {
        if (millis() > t + serialPrintInterval)
        {
            int loadMass = LoadCell.getData();  
            newDataReady = 0;
            t = millis();
            return String(loadMass);  
        }
    }

    
    if (Serial.available() > 0)
    {
        char inByte = Serial.read();
        if (inByte == 't')
            LoadCell.tareNoDelay();
    }

   
    if (LoadCell.getTareStatus() == true)
    {
        Serial.println("Tare complete");
    }

    return ""; 
}
