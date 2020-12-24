#pragma once
#include <stdbool.h>

struct battlefield;
typedef struct battlefield battlefield;

struct action;
typedef struct action action;

void init_action(action** act, int** field);
void deinit_action(action* act);
void shoot(action* act, int row, int col);
bool is_gameover(action* act);
void init_battlefield(battlefield** bf);
void deinit_battlefield(battlefield* bf);
void gen_map(battlefield* bf);
void get_map_c(battlefield* bf, int** field);
