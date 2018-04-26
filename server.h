#ifndef MC833_SERVER_H
#define MC833_SERVER_H

#include "data_structures.h"

#define PORT 9010
#define MAXQUEUELEN 3

void *connection_handler(void *socket_desc);
int server_start_listening(Disciplinas *disc);

#endif //MC833_SERVER_H
