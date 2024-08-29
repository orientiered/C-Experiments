#include <stdio.h>
#include <assert.h>

#include "utils.h"
#include "tournamentTable.h"
#include "matrix.h"
#include "myVector.h"


void tournamentTable();
void matrixTests();

int intCmp(const void* a, const void* b);
int floatCmp(const void* a, const void* b);

int main() {
    const float floatData[] = {1000-7, 1, 0.5, 3.4, 9.8, 21};
    vector_t floatVec = vectorCopyCtor(6, sizeof(float), (const void*)floatData);
    mergeSort(floatVec, *floatCmp);
    for (size_t i = 0; i < floatVec.size; i++)
        printf("%f ", *(float*)getElem(floatVec, i));
    vectorDtor(&floatVec);
    //matrixTests
    //tournamentTable();
    return 0;
}

int intCmp(const void* a, const void* b) {
    if (*(const int*)a == *(const int*)b) return 0;
    if (*(const int*)a  < *(const int*)b) return 1;
    return -1;
}

int floatCmp(const void* a, const void* b) {
    if (*(const float*)a == *(const float*)b) return 0;
    if (*(const float*)a  > *(const float*)b) return 1;
    return -1;
}

void matrixTests() {
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


