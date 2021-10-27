#include "FY.h"
#include "Messages.h"

void setup() {
  Serial.begin(115200);
  wifi_setup();
  t_setup();
  //log_setup();
  randomSeed(analogRead(0));
}


void loop() {
  wifi_loop();
  t_loop();
  //log_loop();
}
