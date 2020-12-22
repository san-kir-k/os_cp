#include "connection_handle.h"

static const int TIME_MS = 100;

int get_hostinfo(char* hostname, char* hostip) {
    char hostbuffer[STRLEN]; 
    char *ipbuffer; 
    struct hostent *host_entry; 

    if (gethostname(hostbuffer, sizeof(hostbuffer)) == -1) { 
        perror("ERROR, gethostname"); 
        return GET_HOST_NAME_ERR;
    } 
  
    host_entry = gethostbyname(hostbuffer); 
    if (host_entry == NULL) { 
        perror("ERROR, gethostbyname"); 
        return GET_HOST_IP_ERR;
    } 

    ipbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0])); 
    strcpy(hostname, hostbuffer);
    strcpy(hostip, ipbuffer);
    return OK;
}

void send_loop_event_to(void* socket, loop_event* e) {
    zmq_msg_t message;
    zmq_msg_init(&message);
    zmq_msg_init_size(&message, sizeof(loop_event));
    memcpy(zmq_msg_data(&message), e, sizeof(loop_event));
    zmq_msg_send(&message, socket, 0);
    zmq_msg_close(&message);
}

void send_init_event_to(void* socket, init_event* e) {
    zmq_msg_t message;
    zmq_msg_init(&message);
    zmq_msg_init_size(&message, sizeof(init_event));
    memcpy(zmq_msg_data(&message), e, sizeof(init_event));
    zmq_msg_send(&message, socket, 0);
    zmq_msg_close(&message);
}

void recv_loop_event_from(void* socket, loop_event* e) {
    zmq_msg_t message;
    zmq_msg_init(&message);
    zmq_msg_init_size(&message, sizeof(loop_event));
    zmq_msg_recv(&message, socket, 0);
    memcpy(e, zmq_msg_data(&message), sizeof(loop_event));
    zmq_msg_close(&message);
}

void recv_init_event_from(void* socket, init_event* e) {
    zmq_msg_t message;
    zmq_msg_init(&message);
    zmq_msg_init_size(&message, sizeof(init_event));
    zmq_msg_recv(&message, socket, 0);
    memcpy(e, zmq_msg_data(&message), sizeof(init_event));
    zmq_msg_close(&message);
}

int init_host_socket(void** context, void** socket, char* ip, char* port) {
    *context = zmq_ctx_new();
    if (*context == NULL) {
        fprintf(stderr, "[HOST %s:%s]: ERROR, zmq_ctx_new\n", ip, port);
        return HOST_CTX_CREATE_ERR;
    }

    void* request = zmq_socket(*context, ZMQ_REQ);
    if (request == NULL) {
        char err_msg[STRLEN];
        sprintf(err_msg, "[HOST %s:%s]: ERROR, zmq_socket", ip, port);
        perror(err_msg);
        return HOST_REQ_CREATE_ERR;
    }

    char socket_name[STRLEN];
    sprintf(socket_name, SOCKET_PATTER"%s:%s", ip, port);
    int br = zmq_bind(request, socket_name); 
    if (br != 0) {
        char err_msg[STRLEN];
        sprintf(err_msg, "[HOST %s:%s]: ERROR, zmq_bind", ip, port);
        perror(err_msg);
        return HOST_REQ_BIND_ERR;
    }
    *socket = request;
    return OK;
}

int init_client_socket(void** context, void** socket, char* ip, char* port) {
    *context = zmq_ctx_new();
    if (*context == NULL) {
        fprintf(stderr, "[CLIENT %s:%s]: ERROR, zmq_ctx_new\n", ip, port);
        return HOST_CTX_CREATE_ERR;
    }

    void* reply = zmq_socket(*context, ZMQ_REP);
    if (reply == NULL) {
        char err_msg[STRLEN];
        sprintf(err_msg, "[CLIENT %s:%s]: ERROR, zmq_socket", ip, port);
        perror(err_msg);
        return HOST_REQ_CREATE_ERR;
    }

    char socket_name[STRLEN];
    sprintf(socket_name, SOCKET_PATTER"%s:%s", ip, port);
    zmq_setsockopt(reply, ZMQ_CONNECT_TIMEOUT, &TIME_MS, sizeof(TIME_MS));
    int cr = zmq_connect(reply, socket_name); 
    if (cr != 0) {
        char err_msg[STRLEN];
        sprintf(err_msg, "[CLIENT %s:%s]: ERROR, zmq_connect", ip, port);
        perror(err_msg);
        return HOST_REQ_BIND_ERR;
    }
    *socket = reply;
    return OK;
}   

int deinit_socket(void* context, void* socket) {
    if (zmq_close(socket) != 0) {
        perror("ERROR, zmq_close");
        return SOCKET_CLOSE_ERR;
    }
    if (zmq_ctx_term(context) != 0) {
        perror("ERROR, zmq_ctx_term");
        return CTX_CLOSE_ERR;        
    }
    return OK;
}
