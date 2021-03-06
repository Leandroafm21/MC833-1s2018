#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "protocol_messages.h"
#include "server.h"
#include "protocol.h"

void clear_buffer(char *buffer, int size)
{
    int i;
    for (i = 0; i < size; i++)
        buffer[i] = 0;
}

void *connection_handler(void *socket_desc)
{
    Data *data = (Data*) socket_desc;

    int read_size;
    char server_message[BUFFER_SIZE], client_message[BUFFER_SIZE];

    while ((read_size = recv(data->client_sock, client_message, BUFFER_SIZE, 0)) > 0)
    {
        process_message(client_message, data, server_message);
        write(data->client_sock, server_message, strlen(server_message));
        clear_buffer(client_message, BUFFER_SIZE);
        clear_buffer(server_message, BUFFER_SIZE);
    }

    return 0;
}

int server_start_listening(Disciplinas *disc)
{
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    Data *data;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
        return -1;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
        return -2;

    listen(socket_desc, MAXQUEUELEN);

    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        data = malloc(sizeof(Data));
        data->autenticado = 0;
        data->disc = disc;
        data->client_sock = client_sock;
        if (pthread_create(&thread_id, NULL, connection_handler, (void*) data) < 0)
        {
            free(data);
            return -3;
        }
    }

    if (client_sock < 0)
        return -4;

    return 0;
}
