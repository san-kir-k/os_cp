#include "gui.h"

static const int    MAX_BUF_LEN = 256;

static const int    BATTLESHIP = 4;
static const int    CRUISER = 3;
static const int    DESTROYER = 2;
static const int    BOAT = 1;
static const int    NONE = 0;
static const int    DEAD = -1;
static const int    SHOOTED = -2;
static const int    MISSED = -3;

static const char   SHIP_CHAR = 'O';
static const char   NONE_CHAR = '~';
static const char   DEAD_CHAR = 'X';
static const char   SHOOTED_CHAR = '*';
static const char   MISSED_CHAR = '#';

static const int    MAP_SIZE = 10;
static const int    MAP_STR_WIDTH = 23;
static const int    MAP_STR_HEIGHT = 15;

static char**       MY_STR_MAP;
static char**       ENEMY_STR_MAP;

static int          MAP_WIN_WIDTH;
static int          MAP_WIN_HEIGHT;
static int          INPUT_WIN_WIDTH;
static int          INPUT_WIN_HEIGHT;

static int          MY_MAP_START_X;
static int          MY_MAP_START_Y;
static int          ENEMY_MAP_START_X;
static int          ENEMY_MAP_START_Y;

WINDOW*             MY_MAP_WIN;
WINDOW*             ENEMY_MAP_WIN;
WINDOW*             INPUT_WIN;
WINDOW*             HELPER_WIN;

void gen_my_str_map(char** str_map, int** map) {
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        for (int j = 0; j < MAP_STR_WIDTH; ++j) {
            str_map[i][j] = ' ';
        }
    }

    str_map[1][0] = '/';
    for (int i = 1; i < MAP_STR_WIDTH - 1; ++i) {
        str_map[0][i] = '_';
    }
    str_map[1][MAP_STR_WIDTH - 1] = '\\';
    str_map[1][10] = 'Y';
    str_map[1][11] = 'O';
    str_map[1][12] = 'U';
    str_map[MAP_STR_HEIGHT - 1][0] = '\\';
    for (int i = 1; i < MAP_STR_WIDTH - 1; ++i) {
        str_map[MAP_STR_HEIGHT - 1][i] = '_';
    }
    str_map[MAP_STR_HEIGHT - 1][MAP_STR_WIDTH - 1] = '/';

    str_map[2][0] = ' ';
    str_map[2][MAP_STR_WIDTH - 1] = ' ';
    int num = 0;
    for (int i = 2; i < MAP_STR_WIDTH - 1; i += 2) {
        str_map[2][i] = num + '0';
        num++;
    }
    str_map[MAP_STR_HEIGHT - 2][0] = ' ';
    str_map[MAP_STR_HEIGHT - 2][MAP_STR_WIDTH - 1] = ' ';
    num = 0;
    for (int i = 2; i < MAP_STR_WIDTH - 1; i += 2) {
        str_map[MAP_STR_HEIGHT - 2][i] = num + '0';
        num++;
    }

    num = 0;
    for (int i = 3; i < MAP_STR_HEIGHT - 2; i++) {
        str_map[i][0] = num + '0';
        num++;
    }
    num = 0;
    for (int i = 3; i < MAP_STR_HEIGHT - 2; i++) {
        str_map[i][MAP_STR_WIDTH - 1] = num + '0';
        num++;
    }

    for (int i = 3, m_i = 0; i < MAP_STR_HEIGHT - 2; i++, m_i++) {
        for (int j = 2, m_j = 0; j < MAP_STR_WIDTH - 1; j += 2, m_j++) {
            if (map[m_i][m_j] != NONE) {
                str_map[i][j] = 'O';
            } else {
                str_map[i][j] = '~';
            }
        }
    }
} 

