#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "protocol.h"

static void list_add_item(List *lista, void *item)
{
    struct _list_node *current = lista->items;
    lista->size++;
    if (!current)
    {
        lista->items = (struct _list_node *) calloc(1, sizeof(struct _list_node));
        current = lista->items;
    } else {
        while (current->next)
            current = current->next;
        current->next = (struct _list_node *) calloc(1, sizeof(struct _list_node));
        current->next->prev = current;
        current = current->next;
    }
    current->item = item;
}

static List* list_create()
{
    return (List*) calloc(1, sizeof(List));
}

void disciplina_novo(Disciplinas *disciplinas, char codigo[], char nome[], char ementa[], char horario[])
{
    Disciplina *disc = calloc (1, sizeof(Disciplina));
    strncpy(disc->codigo, codigo, CODIGO_LEN);
    strncpy(disc->nome, nome, NOME_LEN);
    strncpy(disc->ementa, ementa, MAX_LEN);
    strncpy(disc->horario, horario, SCHEDULE_LEN);
    list_add_item(disciplinas, (void*)disc);
}


Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]) {
    struct _list_node *node = disciplinas->items;
    Disciplina *disc;
    while (node)
    {
        disc = (Disciplina *)node->item;
        if (!strncmp(disc->codigo, codigo, CODIGO_LEN-1))
            return disc;
        node = node->next;
    }
    return NULL;
}

Disciplinas *disciplina_cria_lista()
{
    Disciplinas *disc = list_create();
    return disc;
}

void disciplina_adiciona_em_lista(List *lista, Disciplina *disc)
{
    lista->size++;
    struct _list_node *new = calloc(1, sizeof(struct _list_node));
    new->item = disc;
    new->next = NULL;

    struct _list_node *node = lista->items;
    if (!node) {
        lista->items = new;
        new->prev = NULL;
    } else {
        while (node->next) node = node->next;
        node->next = new;
        new->prev = node->next;
    }
}
