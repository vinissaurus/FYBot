#include <EEPROM.h>
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

//-------------------------EEPROM addresses
#define LAST_DAY 0
#define TOTAL_REQUESTS 1
//-------------------------EEPROM addresses


#define REFRESH_RATE 10

int unstaged_requests = 0;
int staged_requests = 0;
String last_day;//by david august
int MM,DD,YYYY;


void e_save(int Position, int Value) {
  EEPROM.begin(512);
  EEPROM.write(Position, Value);
  EEPROM.commit();
  EEPROM.end();
}

int e_read(int Position) {
  EEPROM.begin(512);
  return EEPROM.read(Position);
  EEPROM.end();
}

void delete_log() {
  Serial.println("Deleting log...");
  EEPROM.begin(512);
  EEPROM.write(TOTAL_REQUESTS, 0);
  EEPROM.commit();
  EEPROM.end();
}

void startup_reading() {
  last_day = e_read(LAST_DAY);
  staged_requests = e_read(TOTAL_REQUESTS);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  if(last_day.indexOf("/")==-1){
//    struct tm timeinfo;
//    if(getLocalTime(&timeinfo)){
//      char data_in[20];
//      strftime(data_in,20,"%B/%d/%Y",&timeinfo);
//      DD=data_in[0,2].toInt();serial(String(DD));
//      MM=data_in[3,5].toInt();serial(String(MM));
//      YYYY=data_in[6,8].toInt();serial(String(YYYY));
//      
//    }
//    
    }
  //xx/xx/xxxx
  
}

void request() {
  unstaged_requests++;


  if (unstaged_requests > 10) {
    int total_requests = staged_requests + unstaged_requests;
    e_save(TOTAL_REQUESTS, total_requests);
    unstaged_requests = 0;
  }
}


//String use_info() {
//  String answer = "I'm a simple and limited bot. My server is tiny, just like your dick.\n" +
//                 "I'm up since";
//   return null;
//}

void log_loop() {
  

  //Serial.println(timeClient.getDay());
  //delay(1000);
}
