extern "C" {
#include "controller/joystick.h"
}

void objects();
void pong();

int main() {
  Joystick_init();

  while(1) {
    objects();
    pong();
  }

  Joystick_cleanUp();
}