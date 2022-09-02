#include <stdio.h>
#include "disk.h"

#define COLUMNS 3
#define MAX_ROWS 5

static int difficulty = 3;
static int baseY = 0;
static Disk columns[COLUMNS][MAX_ROWS];

void Game_render() {
  for (int y = baseY; y < MAX_ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      if (columns[x][y].size == 0) {
        printf("     |     ");
      } else {
        printf("%s", columns[x][y].string);
      }
    }

    printf("\n");
  }
}

void Game_greet() {
  printf("Welcome to Towers of Hanoi.\n");
  printf("Enter your difficult level [1-3]: ");
}

int Game_setDifficulty() {
  if (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 3) {
    printf("Error: Difficult should be between 1 and 3.");
    return -1;
  }

  baseY = MAX_ROWS - (difficulty + 2);

  return 0;
}

void Game_initDisks() {
  for (int x = 0; x < COLUMNS; x++) {
    for (int i = 0; i < 2 + difficulty; i++) {
      int y = baseY + i;

      if (x == 0) {
        Disk_set(&columns[x][y], 1 + 2 * i);
      } else {
        Disk_empty(&columns[x][y]);
      }
    }
  }
}

void Game_start() {
  printf("\n====================\n");
  printf("Your selected difficult is: %d\n", difficulty);
  printf("Let's begin.\n\n");

  Game_initDisks();
  Game_render();
}