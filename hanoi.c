#include <stdio.h>
#include "game.h"

int main() {
  printf("Welcome to Towers of Hanoi.\n");

  if (Game_setDifficulty() == -1) { return -1; }  

  Game_start();

  return 0;
}