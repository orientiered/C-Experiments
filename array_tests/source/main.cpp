#include <stdio.h>
#include <assert.h>

#include "utils.h"
#include "tournamentTable.h"
#include "matrix.h"
void tournamentTable();

int main() {
    const int data1[][4] = {
        {1, 2, 3, 4},
        {1, 1, 1, 1}
    };
    const int data2[][3] {
        {0, 1, 2},
        {1, 1, 1},
        {2, 2, 2},
        {1, 2, 3}
    };
    matrix_t m1 = createMatrix(4, 2);
    setMatrix(m1, (const int *) data1);
    matrix_t m2 = createMatrix(3, 4);
    setMatrix(m2, (const int *) data2);
    printMatrix(m1);
    printMatrix(m2);
    matrix_t m3 = multiplyMatrix(m1, m2);
    printMatrix(m3);
    //m3 = multiplyMatrix(m2, m1);

    const int data3[20][20] {
        {1,  2,  3,  4,  5},
        {0, -4,  3,  2, 21},
        {5, -1,  2,  9, 15},
        {5, 12, -9, 18,  2},
        {4,  4, -4, 12,  5}
    };
    matrix_t detTest = createMatrix(20, 20);
    setMatrix(detTest, (const int *)data3);
    printMatrix(detTest);
    long long determinant = det(detTest);
    printf("\n%lld\n", determinant);
    delMatrix(&m1);
    delMatrix(&m2);
    delMatrix(&m3);
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


