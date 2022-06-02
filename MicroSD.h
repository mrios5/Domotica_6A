class MicroSD {

  public:
    String filename = "", json_string = "";

  public:
    void MicroSD_init ( void ); //Inicia el MicroSD
    void FileID ( void ); //Para poner un ID al archivo como un identificador
    void JSON ( void ); //Acomodar en JSON
    void JSON_SaveFile ( DynamicJsonDocument * ); //Para guardar el JSON
};


//Inicia el MicroSD
void MicroSD::MicroSD_init ( void ){

    while ( ! SD.begin ( MICROSD_PIN ) ) {
    Serial.println(F("La memoria fallo mi pana, o no la has puesto"));
      delay(1000);
    // don't do anything more:
  }
  Serial.println(F("Todo piola con la memoria"));
    
  
  }

//Para poner un ID al archivo como un identificador
void MicroSD::FileID ( void ) {
  RTC.get_time();
  filename = '/';
  if( RTC.dia  < 10) filename += '0';
  filename += RTC.dia;
  
  filename += '-';
  if( RTC.mes  < 10) filename += '0';
  filename += RTC.mes;
  
  filename += '-';
  if( RTC.ano  < 10) filename += '0';
  filename += RTC.ano;
  filename += EXTENSION;
  
  }

//Acomodar en JSON
void MicroSD::JSON ( void ) {
//se mandan a llamar los datos que se van a guardar
  DynamicJsonDocument obj(1024);
    obj["Temperatura"] = 35;
    RTC.format_date( );
    RTC.format_time( );
    obj["fecha"] = RTC.fecha.c_str();
    obj["tiempo"] = RTC.tiempo.c_str();
    JSON_SaveFile ( &obj );  
  }

//para guardar en JSON
void MicroSD::JSON_SaveFile ( DynamicJsonDocument *obj ) {
  FileID();
  json_string = "";
  //si el archivo no existe, el simple OPEN crearia el archivo por defecto
  MicroSD_File = SD.open ( filename, FILE_APPEND );
  if( MicroSD_File ){
      serializeJson(*obj, json_string);
      MicroSD_File.print( json_string );
      MicroSD_File.println( ',' );
      MicroSD_File.close();
    }
    else
    Serial.println("Se guardo con exito");
    delay (1000);
  
  }
