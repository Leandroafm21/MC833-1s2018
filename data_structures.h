#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdint.h>
#include "protocol_messages.h"

/* No de uma lista */
struct _list_node {
    void *item;
    struct _list_node *next;
    struct _list_node *prev;
} ;

/* Lista */
typedef struct {
    struct _list_node *items;
    uint16_t size;
} List;

/* Informacoes de uma disciplina */
typedef struct _disciplina_dados {
    char codigo[CODE_SIZE];
    char nome[TITLE_SIZE];
    char ementa[SYLLABUS_SIZE];
    char texto_aula[MESSAGE_SIZE];
    char horario[SCHEDULE_SIZE];
} Disciplina;

typedef List Disciplinas;

/* Dada uma lista de disciplinas, retorna um ponteiro para seu no com base no seu codigo enviado */
Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]);

/* Adiciona uma disciplina a lista de disciplinas */
void disciplina_novo(Disciplinas *disciplinas, char codigo[], char nome[], char ementa[], char horario[]);

/* Cria uma lista de disciplinas */
Disciplinas *disciplina_cria_lista();

#endif
