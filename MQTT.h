#include <WiFi.h>
  WiFiClient ESP32_WIFI;
  
#include <PubSubClient.h>
  PubSubClient MQTT_ESP32 (ESP32_WIFI);
 
const char* HOTSPOT_WIFI= "manu";
const char* HOTSPOT_PWD = "manuelrios";
const char* MQTT_SERVER = "test.mosquitto.org";
#define MQTT_PORT 1883
#define TOPIC "/6A/HOUSE/GARDEN"

class MQTT {

  public:
  public:
    void subscribe_MQTT ( void );
    void publish_MQTT ( void );
    void reconnect_MQTT ( void );
    void setup_Wifi ( void );
    void set_MQTT_server ( void );
  };
  
void MQTT::set_MQTT_server ( void ){
    MQTT_ESP32.setServer(MQTT_SERVER, MQTT_PORT);
  }
void MQTT::subscribe_MQTT ( void ){
  
  }

void MQTT::publish_MQTT ( void ){

    String hola = "La verdad es dura, pero...";
    Serial.println("Mensaje enviado correctamente");
    MQTT_ESP32.publish( TOPIC, MSD.json_string.c_str() );
  }

void MQTT::reconnect_MQTT ( void ){
  
  if (!MQTT_ESP32.connected()) {
    
    while (!MQTT_ESP32.connected()) {
      
    Serial.print("Conectado nuevamente al servidor...");
    // Attempt to connect
    if (MQTT_ESP32.connect("6A/E1")){
      Serial.println("Cliente conectado!");
      // Subscribe
      //MQTT_ESP32.subscribe("esp32/output");
      
    } else {
      
      Serial.print("failed, rc=");
      Serial.print(MQTT_ESP32.state());
      Serial.println(" try again in 5 seconds");
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  }
  MQTT_ESP32.loop();
  
  }

void MQTT::setup_Wifi ( void ){

  delay ( 10 );
  WiFi.begin ( HOTSPOT_WIFI, HOTSPOT_PWD ); 
  Serial.println ( "Configurando WiFi...." );
  while ( WiFi.status ( ) != WL_CONNECTED ) {
    
    delay(500);
    Serial.print(".");
    
  }
    Serial.println ( "WiFi Configurado! :D, Ip: ");
    Serial.println  (WiFi.localIP());
  }
