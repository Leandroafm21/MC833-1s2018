#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/*As estruturas de dados utilizadas virão a partir das descrições
encontradas em data_structures.h e das funções em data_structures.c.*/
#include <stdint.h>
#include "protocol_messages.h"

#define NOME_LEN 256
#define MAX_LEN 768
#define CODIGO_LEN 6
#define SCHEDULE_LEN 72

//Gerais
struct _list_node {
    void *item;
    struct _list_node *next;
    struct _list_node *prev;
} ;

typedef struct {
    struct _list_node *items;
    uint16_t size;
} List;


//Específicos
/*typedef struct _aluno_dados {
  char nome[NOME_LEN];
  char login[NOME_LEN];
  char senha[32];
  List disciplinas_cursadas;
} Aluno;*/

/*typedef struct _professor {
    char nome[NOME_LEN];
    char login[NOME_LEN];
    char senha[PWD_SIZE];
    List disciplinas_ministradas;
} Professor;*/

typedef struct _disciplina_dados {
    char codigo[CODIGO_LEN];
    char nome[NOME_LEN];
    char ementa[MAX_LEN];
    char texto_aula[MAX_LEN];
    char horario[SCHEDULE_LEN];
    //Professor *professor;
} Disciplina;

typedef List Professores;
typedef List Disciplinas;

//Funções de acesso

/*
//Professor
void professor_novo(Professores *professores, char nome[], char login[], char senha[]);
Professor *professor_autentica(Professores *professores, char login[], char senha[]);
Professores *professor_cria_lista();
void professor_deleta_lista(Professores *professores);*/

//Disciplinas
Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]);
void disciplina_novo(Disciplinas *disciplinas, char codigo[], char nome[], char ementa[], char horario[]); //, Professor *professor);
Disciplinas *disciplina_cria_lista();
void disciplina_adiciona_em_lista(List *lista, Disciplina *disc);
void disciplina_deleta_lista(Disciplinas *disc);

#endif
