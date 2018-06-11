#ifndef MC833_SERVER_H
#define MC833_SERVER_H

#include "data_structures.h"

#define PORT 9010
#define MAXQUEUELEN 3

/* Trata uma conexao de um cliente, lendo requisicoes e enviando respostas */
void *connection_handler(void *socket_desc);

/* Configura o socket para comecar a ouvir */
int server_start_listening(Disciplinas *disc);

#endif //MC833_SERVER_H
