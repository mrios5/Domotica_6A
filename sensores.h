//Librerias para usar el sensor RFID
#include <SPI.h>
#include <MFRC522.h>

//Definiciones para usar RFID
#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);   //Creacion de la instancia MFRC522.

//Librerias para usar el sensor BH1750 sensor de iluminucida
#include <BH1750.h>  // incluye libreria BH1750
#include <Wire.h> // incluye libreria para bus I2C

//Definiciones para usar el sensor BH1750
BH1750 sensors;    // crea objeto con nombre sensor
#define LED 4   // reemplaza ocurrencia de LED por 2
#define UMBRAL 30 // reemplaza ocurrencia de UMBRAL por 30

//Librerias para usar el sensor DHT11 (temperatura)
#include <DHT.h>

//Definiciones para usar el sensor DHT11 (temperatura)
#define DHTPIN 27 // Definimos el pin digital donde se conecta el sensor
const int VENTI = 26; // Definimos el pin digital donde se conecta el ventilador
#define DHTTYPE DHT11 // Definiendo el tipo de sensor
DHT dht(DHTPIN, DHTTYPE); // Inicializamos el sensor DHT11

class Sensores {
  public:
    void setup_rfid ( void ); //setup lector rfid
    void rfid ( void ); //acciones lector rfid
    void setup_luz ( void ); //setup sensor de luz
    void luz ( void ); //acciones sensor de luz
    void setup_temperatura ( void ); //setup sensor de temperatura
    void temperatura ( void ); //acciones sensor de temperatura
  };

//Funciones para usar el lector RFID
 void Sensores::setup_rfid ( void ){
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Aproxima la tarjeta del lector...");
  Serial.println();
  
  }

  //ejecucion de RFID
 void Sensores::rfid ( void ){

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "13 97 F9 12") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Acceso autorizado");
    actuators.servo();
  }
 
 else   {
    Serial.println("Acceso denegado");
    delay(3000);
  }
  
  }

//Funciones para el sensor de Luz junto con el led
 void Sensores::setup_luz ( void ){
  Wire.begin();   // inicializa bus I2C
  sensors.begin(); // inicializa sensor con valores por defecto
  pinMode(LED, OUTPUT); // pin 2 como salida
  }

  void Sensores::luz ( void ){
  unsigned int lux = sensors.readLightLevel(); // lee y almacena lectura de sensor
  Serial.print("Nivel: ");  // muestra texto
  Serial.print(lux);    // muestra valor de variable lux
  Serial.println(" lx");  // muestra texto y salto de linea

  if (lux < UMBRAL){    // si lectura de sensor es menor a UMBRAL
    digitalWrite(LED, HIGH);  // enciende LED
  }
  else if (lux > UMBRAL + 20){  // si lectura de sensor es mayor a UMBRAL+20
    digitalWrite(LED, LOW); // apaga LED
  }

  delay(1000);      // demora de 1 seg.
  }

//Funciones para el sensor DHT11 junto con el "VENTILADOR"
 void Sensores::temperatura ( void ){
  
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
 
  // Comprobamos si ha habido algún error en la lectura
  if ( isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
  
  // Funcion para prender ventilador 
  if (t > 30){
    // si la temperatura es mayor a 24 se pone en bajo en relay
     digitalWrite(VENTI, HIGH);
  }else{
     digitalWrite(VENTI, LOW);
  }

 //Impresion de la temperatura en puerto serial
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C ");  
  }

 void Sensores::setup_temperatura ( void ){
  dht.begin();
  pinMode(VENTI, OUTPUT);  //definir pin como salida
  digitalWrite(VENTI, LOW); // se manda seal a ventilador en bajo  
  }
