#define MICROSD_PIN 5
#define EXTENSION ".json"
#include <ArduinoJson.h> //libreria para el JSON
#include <Wire.h> //
#include "RTClib.h" //Libreria para el reloj
  RTC_DS1307 rtc;

#include <SPI.h> //protocolo spi
#include <SD.h>
File MicroSD_File;
#include "RTC.h"
  DS1307_RTC RTC;
  
#include "MicroSD.h"
  MicroSD MSD;
