#ifndef TOUR_TABLE_H
#define TOUR_TABLE_H

typedef struct game {
    int first, second;
} game_t;

const size_t numTeams = 5;
const size_t tableSize = numTeams*(numTeams-1)/2;

game_t *getValue(game_t *table, int firstTeam, int secondTeam);
void addGame(game_t *table, int firstTeam, int secondTeam, game_t result);
void printGame(game_t *table, int firstTeam, int secondTeam);
void printTable(game_t *table);

#endif
