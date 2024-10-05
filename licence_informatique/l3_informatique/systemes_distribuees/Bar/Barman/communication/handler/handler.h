#ifndef HANDLER_H
#define HANDLER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include "../../controle/utils/utils.h"


#define BUFFER_SIZE 256
#define PIPE_CONFIRM_PATH "/tmp/pipe_confirm"

typedef struct {
    int client_id;
    int client_socket;
    int pipe_fd;
} client_data_t;

void *client_handler(void *arg);

#endif
