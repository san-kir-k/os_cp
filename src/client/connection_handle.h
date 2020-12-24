#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <zmq.h>
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <string.h>

#include "defines.h"

typedef enum {
    init_event_enum,
    loop_event_enum,
    surr_event_enum,
    win_event_enum
} e_type;

typedef struct {
    e_type type;
    int map[10][10];
} init_event;

typedef struct {
    e_type type;
    int row;
    int col;
} loop_event;

int     get_hostinfo(char* hostname, char* hostip);
int     send_init_event_to(void* socket, init_event* e);
int     send_loop_event_to(void* socket, loop_event* e);
int     recv_init_event_from(void* socket, init_event* e);
int     recv_loop_event_from(void* socket, loop_event* e);
int     init_host_socket(void** context, void** socket, char* ip, char* port);
int     init_client_socket(void** context, void** socket, char* ip, char* port);                                            
int     deinit_socket(void* context, void* socket); 
