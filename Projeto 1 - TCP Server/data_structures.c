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
    strncpy(disc->codigo, codigo, CODE_SIZE);
    strncpy(disc->nome, nome, TITLE_SIZE);
    strncpy(disc->ementa, ementa, SYLLABUS_SIZE);
    strncpy(disc->horario, horario, SCHEDULE_SIZE);
    list_add_item(disciplinas, (void*)disc);
}


Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]) {
    struct _list_node *node = disciplinas->items;
    Disciplina *disc;
    while (node)
    {
        disc = (Disciplina *)node->item;
        if (!strncmp(disc->codigo, codigo, CODE_SIZE-1))
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
