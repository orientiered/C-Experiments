#include <stdio.h>
#include <assert.h>

#include "utils.h"
#include "tournamentTable.h"
#include "matrix.h"
void tournamentTable();

int main() {
    matrix_t mat = createMatrix(4, 5);
    printMatrix(mat);
    fillMatrix(mat, 4);
    printMatrix(mat);
    matrix_t mat2 = createMatrix(4, 5);
    fillMatrix(mat2, 7);
    matrix_t mat3 = addMatrix(mat, mat2);
    printMatrix(mat3);
    delMatrix(&mat);
    delMatrix(&mat2);
    delMatrix(&mat3);
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


