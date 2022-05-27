class DS1307_RTC {

  public:
    uint8_t hora, minuto, segundo, dia, mes;
    uint16_t ano;
    String fecha = "", tiempo = "";

  public:
    void RTC_init ( void );
    void get_time ( void );
    void format_date ( void );
    void format_time ( void );
};

void DS1307_RTC::RTC_init ( void ){

  while ( ! rtc.begin ( ) ) {
    Serial.println(F("Hijo, hay un error de reconocimiento en el RTC"));
    Serial.flush();
    delay(3000);
    
  }
  Serial.println(F("Todo piola con el RTC"));
  
  }
void DS1307_RTC::get_time ( void ){
    DateTime now = rtc.now();
    segundo = now.second ( );
    minuto = now.minute ( );
    hora = now.hour ( );
    dia = now.day ( );
    mes = now.month ( );
    ano = now.year ( );
    
  }
void DS1307_RTC::format_date ( void ){
  fecha = "";
  if ( dia < 10) fecha += '0';
  fecha += dia;
  fecha += '/';
  if ( mes < 10) fecha += '0';
  fecha += mes;
  fecha += '/';
  fecha += ano;
  }
void DS1307_RTC::format_time ( void ){
  tiempo = "";
  if ( hora < 10) tiempo += '0';
  tiempo += hora;
  tiempo += ':';
  if ( minuto < 10) tiempo += '0';
  tiempo += minuto;
  tiempo += ':';
  if ( segundo < 10) tiempo += '0';
  tiempo += segundo;
  
  
  }
