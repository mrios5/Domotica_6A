#include "MQTT.h"
  MQTT mqtt;
#define TEMP_TIME 2000
#define SERVO_TIME 5000

class Tareas {
  public:
    unsigned long task_2s = 0,
                  task_5s = 0,
                  task_10s = 0,
                  task_20s = 0,
                  currentMillis = 0;
  
  public:
  void _2s ( void );
  void _5s ( void );
  void _10s ( void );
  void _20s ( void );
  };

void Tareas::_2s ( void ){
  
  if( ( currentMillis - task_2s) >= TEMP_TIME){
    
      sensor.rfid();
      sensor.luz();
      sensor.temperatura();    
      task_2s = currentMillis;
    }
  }

void Tareas::_5s ( void ){
  
  if( ( currentMillis - task_5s) >= SERVO_TIME){
    
      actuators.pantallalcd();
      task_5s = currentMillis;
      
    }
  }

 void Tareas::_10s ( void ){
  
  if( ( currentMillis - task_10s) >= SERVO_TIME){
    
      RTC.get_time();
      MSD.JSON();
      
      task_10s = currentMillis; 
    }
  }

 void Tareas::_20s ( void ){
  
  if( ( currentMillis - task_20s) >= SERVO_TIME){
    
      mqtt.publish_MQTT();
      
      task_20s = currentMillis;
    }
  }
  

  
