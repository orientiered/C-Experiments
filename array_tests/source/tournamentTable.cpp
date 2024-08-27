#include <stdio.h>
#include <utils.h>
#include <assert.h>

#include "tournamentTable.h"

void addGame(game_t *table, int firstTeam, int secondTeam, game_t result) {
    game_t *pos = getValue(table, firstTeam, secondTeam);
    if (pos)
        *pos = result;
    else
        printf("Не получилось добавить запись\n");
}

void printGame(game_t *table, int firstTeam, int secondTeam) {
    game_t *pos = getValue(table, firstTeam, secondTeam);
    if (pos) {
        if (firstTeam < secondTeam)
            SWAP(firstTeam, secondTeam);
        if (pos->first == 0 && pos->second == 0)
            printf("Эти команды ещё не играли\n");
        else if (pos->first == pos->second)
            printf("Счёт %d : %d - ничья\n", pos->first, pos->second);
        else if (pos->first > pos->second)
            printf("Счёт %d : %d - победа команды %d\n", pos->first, pos->second, firstTeam+1);
        else
            printf("Счёт %d : %d - победа команды %d\n", pos->first, pos->second, secondTeam+1);
    }

}

void printTable(game_t *table) {
    printf("   ");
    for (size_t i = 0; i < numTeams; i++) {
        printf("%3d ", i+1);
    }
    putchar('\n');
    for (size_t i = 1; i < numTeams; i++) {
        printf("%3d ", i+1);
        for (size_t j = 0; j < numTeams; j++) {
            if (i == j)
                printf("### ");
            else if (j > i)
                printf(" x  ");
            else
                printf("%d:%d ", getValue(table, i, j)->first, getValue(table, i, j)->second);
        }
        putchar('\n');
    }
}

game_t *getValue(game_t *table, int firstTeam, int secondTeam) {
    if (firstTeam == secondTeam) {
        printf("Команды не играют сами с собой\n");
        return NULL;
    }

    if (firstTeam < secondTeam)
        SWAP(firstTeam, secondTeam);

    assert(firstTeam > secondTeam);

    size_t index = firstTeam*(firstTeam-1)/2 + secondTeam;
    if (index >= tableSize) {
        printf("Слишком большие номера команд\n");
        return NULL;
    }
    assert(index < tableSize);
    return table + index;
}
