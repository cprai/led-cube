extern "C" {
#include "controller/joystick.h"
}

void pong();

int main() {
  Joystick_init();

  pong();

  Joystick_cleanUp();
}