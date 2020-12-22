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
        send_init_event_to(SOCKET, &my_e);
        recv_init_event_from(SOCKET, &enemy_e);
    } else {
        recv_init_event_from(SOCKET, &enemy_e);
        send_init_event_to(SOCKET, &my_e);
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

// DELETE LATER, JUST FOR TESTING
void print() {
    printf("=================MY_MAP===================\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%-2d ", MY_MAP[i][j]);
        }
        printf("\n");
    }
    printf("==============END_OF_MY_MAP===============\n\n");
    printf("###=============ENEMY_MAP==============###\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%-2d ", ENEMY_MAP[i][j]);
        }
        printf("\n");
    }
    printf("###==========END_OF_ENEMY_MAP==========###\n");
}
// DELETE LATER, JUST FOR TESTING

void host_loop() {
    if (init_host_socket(&CONTEXT, &SOCKET, hostip, hostport) != OK) {
        exit(CLIENT_ERR);
    }

    init_maps(host_enum);
    print();
    
    while (true) {
        loop_event e;
        e.type = loop_event_enum;

        printf("Enter row and col:\n");
        scanf("%d%d", &(e.row), &(e.col));
        send_loop_event_to(SOCKET, &e);
        shoot(ENEMY_ACT_PTR, e.row, e.col);
        if (is_gameover(ENEMY_ACT_PTR)) {
            printf("Congrats, winner!\n");
            break;
        }
        recv_loop_event_from(SOCKET, &e);
        shoot(MY_ACT_PTR, e.row, e.col);
        if (is_gameover(MY_ACT_PTR)) {
            printf("Try again, probably next time you'll win!\n");
            break;
        }
        // JUST FOR TESTING DELETE LATER
        if (e.row == -1) {
            break;
        } 
        // print();
    }

    deinit_maps();

    if (deinit_socket(CONTEXT, SOCKET) != OK) {
        exit(CLIENT_ERR);
    }
}

void client_loop() {
    if (init_client_socket(&CONTEXT, &SOCKET, hostip, hostport) != OK) {
        exit(CLIENT_ERR);
    }

    init_maps(client_enum);
    print();

    while (true) {
        loop_event e;
        e.type = loop_event_enum;

        recv_loop_event_from(SOCKET, &e);
        shoot(MY_ACT_PTR, e.row, e.col);
        if (is_gameover(MY_ACT_PTR)) {
            printf("Try again, probably next time you'll win!\n");
            break;
        }
        printf("Enter row and col:\n");
        scanf("%d%d", &(e.row), &(e.col));
        send_loop_event_to(SOCKET, &e);  
        shoot(ENEMY_ACT_PTR, e.row, e.col);
        if (is_gameover(ENEMY_ACT_PTR)) {
            printf("Congrats, winner!\n");
            break;
        } 
        // JUST FOR TESTING DELETE LATER
        if (e.row == -1) {
            break;
        } 
        // print();    
    }

    deinit_maps();

    if (deinit_socket(CONTEXT, SOCKET) != OK) {
        exit(CLIENT_ERR);
    }
}

void choose_gamemode() {
    if (get_hostinfo(hostname, hostip) != OK) {
        exit(CLIENT_ERR);
    }
    printf("Your host name: %s\n", hostname);
    printf("Your local ip: %s\n", hostip);
    printf("If you want to connect to someone else, enter 1.\nIf you want to be a host, enter 2.\n");
    int mode;
    scanf("%d", &mode);
    if (mode == client_enum) {
        client_loop();
    } else {
        host_loop();
    }
}

int main() {
    choose_gamemode();
    return 0;
}
