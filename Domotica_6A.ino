#include "DataLogger.h" //libreria madre para guardar y mandar datos tanto a MQTT como a JSON
#include "skeleton.h" //libreria madre de los sensores, actuadores y tareas
  
void setup() {
  Serial.begin(115200);

  //DataLogger Guarda la informacion
  MSD.MicroSD_init();//Inicia SD
  RTC.RTC_init(); //Inicia el reloj

  //se conecta a MQTT 
  mqtt.set_MQTT_server();
  mqtt.setup_Wifi();

  //Inicializa el RFID 
  sensor.setup_rfid();

  //Para iniciar el LDC y el MQ7
  actuators.pantallalcd_setup();

  //BH1750 y LED
  sensor.setup_luz();

  //DHT11 y VENTILADOR
  sensor.setup_temperatura();
}

void loop() {

  //Funciones para que se ejecuten las tareas cada cierto tiempo
  tasks.currentMillis = millis( );
  tasks._20s (); //para el datalogger
  tasks._10s (); //para mandar a mqtt
  tasks._5s (); //para actuadores
  tasks._2s (); //para sensores

  //Funcion para reconectar a MQTT en caso de se desconecte 
  mqtt.reconnect_MQTT ();
}
