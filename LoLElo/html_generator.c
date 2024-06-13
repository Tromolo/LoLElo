#include "html_generator.h"

void calculate_kd_ratio(int pocet_zaznamu, FILE *file, ZaznamHry *zaznamy, Hrac *hraci) {
    fprintf(file, "<h2>KD Ratio</h2>\n");
    fprintf(file, "<table class='table'>\n");
    fprintf(file, "<tr><th>Nickname</th><th>KD Ratio</th></tr>\n");
    for (int i = 0; i < player_count; ++i) {
        int kills = 0, deaths = 0;
        for (int j = 0; j < pocet_zaznamu; ++j) {
            for (int k = 0; k < MAX_HRACOV; ++k) {
                if (zaznamy[j].hraci_cerveny[k] == hraci[i].id) {
                    kills += zaznamy[j].kda_cerveny[k][0];
                    deaths += zaznamy[j].kda_cerveny[k][2];
                }
                if (zaznamy[j].hraci_modry[k] == hraci[i].id) {
                    kills += zaznamy[j].kda_modry[k][0];
                    deaths += zaznamy[j].kda_modry[k][2];
                }
            }
        }
        float kd_ratio = (deaths != 0) ? (float)kills / deaths : 0;
        fprintf(file, "<tr><td>%s</td><td>%.2f</td></tr>\n", hraci[i].nickname, kd_ratio);
    }
    fprintf(file, "</table>\n");
}

void find_players_with_most_kills(int top_players, FILE *file, ZaznamHry *zaznamy, Hrac *hraci) {
    fprintf(file, "<h2>Players with Most Kills</h2>\n");
    fprintf(file, "<table class='table'>\n");
    fprintf(file, "<tr><th>Nickname</th><th>Kills</th></tr>\n");
    int kill_count[MAX] = {0};

    for (int i = 0; i < player_count; ++i) {
        for (int j = 0; j < MAX; ++j) {
            for (int k = 0; k < MAX_HRACOV; ++k) {
                if (zaznamy[j].hraci_cerveny[k] == hraci[i].id) {
                    kill_count[i] += zaznamy[j].kda_cerveny[k][0];
                }
                if (zaznamy[j].hraci_modry[k] == hraci[i].id) {
                    kill_count[i] += zaznamy[j].kda_modry[k][0];
                }
            }
        }
    }

    for (int i = 0; i < top_players; ++i) {
        int max_kills = -1;
        int max_index = -1;
        for (int j = 0; j < player_count; ++j) {
            if (kill_count[j] > max_kills) {
                max_kills = kill_count[j];
                max_index = j;
            }
        }

        if (max_index != -1) {
            fprintf(file, "<tr><td>%s</td><td>%d</td></tr>\n", hraci[max_index].nickname, max_kills);
            kill_count[max_index] = -1;
        }
    }
    fprintf(file, "</table>\n");
}

void find_players_with_most_wins(FILE *file, ZaznamHry *zaznamy, Hrac *hraci) {
    fprintf(file, "<h2>Players with Most Wins</h2>\n");
    fprintf(file, "<table class='table'>\n");
    fprintf(file, "<tr><th>Nickname</th><th>Wins</th></tr>\n");
    int win_count[MAX] = {0};
    int count_players = 0;

    for (int i = 0; i < player_count; ++i) {
        for (int j = 0; j < MAX; ++j) {
            for (int k = 0; k < MAX_HRACOV; ++k) {
                if (zaznamy[j].hraci_cerveny[k] == hraci[i].id) {
                    if (strcmp(zaznamy[j].vysledok, "red") == 0) {
                        win_count[i]++;
                    }
                }
                if (zaznamy[j].hraci_modry[k] == hraci[i].id) {
                    if (strcmp(zaznamy[j].vysledok, "blue") == 0) {
                        win_count[i]++;
                    }
                }
            }
        }
    }

    int max_wins = -1;
    for (int i = 0; i < player_count; ++i) {
        if (win_count[i] > max_wins) {
            max_wins = win_count[i];
        }
    }

    for (int i = 0; i < player_count; ++i) {
        if (win_count[i] == max_wins) {
            count_players++;
            fprintf(file, "<tr><td>%s</td><td>%d</td></tr>\n", hraci[i].nickname, win_count[i]);
        }
    }
    fprintf(file, "</table>\n");
}

