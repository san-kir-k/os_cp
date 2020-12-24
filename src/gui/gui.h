#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>

#define PARSE_ERR -1
#define SURRENDER 1
#define COORDS 0

#define ALL_OK 0

void    gen_enemy_str_map(char** str_map);
void    gen_my_str_map(char** str_map, int** map);
void    get_map_coords(int* row, int* col, int str_r, int str_c);
void    get_str_coords(int row, int col, int* str_r, int* str_c);
void    update_str_map(char** str_map, int** map);
void    refresh_maps(int** my_map, int** enemy_map);
void    print_msg(char* msg, int len, bool is_wgetch);
void    print_enemy_map();
void    print_my_map();
int     parse_to_coords(char* buf, int* row, int* col);
void    scanf_from_input(char* buf);
int     init_gui(int** my_map, int** enemy_map);
void    deinit_gui();
