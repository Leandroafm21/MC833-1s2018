//
// Created by mgn on 4/15/18.
//
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include "protocol_messages.h"
#include "server.h"

void *connection_handler(void *socket_desc)
{
    int sock = *(int*) socket_desc;
    int read_size;
    char server_message[BUFFER_SIZE], client_message[BUFFER_SIZE];

    strcpy(server_message, "HELLO");

    write(sock, server_message, strlen(server_message));
    while ((read_size = recv(sock, client_message, BUFFER_SIZE, 0)) > 0)
    {
        //Do logic
        write(sock, server_message, strlen(server_message));
    }

    return 0;

}

int server_start_listening()
{
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    //Preparing stuff
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
        return -1;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    //Binding
    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
        return -2;

    //Listening
    listen(socket_desc, MAXQUEUELEN);

    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        if (pthread_create(&thread_id, NULL, connection_handler, (void*) &client_sock) < 0)
        {
            return -3;
        }
    }

    if (client_sock < 0)
        return -4;



    return 0;
}