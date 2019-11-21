extern "C" {
#include "controller/joystick.h"
}

#include "displayer/displayer.h"
#define N 294

void objects(displayer::Displayer<N> &displayer);
void pong(displayer::Displayer<N> &displayer);

int main() {
  Joystick_init();
  displayer::Displayer<N> displayer;

  while(1) {
    objects(displayer);
    pong(displayer);
  }

  Joystick_cleanUp();
}