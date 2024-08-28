#include <stdio.h>
#include <assert.h>

#include "utils.h"
#include "tournamentTable.h"
#include "matrix.h"
void tournamentTable();

int main() {
    const double data1[][4] = {
        {1, 2, 3, 4},
        {1, 1, 1, 1}
    };
    const double data2[][3] {
        {0, 1, 2},
        {1, 1, 1},
        {2, 2, 2},
        {1, 2, 3}
    };
    matrix_t m1 = createMatrix(4, 2);
    setMatrix(m1, (const double *) data1);
    matrix_t m2 = createMatrix(3, 4);
    setMatrix(m2, (const double *) data2);
    printMatrix(m1);
    printMatrix(m2);
    matrix_t m3 = multiplyMatrix(m1, m2);
    printMatrix(m3);
    //m3 = multiplyMatrix(m2, m1);

    const double data3[][5] {
        {1,  2,  3,  4,  5},
        {0, -4,  3,  2, 21},
        {5, -1,  2,  9, 15},
        {5, 12, -9, 18,  2},
        {4,  4, -4, 12,  5}
    };
    matrix_t detTest = createMatrix(5, 5);
    setMatrix(detTest, (const double *)data3);
    printMatrix(detTest);
    double determinant = det(detTest);
    printf("\n%lg\n", determinant);
    matrix_t inv = inverse(detTest);
    printMatrix(inv);
    matrix_t m4 = multiplyMatrix(inv, detTest);
    printMatrix(m4);
    delMatrix(&m1);
    delMatrix(&m2);
    delMatrix(&m3);
    delMatrix(&m4);
    delMatrix(&inv);
    delMatrix(&detTest);
    //tournamentTable();
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


