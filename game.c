#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "disk.h"

#define COLUMNS 3
#define MAX_ROWS 5

static int difficulty = 3;
static int baseY = 0;
static Disk columns[COLUMNS][MAX_ROWS];

void Game_renderBoard() {
  printf("\n     A          B          C     ");
  printf("\n                                 \n");

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

void Game_getPlayerMovement(char *a, char *b) {
  bool correctValues = false;

  do {
    printf("\nEnter your movement (eg: 'A to B'): ");
    
    while (getchar() != '\n');
    
    if (scanf("%c to %c", a, b) == 2) {
      correctValues = true;
    } else {
      printf("Incorrect format, try again.\n");
    }
  } while (correctValues == false);
};

int Game_getColumnIndex(char column) {
  if (column == 'a' || column == 'A') {
    return 0;
  } else if (column == 'b' || column == 'B') {
    return 1;
  } else if (column == 'c' || column == 'C') {
    return 2;
  }

  printf("Incorrect column '%c'\n", column);
  return -1;
}

int Game_getTopDiskSize(int column) {
  int index = 0;

  while (columns[column][index].size == 0 && index < MAX_ROWS) {
    index++;
  }

  return columns[column][index].size;
}

void Game_clearTopDisk(int column) {
  int index = 0;

  while (columns[column][index].size == 0 && index < MAX_ROWS) {
    index++;
  }

  Disk_empty(&columns[column][index]);
}

void Game_setTopDisk(int column, int size) {
  int index = MAX_ROWS - 1;

  while (columns[column][index].size != 0 && index > 0) {
    index--;
  }

  Disk_set(&columns[column][index], size);
}

bool Game_isFinished() {
  return columns[2][baseY].size == 1;
}

void Game_loop() {
  char a, b;
  int diskSizeA, diskSizeB, columnIndexA, columnIndexB;
  
  Game_renderBoard();
  Game_getPlayerMovement(&a, &b);
  
  columnIndexA = Game_getColumnIndex(a);
  columnIndexB = Game_getColumnIndex(b);

  if (columnIndexA != -1 && columnIndexB != -1) {
    diskSizeA = Game_getTopDiskSize(columnIndexA);
    diskSizeB = Game_getTopDiskSize(columnIndexB);

    if (diskSizeA < diskSizeB || diskSizeB == 0) {
      Game_clearTopDisk(columnIndexA);
      Game_setTopDisk(columnIndexB, diskSizeA);
    } else {
      printf("Cannot move the disk above a smaller one.\n");
    }

    if (Game_isFinished()) {
      Game_renderBoard();
      printf("========================================\n");
      printf("Congratulations! You have won the game.\n");
      printf("Now, get out and live your life.");
    }
  }
}

int Game_setDifficulty() {
  printf("Enter your difficult level [1-3]: ");

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

  while (!Game_isFinished()) {
    Game_loop();
  }
}