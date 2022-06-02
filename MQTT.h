#include <WiFi.h>
  WiFiClient ESP32_WIFI;
  
#include <PubSubClient.h>
  PubSubClient MQTT_ESP32 (ESP32_WIFI);
 
const char* HOTSPOT_WIFI= "manu"; //nombre del hotspot
const char* HOTSPOT_PWD = "manuelrios"; //la password para el hotspot
const char* MQTT_SERVER = "test.mosquitto.org"; //Broker al que nos conectamos
#define MQTT_PORT 1883 //puerto al que nos conectaremos
#define TOPIC "/6A/HOUSE/GARDEN" //topic al que nos vamos a suscribir

class MQTT {

  public:
  public:
    void subscribe_MQTT ( void ); //funcion para suscribirse al MQTT
    void publish_MQTT ( void ); //Publicar en MQTT
    void reconnect_MQTT ( void ); //Reconectar en MQTT
    void setup_Wifi ( void ); //Iniciar el WIFI
    void set_MQTT_server ( void );
  };
  
void MQTT::set_MQTT_server ( void ){
    MQTT_ESP32.setServer(MQTT_SERVER, MQTT_PORT);
  }
void MQTT::subscribe_MQTT ( void ){
  
  }

//Esta funcion publica en MQTT
void MQTT::publish_MQTT ( void ){
    Serial.println("Mensaje enviado correctamente");
    MQTT_ESP32.publish( TOPIC, MSD.json_string.c_str() );
  }

//En caso de que se desconecte funcion parfa reconectar el MQTT
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

//funcion para setear el WIFI, que se conecte a wifi
void MQTT::setup_Wifi ( void ){

  delay ( 10 );
  WiFi.begin ( HOTSPOT_WIFI, HOTSPOT_PWD ); 
  Serial.println ( "Configurando WiFi...." );
  while ( WiFi.status ( ) != WL_CONNECTED ) {
    
    delay(500);
    Serial.print(".");
    
  }
    Serial.println ( "WiFi Configurado! :D, Ip: ");
    //Saca y muestra la IP local a la que se conecto
    Serial.println  (WiFi.localIP());
  }
