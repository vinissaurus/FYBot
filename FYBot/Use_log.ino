#include <EEPROM.h>
#include <NTPClient.h>

//-------------------------EEPROM addresses
#define LAST_DAY 0
#define TOTAL_REQUESTS 1
//-------------------------EEPROM addresses


#define REFRESH_RATE 10

int unstaged_requests = 0;
int staged_requests = 0;
String last_day;//by david august

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

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
  timeClient.begin();
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
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());
  delay(1000);
}
