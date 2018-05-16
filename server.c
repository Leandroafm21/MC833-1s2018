#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "protocol_messages.h"
#include "server.h"
#include "protocol.h"
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

void clear_buffer(char *buffer, int size)
{
    int i;
    for (i = 0; i < size; i++)
        buffer[i] = 0;
}

#ifdef TCP
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

    socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
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

#else
int server_start_listening(Disciplinas *disc) {
    int sockfd; /* socket */
    int portno; /* port to listen on */
    int clientlen; /* byte size of client's address */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    struct hostent *hostp; /* client host info */
    char client_message[BUFFER_SIZE]; /* message buf */
    char server_message[BUFFER_SIZE]; /* message buf */
    char *hostaddrp; /* dotted decimal host addr string */
    int optval; /* flag value for setsockopt */
    int n; /* message byte size */
    Data data; /*dados de disciplinas e autenticação*/

    data.disc = disc;
    data.autenticado = 0;

    /*
     * socket: create the parent socket
     */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    /* setsockopt: Handy debugging trick that lets
     * us rerun the server immediately after we kill it;
     * otherwise we have to wait about 20 secs.
     * Eliminates "ERROR on binding: Address already in use" error.
     */
    optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
               (const void *) &optval, sizeof(int));

    /*
     * build the server's Internet address
     */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short) PORT);

    if (bind(sockfd, (struct sockaddr *)&serveraddr,
             sizeof(serveraddr)) < 0)
        perror("ERROR on binding");

    /*
     * main loop: wait for a datagram, then echo it
     */
    clientlen = sizeof(clientaddr);
    while (1) {
        bzero(client_message, BUFFER_SIZE);
        bzero(server_message, BUFFER_SIZE);
        n = recvfrom(sockfd, client_message, BUFFER_SIZE, 0,
                     (struct sockaddr *) &clientaddr, &clientlen);
        hostp = gethostbyaddr((const char *) &clientaddr.sin_addr.s_addr,
                              sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        hostaddrp = inet_ntoa(clientaddr.sin_addr);
        process_message(client_message, &data, server_message);

        n = sendto(sockfd, server_message, strlen(server_message), 0,
                   (struct sockaddr *) &clientaddr, clientlen);
    }
}
#endif