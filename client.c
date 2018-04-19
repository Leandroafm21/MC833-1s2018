// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "user_interface.h"

#define PORT 8080

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    int closed;
    char user_type;
    char teacher_password[PWD_SIZE];
    int try_number;
    int finished;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    clear_buffer(buffer, BUFFER_SIZE);
    closed = 0;
    while (closed == 0) {
        printf("Welcome!\n");
        user_type = get_user();
        if (user_type == 't') {
            try_number = 0;
            finished = 0;
            while (finished == 0 && get_teacher_password(teacher_password, try_number++) >= 0) {
                if (build_message(buffer, user_type, teacher_password) < 0) {
                    printf("Message is too big, buffer will overflow!\n");
                    return -1;
                }
                send(sock, buffer, strlen(buffer), 0);
                clear_buffer(buffer, BUFFER_SIZE);

                /* Resposta do servidor pra senha enviada, remover if comentado abaixo */
                valread = read(sock, buffer, 1024);
                if (1) {
                /* if (strcmp(buffer, "authorized") == 0) { */
                    printf("Login was successful. ");
                    while (teacher_terminal(buffer) >= 0) {
                        send(sock, buffer, strlen(buffer), 0);
                        clear_buffer(buffer, BUFFER_SIZE);
                    }
                    finished = 1;
                }
                else {
                    printf("Access denied. Please, try again.\n");
                }
            }
        }
        else {
            if (build_message(buffer, user_type, "\0") < 0) {
                printf("Message is too big, buffer will overflow!\n");
                return -1;
            }
            send(sock, buffer, strlen(buffer), 0);
            clear_buffer(buffer, BUFFER_SIZE);

            printf("Welcome, student!\n");
            while (student_terminal(buffer) >= 0) {
                send(sock, buffer, strlen(buffer), 0);
                clear_buffer(buffer, BUFFER_SIZE);
            }
        }

        printf("System is now closing...\n");
        closed = 1;
        clear_buffer(buffer, BUFFER_SIZE);
        close(sock);
        sleep(3);
    }

    return 0;
}
