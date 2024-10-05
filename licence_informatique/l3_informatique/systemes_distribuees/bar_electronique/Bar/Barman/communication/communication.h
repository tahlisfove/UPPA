#ifndef UTILS_H
#define UTILS_H

// Inclusion des bibliothèques de C
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#include "handler/handler.h"

#define BUFFER_SIZE 256
#define PIPE_CONFIRM_PATH "/tmp/pipe_confirm"
// Déclaration de la fonction principale

int main(int argc, char *argv[]);

// Fin de la directive de préprocesseur
#endif
