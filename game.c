#include <stdio.h>
#include <stdbool.h>
#include "disk.h"

#define COLUMNS 3
#define MAX_ROWS 5

static int difficulty = 3;
static int baseY = 0;
static Disk columns[COLUMNS][MAX_ROWS];

void Game_renderBoard() {
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
      printf("incorrect format, try again.\n");
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

  return -1;
}

int Game_getTopDisk(int column) {
  int index = 0;
  int size = 0;

  while (columns[column][index].size == 0 && index < MAX_ROWS) {
    index++;
  }

  size = columns[column][index].size;
  Disk_empty(&columns[column][index]);

  return size;
}

void Game_setTopDisk(int column, int size) {
  int index = MAX_ROWS - 1;
  while (columns[column][index].size != 0 && index > 0) {
    index--;
  }

  Disk_set(&columns[column][index], size);
}

void Game_render() {
  char a, b;
  int diskSize;
  
  Game_renderBoard();
  Game_getPlayerMovement(&a, &b);
  
  diskSize = Game_getTopDisk(Game_getColumnIndex(a));
  Game_setTopDisk(Game_getColumnIndex(b), diskSize);
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
  bool gameOver = false;

  printf("\n====================\n");
  printf("Your selected difficult is: %d\n", difficulty);
  printf("Let's begin.\n\n");

  Game_initDisks();

  while (!gameOver) {
    Game_render();
  }
}