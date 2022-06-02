//Libreria para usar el servomotor
#include <Servo.h> 

//Definicion de lo que se necesita para trabajar con el servomotor
#define servo_pin 4
Servo myservo;
int angle = 0;

//Libreria para la pantalla LCD
#include <LiquidCrystal_I2C.h>

//Definicion de lo que se necesita para trabajar con la pantalla LCD
int lcdColumns = 16; //Columnas
int lcdRows = 2; //Filas
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 


class Actuadores {

  public:
    void servo_setup (void); //setup del servomotor
    void servo (void); //acciones del servomotor
    void pantallalcd_setup (void); //setup del servomotor
    void pantallalcd (void); //acciones del servomotor
  };

 void Actuadores::servo_setup ( void ){
  
  myservo.attach(servo_pin);
  
  }
  
 void Actuadores::servo ( void ){

  // abrir puerta
  for(angle = 0; angle < 95; angle += 1)
  {                          
    myservo.write(angle);                       
  } 

  delay(3000);
  
  // cerrar puerta
  for(angle = 95; angle>=1; angle-=5)
  {                                
    myservo.write(angle);                     
  } 
  
  }

  void Actuadores::pantallalcd_setup ( void ){
    // initialize LCD
    lcd.begin();
    // turn on LCD backlight                      
    lcd.backlight();
  }
  
 void Actuadores::pantallalcd ( void ){
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(36);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1000);
  
  if(sensorValue < 2100){
      lcd.setCursor(0,0);
      lcd.print("Todo Piola");
      delay(300);
      lcd.clear();
  }else if(sensorValue > 2100){
      lcd.setCursor(0,0);
      lcd.print("Fuga de gas!!");
      delay(300);
      lcd.clear();
      }
  }
