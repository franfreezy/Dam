#include <HX711_ADC.h>
#if defined(ESP8266) || defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

// pins:
const int HX711_dout = 2; // mcu > HX711 dout pin
const int HX711_sck = 4;  // mcu > HX711 sck pin
#include <HX711_ADC.h>
#if defined(ESP8266) || defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;
unsigned long t = 0;

void damMass()
{
    static boolean newDataReady = 0;
    const int serialPrintInterval = 3000; 

    
    if (LoadCell.update())
        newDataReady = true;

    
    if (newDataReady)
    {
        if (millis() > t + serialPrintInterval)
        {
            int i = LoadCell.getData();
            Serial.print("Load_cell output val: ");
            Serial.println(i);
            newDataReady = 0;
            t = millis();
        }
    }

    // receive command from serial terminal, send 't' to initiate tare operation:
    if (Serial.available() > 0)
    {
        char inByte = Serial.read();
        if (inByte == 't')
            LoadCell.tareNoDelay();
    }

    // check if last tare operation is complete:
    if (LoadCell.getTareStatus() == true)
    {
        Serial.println("Tare complete");
    }
}