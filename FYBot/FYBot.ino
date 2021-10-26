#include "FY.h"
#include "Messages.h"

void setup() {
  s_setup();
  wifi_setup();
  t_setup();
  randomSeed(analogRead(0));
}

void loop() {
  wifi_loop();
  t_loop();
  s_loop();
}
