#include <stdlib.h>
#include <string.h>
#include "disk.h"

void Disk_createString(char *string, int size) {
  int emptySpace = (11 - size) / 2;

  memset(string, ' ', 11);
  memset(string, '*', size + emptySpace);
  memset(string, ' ', emptySpace);
}

void Disk_set(Disk *disk, int size) {
  disk->size = size;
  
  Disk_createString(disk->string, size);
}

void Disk_empty(Disk *disk) {
  disk->size = 0;
  memset(disk->string, ' ', 11);
}