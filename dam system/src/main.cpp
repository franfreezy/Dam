#include <Arduino.h>
#include "loadcell.h"
#include "tiltsensor.h"
#include "ultrasonic.h"
#include "actuators.h"
#include "comms.h"

void setup()
{
  Serial.begin(57600);
  SerialAT.begin(GSM_BAUD);        
  
  delay(3000); 
  modem.restart();                  
  String modemInfo = modem.getModemInfo();
  Serial.println("Modem Info: " + modemInfo);
  Serial.println("Connecting to the GSM network...");
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    Serial.println("Failed to connect to GPRS.");
    return;
  }
  Serial.println("Connected to GPRS.");

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
  

  // loadcell configuration
  
  delay(10);
  LoadCell.begin();
  float calibrationValue;
  calibrationValue = 761.31;
  unsigned long stabilizingtime = 2000;
  boolean _tare = true;
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag())
  {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1)
      ;
  }
  else
  {
    LoadCell.setCalFactor(calibrationValue);
    delay(100);
  }
  delay(1000);
  LoadCell.tareNoDelay();

  // tilt sensor configuration

  pinMode(tiltsensordata, INPUT_PULLUP);
  
  // actuators initialisation
  pinMode(spillwayrelay, OUTPUT);
  pinMode(alarmrelay, OUTPUT);
}

void loop()
{ 
  Serial.println("in the loop");
  gsmMqtt();
  //damMass();
  //triggerSpillway();
}