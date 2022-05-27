#define MICROSD_PIN 5
#define EXTENSION ".json"
#include <ArduinoJson.h>
#include <Wire.h>
#include "RTClib.h"
  RTC_DS1307 rtc;

#include <SPI.h>
#include <SD.h>
File MicroSD_File;
#include "RTC.h"
  DS1307_RTC RTC;
  
#include "MicroSD.h"
  MicroSD MSD;
