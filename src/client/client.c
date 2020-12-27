#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <zmq.h>

#include "../engine/engine_c_externs.h"
#include "connection_handle.h"
#include "../gui/gui.h"

static char         hostname[STRLEN];
static char         hostport[STRLEN] = "4040";
static char         hostip[STRLEN];

static void*        CONTEXT;
static void*        SOCKET;

static battlefield* MY_BF_PTR;
static action*      MY_ACT_PTR;
static int**        MY_MAP;
static action*      ENEMY_ACT_PTR;
static int**        ENEMY_MAP;

static const int    MAP_SIZE = 10;

typedef enum {
    host_enum = 2,
    client_enum = 1
} gamemode;

void clear_buf(char* buf) {
    for (int i = 0; i < STRLEN; ++i) {
        buf[i] = ' ';
    }
    buf[STRLEN - 1] = '\0';
}

void init_maps(int gamemode) {
    MY_MAP = (int**)malloc(MAP_SIZE * sizeof(int*));
    for (int i = 0; i < MAP_SIZE; ++i) {
        MY_MAP[i] = (int*)malloc(MAP_SIZE * sizeof(int));
    }

    init_battlefield(&MY_BF_PTR);
    gen_map(MY_BF_PTR);
    get_map_c(MY_BF_PTR, MY_MAP);
    init_action(&MY_ACT_PTR, MY_MAP);    

    init_event my_e;
    my_e.type = init_event_enum;
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            my_e.map[i][j] = MY_MAP[i][j];
        }
    }

    ENEMY_MAP = (int**)malloc(MAP_SIZE * sizeof(int*));
    for (int i = 0; i < MAP_SIZE; ++i) {
        ENEMY_MAP[i] = (int*)malloc(MAP_SIZE * sizeof(int));
    }

    init_event enemy_e;

    if (gamemode == host_enum) {
        if (send_init_event_to(SOCKET, &my_e) == TIME_LIMIT_ERR) {
            printf("Unable to connect to another player...\n");
            exit(CLIENT_ERR);
        }
        if (recv_init_event_from(SOCKET, &enemy_e) == TIME_LIMIT_ERR) {
            printf("Unable to connect to another player...\n");
            exit(CLIENT_ERR);
        }
    } else {
        if (recv_init_event_from(SOCKET, &enemy_e) == TIME_LIMIT_ERR) {
            printf("Unable to connect to another player...\n");
            exit(CLIENT_ERR);
        }
        if (send_init_event_to(SOCKET, &my_e) == TIME_LIMIT_ERR) {
            printf("Unable to connect to another player...\n");
            exit(CLIENT_ERR);
        }
    }

    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            ENEMY_MAP[i][j] = enemy_e.map[i][j];
        }
    }
    init_action(&ENEMY_ACT_PTR, ENEMY_MAP); 
}

void deinit_maps() {
    deinit_action(MY_ACT_PTR);
    deinit_action(ENEMY_ACT_PTR);

    deinit_battlefield(MY_BF_PTR);

    for (int i = 0; i < MAP_SIZE; ++i) {
        free(MY_MAP[i]);
    }
    free(MY_MAP);

    for (int i = 0; i < MAP_SIZE; ++i) {
        free(ENEMY_MAP[i]);
    }
    free(ENEMY_MAP);
} 

bool trap_handle(int r, int c, int* tr, int* tc) {
    if (is_trap(ENEMY_ACT_PTR, r, c)) {
        chose_alive(MY_ACT_PTR, tr, tc);
        return true;
    }
    return false;
}

void host_loop() {
    if (init_host_socket(&CONTEXT, &SOCKET, hostip, hostport) != ALL_OK) {
        exit(CLIENT_ERR);
    }

    init_maps(host_enum);

    init_gui(MY_MAP, ENEMY_MAP);
    
    char buf[STRLEN];
    while (true) {
        loop_event e;
        e.type = loop_event_enum;

        bool is_surr = false;
        while (true) {
            clear_buf(buf);
            scanf_from_input(buf);
            int pv = parse_to_coords(buf, &e.row, &e.col);
            if (pv == COORDS) {
                break;
            } else if (pv == SURRENDER) {
                e.type = surr_event_enum;
                send_loop_event_to(SOCKET, &e);
                recv_loop_event_from(SOCKET, &e);
                print_msg("You have lost!", 12, true);
                is_surr = true;
                break;
            } else {
                print_msg("Invalid coords", 12, true);
            }
        }
        if (is_surr) {
            break;
        }

        shoot(ENEMY_ACT_PTR, e.row, e.col);
        int rt, ct;
        if (trap_handle(e.row, e.col, &rt, &ct)) {
            e.rt = rt;
            e.ct = ct;
            e.type = show_event_enum;
            // show chosed ship in our map
        }
        refresh_maps(MY_MAP, ENEMY_MAP); 
        if (is_gameover(ENEMY_ACT_PTR)) {
            e.type = win_event_enum;
            if (send_loop_event_to(SOCKET, &e) == TIME_LIMIT_ERR) {
                print_msg("Send time limit!", 16, true);    
                break;     
            }
            if (recv_loop_event_from(SOCKET, &e) == TIME_LIMIT_ERR) {
                print_msg("Recv time limit!", 16, true);     
                break;        
            }
            print_msg("Congrats, winner!", 16, true);
            break;
        }
        if (send_loop_event_to(SOCKET, &e) == TIME_LIMIT_ERR) {
            print_msg("Send time limit!", 16, true);
            break;            
        }
        print_msg("Wait your turn...", 16, false);
        if (recv_loop_event_from(SOCKET, &e) == TIME_LIMIT_ERR) {
            print_msg("Recv time limit!", 16, true);
            break;               
        }
        if (e.type == surr_event_enum) {
            print_msg("Congrats, winner!", 16, true);
            break;
        }
        if (e.type == show_event_enum) {
            show_enemy_cell(e.rt, e.ct);
            e.type = loop_event_enum;
        }
        shoot(MY_ACT_PTR, e.row, e.col);
        refresh_maps(MY_MAP, ENEMY_MAP);
        if (e.type == win_event_enum) {
            print_msg("You have lost!", 12, true);
            break;
        }
    }

    deinit_maps();
    deinit_gui();

    if (deinit_socket(CONTEXT, SOCKET) != ALL_OK) {
        exit(CLIENT_ERR);
    }
}

