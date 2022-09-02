#include "game.h"

int main() {
  Game_greet();
  if (Game_setDifficulty() == -1) { return -1; }  

  Game_start();

  return 0;
}