void gen_enemy_str_map(char** str_map) {
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        for (int j = 0; j < MAP_STR_WIDTH; ++j) {
            str_map[i][j] = ' ';
        }
    }

    str_map[1][0] = '/';
    for (int i = 1; i < MAP_STR_WIDTH - 1; ++i) {
        str_map[0][i] = '_';
    }
    str_map[1][MAP_STR_WIDTH - 1] = '\\';
    str_map[1][9] = 'E';
    str_map[1][10] = 'N';
    str_map[1][11] = 'E';
    str_map[1][12] = 'M';
    str_map[1][13] = 'Y';
    str_map[MAP_STR_HEIGHT - 1][0] = '\\';
    for (int i = 1; i < MAP_STR_WIDTH - 1; ++i) {
        str_map[MAP_STR_HEIGHT - 1][i] = '_';
    }
    str_map[MAP_STR_HEIGHT - 1][MAP_STR_WIDTH - 1] = '/';

    str_map[2][0] = ' ';
    str_map[2][MAP_STR_WIDTH - 1] = ' ';
    int num = 0;
    for (int i = 2; i < MAP_STR_WIDTH - 1; i += 2) {
        str_map[2][i] = num + '0';
        num++;
    }
    str_map[MAP_STR_HEIGHT - 2][0] = ' ';
    str_map[MAP_STR_HEIGHT - 2][MAP_STR_WIDTH - 1] = ' ';
    num = 0;
    for (int i = 2; i < MAP_STR_WIDTH - 1; i += 2) {
        str_map[MAP_STR_HEIGHT - 2][i] = num + '0';
        num++;
    }

    num = 0;
    for (int i = 3; i < MAP_STR_HEIGHT - 2; i++) {
        str_map[i][0] = num + '0';
        num++;
    }
    num = 0;
    for (int i = 3; i < MAP_STR_HEIGHT - 2; i++) {
        str_map[i][MAP_STR_WIDTH - 1] = num + '0';
        num++;
    }

    for (int i = 3; i < MAP_STR_HEIGHT - 2; i++) {
        for (int j = 2; j < MAP_STR_WIDTH - 1; j += 2) {
            str_map[i][j] = '~';
        }
    }
} 

void get_map_coords(int* row, int* col, int str_r, int str_c) {
    int start_r = 3;
    int start_c = 2;
    int end_r = MAP_STR_HEIGHT - 3;
    int end_c = MAP_STR_WIDTH - 3;
    *row = str_r - start_r;
    *col = (str_c - start_c) / 2;
}

void get_str_coords(int row, int col, int* str_r, int* str_c) {
    int start_r = 3;
    int start_c = 2;
    int end_r = MAP_STR_HEIGHT - 3;
    int end_c = MAP_STR_WIDTH - 3;
    *str_r = start_r + row;
    *str_c = start_c + 2 * col;
}

void update_str_map(char** str_map, int** map) {
    int str_r, str_c;
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            get_str_coords(i, j, &str_r, &str_c);
            if (map[i][j] == DEAD) {
                str_map[str_r][str_c] = DEAD_CHAR;
            } else if (map[i][j] == MISSED) {
                str_map[str_r][str_c] = MISSED_CHAR;
            } else if (map[i][j] == SHOOTED) {
                str_map[str_r][str_c] = SHOOTED_CHAR;
            } else {
                continue;
            }
        }
    }
}

void print_my_map() {
    int curr_y = MY_MAP_START_Y;
    int curr_x = MY_MAP_START_X;
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        for (int j = 0; j < MAP_STR_WIDTH; ++j) {
            mvwaddch(MY_MAP_WIN, curr_y, curr_x, MY_STR_MAP[i][j]);
            curr_x++;
        }
        curr_y++;
        curr_x = MY_MAP_START_X;
    }
}

void print_enemy_map() {
    int curr_y = ENEMY_MAP_START_Y;
    int curr_x = ENEMY_MAP_START_X;
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        for (int j = 0; j < MAP_STR_WIDTH; ++j) {
            mvwaddch(ENEMY_MAP_WIN, curr_y, curr_x, ENEMY_STR_MAP[i][j]);
            curr_x++;
        }
        curr_y++;
        curr_x = ENEMY_MAP_START_X;
    }
}

void print_msg(char* msg, int len, bool is_wgetch) {
    int input_x;
    int input_y;
    wclear(INPUT_WIN);
    flushinp();
    echo();
    cbreak();
    curs_set(1);
    getmaxyx(INPUT_WIN, input_y, input_x);
    mvwprintw(INPUT_WIN, input_y / 4 + 1, input_x / 2 - len / 2, msg);
    wrefresh(INPUT_WIN);
    if (is_wgetch) {
        wgetch(INPUT_WIN);
    }
    curs_set(0);
    noecho();
    nocbreak();
}

int parse_to_coords(char* buf, int* row, int* col) {
    *row = -1;
    *col = -1;
    bool is_row = true;
    for (int i = 0; i < MAX_BUF_LEN; ++i) {
        if (buf[i] == ' ' || buf[i] == '\t') {
            continue;
        }
        if ((*row == -1 || *col == -1) && buf[i] >= '0' && buf[i] <= '9') {
            if (is_row) {
                *row = buf[i] - '0';
                is_row = false;
                continue;
            } else {
                *col = buf[i] - '0';
                break;
            }
        } if (buf[i] == '-' && i + 1 < MAX_BUF_LEN && buf[i + 1] == '1') {
            if (*row == -1 && *col == -1) {
                return SURRENDER;
            } else {
                return PARSE_ERR;
            }
        } else {
            return PARSE_ERR;
        }
    }
    if (*row == -1 || *col == -1) {
        return PARSE_ERR;
    }
    return COORDS;
}

