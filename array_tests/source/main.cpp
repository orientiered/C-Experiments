#include <stdio.h>
#include <assert.h>

#include "utils.h"
#include "tournamentTable.h"

void tournamentTable();

int main() {
    tournamentTable();
    return 0;
}

void tournamentTable() {
    game_t table[tableSize] = {};

    while (1) {
        char command = 0;
        int firstTeam = 0, secondTeam = 0;
        game_t tempGame = {};
        scanf("%c", &command);
        switch(command) {
            case 'a':
                scanf("%d %d %d %d", &firstTeam, &secondTeam, &tempGame.first, &tempGame.second);
                addGame(table, firstTeam-1, secondTeam-1, tempGame);
                break;
            case 'p':
                scanf("%d %d", &firstTeam, &secondTeam);
                printGame(table, firstTeam-1, secondTeam-1);
                break;
            case 't':
                printTable(table);
                break;
            case 'b':
                return;
            default:
                printf("Unknown command\n");
                break;
        }
        flushScanfBuffer();
    }
}


