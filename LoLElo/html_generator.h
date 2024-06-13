#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H

#include <stdio.h>
#include "match_loader.h"
#include "player_loader.h"

void calculate_kd_ratio(int pocet_zaznamu, FILE *file, ZaznamHry *zaznamy, Hrac *hraci);
void find_players_with_most_kills(int top_players, FILE *file, ZaznamHry *zaznamy, Hrac *hraci);
void find_players_with_most_wins(FILE *file, ZaznamHry *zaznamy, Hrac *hraci);
void generate_player_statistics_table(FILE *file, ZaznamHry *zaznamy, int pocet_zaznamu, Hrac *hraci);
void display_info(const char *output_file, ZaznamHry *zaznamy, int pocet_zaznamu, int top_kill_players, Hrac *hraci);

#endif