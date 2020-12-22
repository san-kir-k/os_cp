#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <zmq.h>

#include "../engine/engine_c_externs.h"
#include "connection_handle.h"
#include "../gui/gui.h"

static char     hostname[STRLEN];
static char     hostport[STRLEN] = "4040";
static char     hostip[STRLEN];
static void*    CONTEXT;
static void*    SOCKET;

void host_loop() {
    // init_host_socket(&CONTEXT, &SOCKET, hostip, hostport);
    if (init_host_socket(&CONTEXT, &SOCKET, "127.0.0.1", hostport) != OK) {
        exit(CLIENT_ERR);
    }
    
    while (true) {
        loop_event e;
        e.col = 1;
        e.row = 42;
        e.type = loop_event_enum;
        printf("Host sent e.col: %d, e.row: %d\n", e.col, e.row);
        send_loop_event_to(SOCKET, &e);
        recv_loop_event_from(SOCKET, &e);
        printf("Host got e.col: %d, e.row: %d\n", e.col, e.row);
        break;
    }

    if (deinit_socket(CONTEXT, SOCKET) != OK) {
        exit(CLIENT_ERR);
    }
}

void client_loop() {
    // init_client_socket(&CONTEXT, &SOCKET, hostip, hostport);
    if (init_client_socket(&CONTEXT, &SOCKET, "127.0.0.1", hostport) != OK) {
        exit(CLIENT_ERR);
    }

    while (true) {
        loop_event e;
        recv_loop_event_from(SOCKET, &e);
        printf("Client got e.col: %d, e.row: %d\n", e.col, e.row);
        e.col = 228;
        e.row = 1337;
        e.type = loop_event_enum;
        printf("Client sent e.col: %d, e.row: %d\n", e.col, e.row);
        send_loop_event_to(SOCKET, &e);
        break;        
    }

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
    if (mode == 1) {
        client_loop();
    } else {
        host_loop();
    }
}

int main() {
    choose_gamemode();
    return 0;
}
