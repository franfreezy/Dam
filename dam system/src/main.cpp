#include <Arduino.h>
#include "loadcell.h"
#include "tiltsensor.h"
#include "ultrasonic.h"
#include "actuators.h"
#include "comms.h"

void setup()
{
  Serial.begin(57600);
  //setup gsm
   Serial3.begin(9600); 

  
  Serial.println("Initializing modem...");
  modem.restart();

  
  Serial.print("Connecting to safaricom...");
  if (!modem.gprsConnect(apn, user, pass)) {
    Serial.println(" failed");
    while (true);
  }
  Serial.println(" success");

  // Configure the MQTT server and connect
  mqtt.setServer(mqttServer, mqttPort);
  mqtt.setCallback(mqttCallback);

  connectToMqtt();

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
  damMass();
  triggerSpillway();
}