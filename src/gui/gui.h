#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define SMALL_SCREEN_ERR -1
#define ALL_OK 0

void    gen_enemy_str_map(char** str_map);
void    gen_my_str_map(char** str_map, int** map);
void    get_map_coords(int* row, int* col, int str_r, int str_c);
void    get_str_coords(int row, int col, int* str_r, int* str_c);
void    update_str_map(char** str_map, int** map);
void    refresh_maps(int** my_map, int** enemy_map);
void    print_enemy_map();
void    print_my_map();
int     init_gui(int** my_map, int** enemy_map);
void    denit_gui();
// TODO считывание
