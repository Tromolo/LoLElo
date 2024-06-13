#include "match_loader.h"
#include "player_loader.h"
#include "html_generator.h"

void check_all_ids_have_nicknames(ZaznamHry* zaznamy, Hrac *hraci) {
    for (int i = 0; i < MAX_HRACOV; i++) {
        for (int j = 0; j < player_count; j++) {
            if (zaznamy->hraci_cerveny[i] == hraci[j].id || zaznamy->hraci_modry[i] == hraci[j].id) {
                if (strcmp(hraci[j].nickname, "") == 0) {
                    printf("Chyba: ID hráč nemá priraden nickname\n");
                    exit(1);
                }
            }
        }
    }
}

void check_empty_player(int pocet_zaznamu, ZaznamHry *zaznamy, Hrac *hraci) {
    for (int zaznam = 0; zaznam < pocet_zaznamu; zaznam++) {
        for (int i = 0; i < MAX_HRACOV; i++) {
            bool found_cerveny = false;
            bool found_modry = false;

            for (int j = 0; j < player_count; j++) {
                if (zaznamy[zaznam].hraci_cerveny[i] == hraci[j].id) {
                    found_cerveny = true;
                }
                if (zaznamy[zaznam].hraci_modry[i] == hraci[j].id) {
                    found_modry = true;
                }
                if (found_cerveny && found_modry) {
                    break;
                }
            }
            if (!found_cerveny || !found_modry) {
                printf("Chyba: ID hráča v zázname nebolo najdene v zozname hracov\n");
                exit(1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Nedostatok vstupnych argumentov\n");
        return 1;
    }

    ZaznamHry *zaznamy = malloc(sizeof(ZaznamHry) * MAX);
    Hrac *hraci = malloc(sizeof(Hrac) * MAX);

    char *file_nicknames = argv[2];

    int nacitanie = load_nicknames(file_nicknames,hraci);
    if (nacitanie == -1) {
        return 1;
    }

    char *file_matches = argv[1];

    int pocet_zaznamu = load_matches(file_matches,zaznamy);
    if (pocet_zaznamu == -1) {
        return 1;
    }

    check_all_ids_have_nicknames(zaznamy,hraci);
    check_empty_player(pocet_zaznamu,zaznamy,hraci);

    char *output_file = argv[3];

    int top_players = 6;
    display_info(output_file,zaznamy,pocet_zaznamu,top_players,hraci);

    free(zaznamy);
    free(hraci);

    return 0;
}