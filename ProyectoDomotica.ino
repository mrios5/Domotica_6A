//este es el bueno
#include "DataLogger.h"
#include "skeleton.h"
  
void setup() {
  Serial.begin(115200);

  //DataLogger Guarda la informacion
  MSD.MicroSD_init();//
  RTC.RTC_init(); //

  //MQTT 
  mqtt.set_MQTT_server();
  mqtt.setup_Wifi();

  //RFID
  sensor.setup_rfid();

  //LCD y MQ7
  actuators.pantallalcd_setup();

  //BH1750 y LED
  sensor.setup_luz();

  //DHT11 y VENTILADOR
  sensor.setup_temperatura();
}

void loop() {

  //Milis
  tasks.currentMillis = millis( );
  tasks._20s ();
  tasks._10s ();
  tasks._5s ();
  tasks._2s ();

  //Reconect MQTT
  mqtt.reconnect_MQTT ();
}
