#ifndef PLAYER_LOADER_H
#define PLAYER_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nickname[50];
} Hrac;

extern int player_count;

int load_nicknames(const char *file_nicknames, Hrac *hraci);

#endif