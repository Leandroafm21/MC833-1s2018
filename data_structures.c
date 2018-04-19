/*As estruturas de dados utilizadas virão a partir das descrições
encontradas em data_structures.h e das funções em data_structures.c.*/
// leftrotate function definition

#include "data_structures.h"
#include "protocol.h"
#include <stdlib.h>
#include <string.h>


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



/*Public functions*/
/*void professor_novo(Professores *professores, char nome[], char login[], char senha[])
{
    Professor *prof = calloc(1, sizeof(Professor));
    strncpy(prof->nome, nome, NOME_LEN);
    strncpy(prof->login, login, NOME_LEN);
    memcpy(prof->senha, senha, PWD_SIZE); //TODO: Alterar o tamanho da senha e colocar em um define
    list_add_item(professores, (void*)prof);
}

Professor * professor_autentica(Professores *professores, char login[], char senha[])
{
    struct _list_node *node = professores->items;
    Professor *prof;
    int min = strlen(senha) < PWD_SIZE? strlen(senha) : PWD_SIZE;
    while (node) {
        prof = (Professor *)node->item;
        if (!strncmp(login, prof->login, NOME_LEN) && !strncmp(senha, prof->senha, PWD_SIZE))
            return prof;
        node = node->next;
    }
    return NULL;
}

Professores *professor_cria_lista() {
    Professores *prof = list_create();
    return prof;
}

void professor_deleta_lista(Professores *professores)
{
//    struct _list_node *current = professores->items;
//    while (current)
//    {
//        free(current->item);
//    }
//    free(professores);
}*/

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

void disciplina_deleta_lista(Disciplinas *disc)
{
//    struct _list_node *prev, *next;
//    for (int i = 0; i < HASHTABLE_SIZE; i++)
//    {
//        prev = disc->items[i].items;
//        next = prev->next;
//        while (next)
//        {
//            free(prev);
//            prev = next;
//            next = next->next;
//        }
//        free(prev);
//    }
//    free(disc);
}