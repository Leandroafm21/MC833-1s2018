//
// Created by mgn on 4/15/18.
//

#include <stdio.h>
#include <string.h>
#include "protocol.h"
#include "protocol_messages.h"
#include "data_structures.h"


int process_message(char client_message[], Data *data, char server_message[BUFFER_SIZE])
{
    char *server_p = server_message;
    char *client_p = client_message+1;
    char login[NOME_LEN], senha[PWD_SIZE];
    struct _list_node *disc_node;
    int i = 0;

    Disciplina *disc;

    //Ajustada inicial para melhor aproveitamento das funções de string:
    for (i = 0; i < BUFFER_SIZE, client_message[i]; i++)
        if (client_message[i] == (char)254)
            client_message[i] = (char) 0;

    switch (client_message[0])
    {
        case LIST_SUBJECTS:
            disc_node = data->disc->items;
            while (disc_node && disc_node->item)
            {
                disc = (Disciplina*) disc_node->item;
                server_p += sprintf(server_p, "%s\n", disc->codigo);
                disc_node = disc_node->next;
            }
            if (server_p == server_message)
                return -1;
            break;
        case SYLLABUS:
            disc = disciplina_obtem_por_codigo(data->disc, client_message+1);
            if (!disc)
                return -1;
            server_p += sprintf(server_p, "%s", disc->ementa);
            break;
        case INFO:
            disc = disciplina_obtem_por_codigo(data->disc, client_message+1);
            if (!disc)
                return -1;
            server_p += sprintf(server_p, "Código: %s\nNome:%s\nHorário:%s\n%s\n", disc->codigo, disc->nome, disc->horario, disc->texto_aula);
            break;
        case NEXT:
            disc = disciplina_obtem_por_codigo(data->disc, client_message+1);
            if (!disc)
                return -1;
            server_p += sprintf(server_p, "%s\n", disc->texto_aula);
            break;
        case AUTHENTICATE:
            if (!strncmp(DEFAULT_PASSWORD, client_message+1, strlen(DEFAULT_PASSWORD)))
            {
                server_message[0] = (char) AUTHENTICATION_SUCCESS;
                server_message[1] = 0;
                data->autenticado = 1;
                return 0;
            }
            server_message[0] = (char) AUTHENTICATION_FAILED;
            server_message[1] = 0;
            return -1;
            break;

        case REGISTER_SUBJECT:
            if (!data->autenticado)
            {
                server_message[0] = (char) OPERATION_NOT_ALLOWED;
                server_message[1] = 0;
                return -1;
            }

            char *codigo, *titulo, *ementa, *horario;
            codigo = client_message+2;
            for (titulo = codigo; *titulo; titulo++);
            titulo++;
            for (ementa = titulo; *ementa; ementa++);
            ementa++;
            for (horario = ementa; *horario; horario++);
            horario++;

            disciplina_novo(data->disc, codigo, titulo, ementa, horario);

            return 0;
            break;
        case CHANGE_MESSAGE:
            if (!data->autenticado)
            {
                server_message[0] = (char) OPERATION_NOT_ALLOWED;
                server_message[1] = 0;
                return -1;
            }

            char codigo_disciplina[CODIGO_LEN];
            memcpy(codigo_disciplina, client_message+1, CODIGO_LEN-1);
            codigo_disciplina[CODIGO_LEN-1] = 0;

            disc = disciplina_obtem_por_codigo(data->disc, codigo_disciplina);
            if (!disc) {
                server_message[0] = (char) INVALID_REQUEST;
                server_message[1] = 0;
                return -1;
            }

            strncmp(disc->texto_aula, client_message+CODIGO_LEN, MAX_LEN);
            return 0;
            break;
        case INFO_ALL:
            disc_node = data->disc->items;
            while (disc_node) {
                disc = (Disciplina*) disc_node->item;
                server_p += sprintf(server_p, "Código: %s\nNome:%s\nHorário:%s\n%s\n\n", disc->codigo, disc->nome,
                                    disc->horario, disc->texto_aula);
                disc_node = disc_node->next;
            }
    }
    return 0;
}