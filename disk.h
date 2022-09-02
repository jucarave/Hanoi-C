#ifndef DISK_HEADER
#define DISK_HEADER

typedef struct {
    int size;
    char string[12];
} Disk;

void Disk_set(Disk *disk, int size);

void Disk_empty(Disk *disk);

#endif