#include <EEPROM.h>
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

//-------------------------EEPROM addresses
#define LAST_DAY 0//Kollektiv Turmstrasse, David August Revision
#define TOTAL_REQUESTS 10
//-------------------------EEPROM addresses


#define REFRESH_RATE 10

int total_requests = 0;
int unstaged_requests = 0;
int staged_requests = 0;
String last_day;//by david august
int month, day, year;


void e_save_date() {
  EEPROM.begin(512);
  last_day = String(day) + "/" + String(month) + "/" + String(year);
  //save date string length
  EEPROM.write(LAST_DAY, last_day.length());
  int starting = LAST_DAY + 1;
  //salvar o SSID
  for (int i = 0; i < last_day.length(); ++i) {
    EEPROM.write(starting + i, last_day[i]);
    Serial.print(last_day[i]);
  }
  //Serial.println("----testcase1");
  EEPROM.commit();
  EEPROM.end();
}

void e_save_requests() {
  EEPROM.begin(512);
  int starting = LAST_DAY + 1 + last_day.length() + 1;
  //save requests string length
  int req = unstaged_requests + staged_requests;
  String requests = String(req);
  EEPROM.write(LAST_DAY + 1 + last_day.length(), requests.length());
  //save the string
  for (int i = 0; i < requests.length(); ++i) {
    EEPROM.write(starting + i, requests[i]);
    Serial.print(requests[i]);
  }
  //Serial.println("----testcase2");
  EEPROM.commit();
  EEPROM.end();
}

void e_read() {

  last_day = "";

  EEPROM.begin(512);
  int sizeOf = EEPROM.read(LAST_DAY);
  if (sizeOf == 0) {//verificar se existem credenciais registradas
    //memPSK = "@null";
    Serial.println("Nothing to read here");

  }
  else {
    int starting = LAST_DAY + 1;
    //read the date
    for (int i = 0; i < sizeOf; ++i) {
      last_day += char(EEPROM.read(starting + i));
    }
    Serial.println(last_day);
    day = last_day.substring(0, last_day.indexOf("/")).toInt();
    month = last_day.substring(last_day.indexOf("/") + 1, last_day.lastIndexOf("/")).toInt();
    year = last_day.substring(last_day.lastIndexOf("/") + 1, last_day.length() - 1).toInt();

    //read the requests
    Serial.println(day);
    Serial.println(month);
    Serial.println(year);
    starting = LAST_DAY + 1 + last_day.length() + 1;
    sizeOf = EEPROM.read(LAST_DAY + 1 + last_day.length());
    String the_requests;
    for (int i = 0; i < sizeOf; ++i)  {
      the_requests += char(EEPROM.read(starting + i));
    }
    staged_requests = the_requests.toInt();
  }
  //Serial.println(memPSK);
  EEPROM.end();



}

void delete_log() {
  Serial.println("Deleting log...");
  EEPROM.begin(512);
  EEPROM.write(TOTAL_REQUESTS, 0);
  EEPROM.commit();
  EEPROM.end();
}

void check_date() {
  struct tm timeinfo;
  if (last_day.indexOf("/") == -1) {

    if (getLocalTime(&timeinfo)) {

      int this_month = (int)(&timeinfo, "%m");
      int this_day = (int)(&timeinfo, "%d");
      int this_year = (int)(&timeinfo, "%Y");
      String full_date = String(month) + "/" + String(day) + "/" + String(year);

      day = this_day;
      month = this_month;
      year = this_year;
      if (this_year > year || (this_month > month && this_year == year) || (this_day + 1 > day && this_month == month && this_year == year)) {
        delay(200);
        e_save_date();
      }

    }

  }
  if (day == 0 || month == 0 || year == 0) {

    e_save_date();
  }
}

void log_setup() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  e_read();
  delay(200);
  check_date();


}

void request() {
  unstaged_requests++;
  total_requests = staged_requests + unstaged_requests;

  if (unstaged_requests > 10) {

    e_save_requests();
    unstaged_requests = 0;
  }
}


String use_info() {
  String answer = "I'm a simple and limited bot. My server is tiny, just like your dick.\nI said FUCK YOU  " +
                  String(total_requests) + " times.\nNow, if you excuse-me, let me just say FUCK YOU!";

  return answer;
}


void log_loop() {
  //Serial.println(timeClient.getDay());
  //delay(1000);
}
