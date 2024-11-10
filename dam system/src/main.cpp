#include <Arduino.h>
#include "loadcell.h"

void setup() {
  
  //loadcell configuration
  Serial.begin(57600); 
  delay(10);
  LoadCell.begin();
  float calibrationValue; 
  calibrationValue = 761.31; 
  unsigned long stabilizingtime = 2000; 
  boolean _tare = true; 
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); 
    delay(100);
    
  }
  delay(1000);
  LoadCell.tareNoDelay();
}

void loop() {
  damMass();

}