void scanf_from_input(char* buf) {
    int input_x;
    int input_y;
    wclear(INPUT_WIN);
    box(INPUT_WIN, 0, 0);
    flushinp();
    echo();
    cbreak();
    curs_set(1);
    getmaxyx(INPUT_WIN, input_y, input_x);
    mvwgetnstr(INPUT_WIN, input_y / 4 + 1, input_x / 2 - 2, buf, MAX_BUF_LEN);
    curs_set(0);
    noecho();
    nocbreak();
}

void refresh_maps(int** my_map, int** enemy_map) {
    update_str_map(MY_STR_MAP, my_map);
    update_str_map(ENEMY_STR_MAP, enemy_map);
    print_my_map();
    print_enemy_map();
    wrefresh(MY_MAP_WIN);
    wrefresh(ENEMY_MAP_WIN);
}

int init_gui(int** my_map, int** enemy_map) {
    initscr();

    MY_STR_MAP = (char**)malloc(MAP_STR_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        MY_STR_MAP[i] = (char*)malloc(MAP_STR_WIDTH * sizeof(char));
    }
    ENEMY_STR_MAP = (char**)malloc(MAP_STR_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        ENEMY_STR_MAP[i] = (char*)malloc(MAP_STR_WIDTH * sizeof(char));
    }

    gen_my_str_map(MY_STR_MAP, my_map);
    gen_enemy_str_map(ENEMY_STR_MAP);

    noecho();
    nocbreak();
    curs_set(0);

    clear();

    int maxx;
    int maxy;
    getmaxyx(stdscr, maxy, maxx);
    MAP_WIN_HEIGHT = (maxy * 9) / 10;
    MAP_WIN_WIDTH = maxx / 3;
    INPUT_WIN_HEIGHT = maxy / 8;
    INPUT_WIN_WIDTH = maxx / 4;

    MY_MAP_START_X = (MAP_WIN_WIDTH - MAP_STR_WIDTH) / 2;
    MY_MAP_START_Y = MAP_WIN_HEIGHT / 4;
    ENEMY_MAP_START_X = (MAP_WIN_WIDTH - MAP_STR_WIDTH) / 2;
    ENEMY_MAP_START_Y = MAP_WIN_HEIGHT / 4;

    MY_MAP_WIN = newwin(MAP_WIN_HEIGHT, MAP_WIN_WIDTH, 0, 0);
    ENEMY_MAP_WIN = newwin(MAP_WIN_HEIGHT, MAP_WIN_WIDTH, 0, 2 * MAP_WIN_WIDTH);
    HELPER_WIN = newwin(MAP_WIN_HEIGHT, MAP_WIN_WIDTH, 0, MAP_WIN_WIDTH);
    int helper_x;
    int helper_y;
    getmaxyx(HELPER_WIN, helper_y, helper_x);
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 1, (helper_x - 14) / 2, "O - YOUR SHIP");
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 3, (helper_x - 14) / 2, "X - DEAD SHIP");
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 5, (helper_x - 20) / 2, "* - HITTING THE SHIP");
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 7, (helper_x - 8) / 2, "# - MISS");
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 9, (helper_x - 16) / 2, "~ - UNKNOWN CELL");
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 11, (helper_x - 22) / 2, "TO SURRENDER ENTER \"-1\"");
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 12, (helper_x - 24) / 2, "IN FIELD FOR INPUT COORDS");
    mvwprintw(HELPER_WIN, MY_MAP_START_X + 14, (helper_x - 26) / 2, "ENTER COORDS IN FIELD BELOW");

    INPUT_WIN = newwin(INPUT_WIN_HEIGHT, INPUT_WIN_WIDTH, MAP_WIN_HEIGHT, 3 * MAP_WIN_WIDTH / 2 - INPUT_WIN_WIDTH / 2);
    box(INPUT_WIN, 0, 0);
    int input_x;
    int input_y;
    getmaxyx(INPUT_WIN, input_y, input_x);
    wrefresh(INPUT_WIN);

    print_my_map();
    print_enemy_map();
    wrefresh(MY_MAP_WIN);
    wrefresh(ENEMY_MAP_WIN);
    wrefresh(HELPER_WIN);

    return ALL_OK;
}

void deinit_gui() {
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        free(MY_STR_MAP[i]);
    }
    free(MY_STR_MAP);   
    for (int i = 0; i < MAP_STR_HEIGHT; ++i) {
        free(ENEMY_STR_MAP[i]);
    }
    free(ENEMY_STR_MAP);  

    wborder(INPUT_WIN, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(INPUT_WIN);
    delwin(MY_MAP_WIN);
    delwin(ENEMY_MAP_WIN);
    delwin(HELPER_WIN);
    delwin(INPUT_WIN);
    endwin();
}