void generate_player_statistics_table(FILE *file, ZaznamHry *zaznamy, int pocet_zaznamu, Hrac *hraci) {
    fprintf(file, "<h2>Player Statistics</h2>\n");
    fprintf(file, "<table class='table'>\n");
    fprintf(file, "<thead>\n<tr><th>Nickname</th><th>Kills</th><th>Assists</th><th>Deaths</th><th>Played Matches</th><th>Wins</th><th>Losses</th><th>Red Team</th><th>Blue Team</th></tr>\n");
    fprintf(file, "</thead>\n<tbody>\n");

    for (int i = 0; i < player_count; ++i) {
        int kills = 0, assists = 0, deaths = 0, matches_played = 0, wins = 0, losses = 0, red_team = 0, blue_team = 0;

        for (int j = 0; j < pocet_zaznamu; ++j) {
            for (int k = 0; k < MAX_HRACOV; ++k) {
                if (zaznamy[j].hraci_cerveny[k] == hraci[i].id) {
                    red_team++;
                    matches_played++;
                    kills += zaznamy[j].kda_cerveny[k][0];
                    assists += zaznamy[j].kda_cerveny[k][1];
                    deaths += zaznamy[j].kda_cerveny[k][2];
                    if (strcmp(zaznamy[j].vysledok, "red") == 0) {
                        wins++;
                    } else {
                        losses++;
                    }
                }
                if (zaznamy[j].hraci_modry[k] == hraci[i].id) {
                    blue_team++;
                    matches_played++;
                    kills += zaznamy[j].kda_modry[k][0];
                    assists += zaznamy[j].kda_modry[k][1];
                    deaths += zaznamy[j].kda_modry[k][2];
                    if (strcmp(zaznamy[j].vysledok, "blue") == 0) {
                        wins++;
                    } else {
                        losses++;
                    }
                }
            }
        }

        fprintf(file, "<tr><td>%s</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td></tr>\n",
                hraci[i].nickname, kills, assists, deaths, matches_played, wins, losses, red_team, blue_team);
    }

    fprintf(file, "</table>\n");
}

void display_info(const char *output_file,ZaznamHry *zaznamy, int pocet_zaznamu, int top_kill_players,Hrac *hraci) {
    FILE *file = fopen(output_file, "w");
    if (file == NULL) {
        printf("Chyba\n");
        return;
    }

    fprintf(file, "<!DOCTYPE html>\n<html lang='en'>\n<head>\n");
    fprintf(file, "<meta charset='UTF-8'>\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n");
    fprintf(file, "<title>Player Information</title>\n<link href='https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css' rel='stylesheet'>\n");
    fprintf(file, "</head>\n<body>\n<div class='container'>\n<h1>Player Information</h1>\n");

    //statistika celkova name, K , D , A , Played matches , W / L , R/B Team
    generate_player_statistics_table(file,zaznamy,pocet_zaznamu,hraci);
    //Top 6 hracov s najviac killami
    find_players_with_most_kills(top_kill_players, file,zaznamy,hraci);
    //Hraci ktory maju najviac vyhier
    find_players_with_most_wins(file,zaznamy,hraci);
    //Kill/Death Ratio vsetkych hracov
    calculate_kd_ratio(pocet_zaznamu, file,zaznamy,hraci);

    fprintf(file, "</div>\n");
    fprintf(file, "<script src='https://code.jquery.com/jquery-3.5.1.slim.min.js'></script>\n");
    fprintf(file, "<script src='https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.1/dist/umd/popper.min.js'></script>\n");
    fprintf(file, "<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js'></script>\n");
    fprintf(file, "</body>\n</html>");

    fclose(file);
}