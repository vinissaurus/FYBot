#include <EEPROM.h>

#define LAST_DAY 0
#define TOTAL_REQUESTS 1

#define REFRESH_RATE 10

int unstaged_requests = 0;
int staged_requests = 0;
String last_day;//by david august

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
}

void request() {
  unstaged_requests++;
  int total_requests = staged_requests + unstaged_requests;

  if (unstaged_requests > 10) {
    e_save(TOTAL_REQUESTS, total_requests);
  }
}


String use_info() {

}

void log_loop() {

}
