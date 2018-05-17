#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include "user_interface.h"

#define IP_SIZE 16

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    char ip[IP_SIZE];
    int sock = 0, serverlen, valread;
    struct sockaddr_in serveraddr;
    char buffer[BUFFER_SIZE];

    int closed, finished;
    char user_type;
    char teacher_password[PWD_SIZE];
    int try_number;
    struct timeval tv1, tv2, tv3, tv4;

    /* Configuracoes de socket */
    if (argc < 3) {
        printf("Usage: ./client <server IP> <port number>\n");
        exit(EXIT_FAILURE);
    }

    strcpy(ip, argv[1]);

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serveraddr, '0', sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    /* Inicio da interface */
    clear_buffer(buffer, BUFFER_SIZE);
    serverlen = sizeof(serveraddr);
    closed = 0;
    while (closed == 0) {
        printf("Welcome!\n");
        /* Obtencao de usuario */
        user_type = get_user();
        if (user_type == 't') {
            try_number = 0;
            finished = 0;
            /* Autenticacao de professor*/
            while (finished == 0 && get_teacher_password(teacher_password, try_number++) >= 0) {
                if (build_message(buffer, user_type, teacher_password) < 0) {
                    printf("Message is too big, buffer will overflow!\n");
                    return -1;
                }
                sendto(sock, buffer, strlen(buffer), 0,
                       (struct sockaddr *) &serveraddr, serverlen);
                clear_buffer(buffer, BUFFER_SIZE);

                valread = recvfrom(sock, buffer, 1024, 0,
                                   (struct sockaddr *) &serveraddr, &serverlen);
                if (buffer[0] == -AUTHENTICATION_SUCCESS) {
                    printf("Login was successful. ");
                    /* Obtencao de comandos para o servidor, ate finalizado, no caso do professor */
                    while (teacher_terminal(buffer) >= 0) {
                        gettimeofday(&tv1, NULL);
                        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &serveraddr, serverlen);
                        gettimeofday(&tv2, NULL);
                        clear_buffer(buffer, BUFFER_SIZE);
                        gettimeofday(&tv3, NULL);
                        recvfrom(sock, buffer, 16384, 0,
                                 (struct sockaddr *) &serveraddr, &serverlen);
                        gettimeofday(&tv4, NULL);

                        if (buffer[0] == REGISTER_SUBJECT_SUCCESS) {
                            printf("Successfully registered subject.\n");
                        }
                        else if (buffer[0] == REGISTER_MESSAGE_SUCCESS) {
                            printf("Succesfully registered next-class message.\n");
                        }
                        else if (buffer[0] == OPERATION_NOT_ALLOWED || buffer[0] == INVALID_REQUEST) {
                            printf("Something wrong happened.\n");
                        }
                        else {
                            printf("%s\n", buffer);
                        }
                        printf("<Tempo de Execucao: %ld microseconds>\n", (tv2.tv_usec - tv1.tv_usec) + (tv4.tv_usec - tv3.tv_usec));
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
            sendto(sock, buffer, strlen(buffer), 0,
                   (struct sockaddr *) &serveraddr, serverlen);
            clear_buffer(buffer, BUFFER_SIZE);

            printf("Welcome, student!\n");
            /* Obtencao de comandos para o servidor, ate finalizado, no caso do aluno */
            while (student_terminal(buffer) >= 0) {
                sendto(sock, buffer, strlen(buffer), 0,
                       (struct sockaddr *) &serveraddr, serverlen);
                clear_buffer(buffer, BUFFER_SIZE);
                valread = recvfrom(sock, buffer, 16384, 0,
                                   (struct sockaddr *) &serveraddr, &serverlen);
                printf("%s\n", buffer);
                clear_buffer(buffer, BUFFER_SIZE);
            }
        }

        /* Finalizacao */
        printf("System is now closing...\n");
        closed = 1;
        clear_buffer(buffer, BUFFER_SIZE);
        close(sock);
        sleep(3);
    }

    return 0;
}
