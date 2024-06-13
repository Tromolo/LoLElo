#include "player_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int player_count = 0;

int load_nicknames(const char *file_nicknames, Hrac *hraci) {
    FILE *file = fopen(file_nicknames, "r");
    if (file == NULL) {
        printf("Subor s prezyvkami nebol najdeny\n");
        return -1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *token = strtok(buffer, ",");
        if (token != NULL) {
            hraci[player_count].id = atoi(token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                //'\n'
                int length = strlen(token);
                if (token[length - 1] == '\n') {
                    token[length - 1] = '\0';
                }
                strcpy(hraci[player_count].nickname, token);
                player_count++;
            }
        }
    }

    fclose(file);
    return 0;
}