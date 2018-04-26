#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdint.h>
#include "protocol_messages.h"

struct _list_node {
    void *item;
    struct _list_node *next;
    struct _list_node *prev;
} ;

typedef struct {
    struct _list_node *items;
    uint16_t size;
} List;


typedef struct _disciplina_dados {
    char codigo[CODE_SIZE];
    char nome[TITLE_SIZE];
    char ementa[SYLLABUS_SIZE];
    char texto_aula[MESSAGE_SIZE];
    char horario[SCHEDULE_SIZE];
} Disciplina;

typedef List Disciplinas;

Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]);
void disciplina_novo(Disciplinas *disciplinas, char codigo[], char nome[], char ementa[], char horario[]);
Disciplinas *disciplina_cria_lista();

#endif
