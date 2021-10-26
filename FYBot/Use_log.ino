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
int month, day, year;


void e_save_date(int Position, String Value) {
}

String e_read_date() {
String yeppers="10/26/2021";
return yeppers;
}

void delete_log() {
  Serial.println("Deleting log...");
  EEPROM.begin(512);
  EEPROM.write(TOTAL_REQUESTS, 0);
  EEPROM.commit();
  EEPROM.end();
}

void startup_reading() {
  last_day = e_read_date();
  //staged_requests = e_read(TOTAL_REQUESTS);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;


  if (last_day.indexOf("/") == -1) {

    if (getLocalTime(&timeinfo)) {

      month = (int)(&timeinfo, "%m");
      day = (int)(&timeinfo, "%d");
      year = (int)(&timeinfo, "%Y");
      String full_date = String(month) + "/" + String(day) + "/" + String(year);
      serial("Just wrote:");
      serial(full_date);
      //e_save(LAST_DAY, full_date);

    }

  }
  else {
    month = last_day.substring(0, 2).toInt();
    day = last_day.substring(3, 5).toInt();
    year = last_day.substring(6, 10).toInt();
    String full_date = String(month) + "/" + String(day) + "/" + String(year);
    serial("Just read:");
    serial(full_date);
  }
  //xx/xx/xxxx

}

void request() {
  unstaged_requests++;


  if (unstaged_requests > 10) {
    int total_requests = staged_requests + unstaged_requests;
    //e_save(TOTAL_REQUESTS, total_requests);
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
