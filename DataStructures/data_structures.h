#ifdef SERVER

/*As estruturas de dados utilizadas virão a partir das descrições
encontradas em data_structures.h e das funções em data_structures.c.*/
#include <stdint.h>

#define NOME_LEN 256
#define MAX_LEN 2048
#define CODIGO_LEN 6
#define HASHTABLE_SIZE 256


//Gerais
struct _list_node {
  void *item;
  struct _lista *next;
  struct _lista *prev;
} ;

typedef struct {
  struct _list_node *items;
  uint16_t size;
} List;

typedef struct {
  List items[HASHTABLE_SIZE];
} Small_Hashtable


//Específicos
/*typedef struct _aluno_dados {
  char nome[NOME_LEN];
  char login[NOME_LEN];
  uint8_t senha[32];
  List disciplinas_cursadas;
} Aluno;*/

typedef struct _professor {
  char nome[NOME_LEN];
  char login[NOME_LEN];
  uint8_t senha[32];
  List disciplinas_ministradas;
} Professor;

typedef struct _disciplina_dados {
  char codigo[CODIGO_LEN];
  char nome[NOME_LEN];
  char ementa[MAX_LEN];
  char texto_aula[MAX_LEN];
  List alunos;
  Professor *professor;
} Disciplina;

typedef (Small_Hashtable) Professores;
typedef (Small_Hashtable) Disciplinas;

//Funções de acesso

//Professor
extern void professor_novo(Professores *professores, char nome[], char login[], uint8_t senha[]);
extern Professor *professor_autentica()(Professores *professores, char login[], uint8_t senha[]);

//Disciplinas
extern Disciplina * disciplina_obtem_por_codigo(Disciplinas *disciplinas, char codigo[]);
extern void disciplina_novo(Disciplinas *disciplinas, char codigo[], char nome[], char ementa[], Professor *professor);
extern char* disciplina_obtem_texto(Disciplina *disciplina);
extern void disciplina_atualiza_texto(Disciplina *disciplina, char texto[], Professor professor);
extern char *disciplina_obtem_ementa(Disciplina *disciplina);
extern void disciplina_atualiza_ementa(Disciplina *disciplina, char texto[], Professor professor);

#endif
