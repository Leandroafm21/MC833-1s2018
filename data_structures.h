#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/*As estruturas de dados utilizadas virão a partir das descrições
encontradas em data_structures.h e das funções em data_structures.c.*/
#include <stdint.h>
#include "protocol_messages.h"

#define NOME_LEN 256
#define MAX_LEN 2048
#define CODIGO_LEN 6
#define HASHTABLE_SIZE 256
#define MAX_KEY_LEN 256

//Gerais
struct _list_node {
    void *item;
    struct _list_node *next;
    struct _list_node *prev;

    //Para uso da hashtable
    char key[MAX_KEY_LEN] ;
} ;

typedef struct {
    struct _list_node *items;
    uint16_t size;
} List;

typedef struct {
    List items[HASHTABLE_SIZE];
} Small_Hashtable;


//Específicos
/*typedef struct _aluno_dados {
  char nome[NOME_LEN];
  char login[NOME_LEN];
  char senha[32];
  List disciplinas_cursadas;
} Aluno;*/

typedef struct _professor {
    char nome[NOME_LEN];
    char login[NOME_LEN];
    char senha[PWD_SIZE];
    List disciplinas_ministradas;
} Professor;

typedef struct _disciplina_dados {
    char codigo[CODIGO_LEN];
    char nome[NOME_LEN];
    char ementa[MAX_LEN];
    char texto_aula[MAX_LEN];
    Professor *professor;
} Disciplina;

typedef Small_Hashtable Professores;
typedef Small_Hashtable Disciplinas;

//Funções de acesso

//Professor
void professor_novo(Professores *professores, char nome[], char login[], char senha[]);
Professor *professor_autentica(Professores *professores, char login[], char senha[]);
Professores *professor_cria_lista();
void professor_deleta_lista(Professores *professores);

//Disciplinas
Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]);
void disciplina_novo(Disciplinas *disciplinas, char codigo[], char nome[], char ementa[], Professor *professor);
Disciplinas *disciplina_cria_lista();
void disciplina_deleta_lista(Disciplinas *disc);

#endif