void client_loop(char* to_connect_ip) {
    if (init_client_socket(&CONTEXT, &SOCKET, to_connect_ip, hostport) != ALL_OK) {
        exit(CLIENT_ERR);
    }

    init_maps(client_enum);

    init_gui(MY_MAP, ENEMY_MAP);

    char buf[STRLEN];
    while (true) {
        loop_event e;
        e.type = loop_event_enum;

        print_msg("Wait your turn...", 16, false);
        if (recv_loop_event_from(SOCKET, &e) == TIME_LIMIT_ERR) {
            print_msg("Recv time limit!", 16, true);
            break;   
        }
        if (e.type == win_event_enum) {
            if (send_loop_event_to(SOCKET, &e) == TIME_LIMIT_ERR) {
                print_msg("Send time limit!", 16, true);   
                break;      
            }
            print_msg("You have lost!", 12, true);
            break;
        }
        if (e.type == surr_event_enum) {
            send_loop_event_to(SOCKET, &e);
            print_msg("Congrats, winner!", 16, true);
            break;
        }
        if (e.type == show_event_enum) {
            show_enemy_cell(e.rt, e.ct);
            e.type = loop_event_enum;
        }
        shoot(MY_ACT_PTR, e.row, e.col);
        refresh_maps(MY_MAP, ENEMY_MAP);

        bool is_surr = false;
        while (true) {
            clear_buf(buf);
            scanf_from_input(buf);
            int pv = parse_to_coords(buf, &e.row, &e.col);
            if (pv == COORDS) {
                break;
            } else if (pv == SURRENDER) {
                e.type = surr_event_enum;
                send_loop_event_to(SOCKET, &e);
                print_msg("You have lost!", 12, true);
                is_surr = true;
                break;
            } else {
                print_msg("Invalid coords", 12, true);
            }
        }
        if (is_surr) {
            break;
        }

        shoot(ENEMY_ACT_PTR, e.row, e.col);
        int rt, ct;
        if (trap_handle(e.row, e.col, &rt, &ct)) {
            e.rt = rt;
            e.ct = ct;
            e.type = show_event_enum;
            // show chosed ship in our map
        }
        refresh_maps(MY_MAP, ENEMY_MAP); 
        if (is_gameover(ENEMY_ACT_PTR)) {
            e.type = win_event_enum;
            if (send_loop_event_to(SOCKET, &e) == TIME_LIMIT_ERR) {
                print_msg("Send time limit!", 16, true);    
                break;     
            }
            print_msg("Congrats, winner!", 16, true);
            break;
        }
        if (send_loop_event_to(SOCKET, &e) == TIME_LIMIT_ERR) {
            print_msg("Send time limit!", 16, true);
            break;   
        } 
    }

    deinit_maps();
    deinit_gui();

    if (deinit_socket(CONTEXT, SOCKET) != ALL_OK) {
        exit(CLIENT_ERR);
    }
}

void choose_gamemode() {
    if (get_hostinfo(hostname, hostip) != ALL_OK) {
        exit(CLIENT_ERR);
    }
    printf("Your host name: %s\n", hostname);
    printf("Your local ip: %s\n", hostip);
    printf("If you want to connect to someone else enter 1.\nIf you want to be a host, enter 2.\nTo exit enter 3.\n");
    int mode;
    scanf("%d", &mode);
    if (mode == client_enum) {
        char to_connect_ip[STRLEN];
        printf("Enter host's IP in local network:\n");
        scanf("%s", to_connect_ip);
        client_loop(to_connect_ip);
    } else if (mode == host_enum) {
        host_loop();
    } else {
        return;
    }
}

int main() {
    choose_gamemode();
    return 0;
}
