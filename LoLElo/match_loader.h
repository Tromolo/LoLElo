#ifndef MATCH_LOADER_H
#define MATCH_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "player_loader.h"

#define MAX 100
#define MAX_HRACOV 3 

typedef struct {
    int hraci_cerveny[MAX_HRACOV];
    int kda_cerveny[MAX_HRACOV][3];
    int hraci_modry[MAX_HRACOV];
    int kda_modry[MAX_HRACOV][3];
    char vysledok[10];
} ZaznamHry;

void error_exit(const char *message);
void check_match_start(const char *buffer);
void check_player_count(int count, int expected_count);
void check_invalid_data(int data_count, int expected_count);
void check_match_result(const char *result);
void check_duplicate_teams(int *red_team_ids, int *blue_team_ids);
char *find_nickname_by_id(int player_id, Hrac *hraci);
void check_duplicate_ids_in_team(int *player_ids, int count);
int load_matches(const char *file_matches, ZaznamHry *zaznamy);

#endif