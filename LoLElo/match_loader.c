#include "match_loader.h"

void error_exit(const char *message) {
    printf("Chyba: %s\n", message);
    exit(1);
}

void check_match_start(const char *buffer) {
    if (strcmp(buffer, "match\n") != 0) {
        error_exit("Neni zaciatok zapasu");
    }
}

void check_player_count(int count, int expected_count) {
    if (count != expected_count) {
        error_exit("Malo hracov v time");
    }
}

void check_invalid_data(int data_count, int expected_count) {
    if (data_count != expected_count) {
        error_exit("Neplatný počet údajov KDA pre hráčov");
    }
}

void check_match_result(const char *result) {
    if (strcmp(result, "red") != 0 && strcmp(result, "blue") != 0) {
        error_exit("Vo vysledku zapasu");
    }
}

void check_duplicate_teams(int *red_team_ids, int *blue_team_ids) {
    for (int i = 0; i < MAX_HRACOV; ++i) {
        for (int j = 0; j < MAX_HRACOV; ++j) {
            if (red_team_ids[i] == blue_team_ids[j]) {
                error_exit("Duplicitné ID hráčov modrých a červených v jednom zápase");
            }
        }
    }
}

char* find_nickname_by_id(int player_id, Hrac *hraci) {
    for (int i = 0; i < player_count; i++) {
        if (hraci[i].id == player_id) {
            return hraci[i].nickname;
        }
    }
    return NULL;
}

void check_duplicate_ids_in_team(int *player_ids, int count) {
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (player_ids[i] == player_ids[j]) {
                error_exit("Duplicitné ID hráčov");
            }
        }
    }
}

int load_matches(const char *file_matches, ZaznamHry *zaznamy) {
    FILE *soubor = fopen(file_matches, "r");
    if (soubor == NULL) {
        printf("Subor so zaznamami nebol najdeny\n");
        exit(1);
    }

    int pocet_zaznamu = 0;
    char buffer[100];
    char *delimiter = ";,";

    while (fgets(buffer, sizeof(buffer), soubor) != NULL) {
        check_match_start(buffer);

        if (strcmp(buffer, "match\n") == 0) {
            //RED ID
            fgets(buffer, sizeof(buffer), soubor);
            char *token = strtok(buffer, delimiter);
            int i = 0;

            while (token != NULL) {
                zaznamy[pocet_zaznamu].hraci_cerveny[i++] = atoi(token);
                token = strtok(NULL, delimiter);
            }

            check_player_count(i, MAX_HRACOV);
            check_duplicate_ids_in_team(zaznamy[pocet_zaznamu].hraci_cerveny, MAX_HRACOV);
            
            //RED KDA
            fgets(buffer, sizeof(buffer), soubor);
            token = strtok(buffer, delimiter);
            i = 0;

            while (token != NULL) {
                zaznamy[pocet_zaznamu].kda_cerveny[i / 3][i % 3] = atoi(token);
                token = strtok(NULL, delimiter);
                i++;
            }
            check_invalid_data(i, MAX_HRACOV * 3);

            //BLUE ID
            fgets(buffer, sizeof(buffer), soubor);
            token = strtok(buffer, delimiter);
            i = 0;
            while (token != NULL) {
                zaznamy[pocet_zaznamu].hraci_modry[i++] = atoi(token);
                token = strtok(NULL, delimiter);
            }

            check_player_count(i, MAX_HRACOV);
            check_duplicate_ids_in_team(zaznamy[pocet_zaznamu].hraci_modry, MAX_HRACOV);

            //BLUE KDA
            fgets(buffer, sizeof(buffer), soubor);
            token = strtok(buffer, delimiter);
            i = 0;

            while (token != NULL) {
                zaznamy[pocet_zaznamu].kda_modry[i / 3][i % 3] = atoi(token);
                token = strtok(NULL, delimiter);
                i++;
            }

            check_invalid_data(i, MAX_HRACOV * 3);

            check_duplicate_teams(zaznamy[pocet_zaznamu].hraci_cerveny, zaznamy[pocet_zaznamu].hraci_modry);

            //RESULT
            fgets(buffer, sizeof(buffer), soubor);
            sscanf(buffer, "%s", zaznamy[pocet_zaznamu].vysledok);
            
            check_match_result(zaznamy[pocet_zaznamu].vysledok);

            pocet_zaznamu++;
        }
    }

    fclose(soubor);
    return pocet_zaznamu;
}