//
// Created by mgn on 4/15/18.
//

#ifndef MC833_PROTOCOL_H
#define MC833_PROTOCOL_H

#define DEFAULT_PASSWORD "123456789"

#include "data_structures.h"
#include <netinet/in.h>


typedef struct {
    Disciplinas *disc;
    int autenticado;
    int client_sock;
} Data;

int process_message(char client_message[], Data *data, char server_message[BUFFER_SIZE]);

#endif //MC833_PROTOCOL_H
