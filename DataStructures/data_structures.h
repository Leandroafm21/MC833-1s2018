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
typedef struct _aluno_dados {
  char nome[NOME_LEN];
  char login[NOME_LEN];
  uint8_t senha[32];
  List disciplinas_cursadas;
} Aluno;

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
extern Professor *professor_novo(char nome[], char login[], uint8_t senha[]);
extern void professor_adiciona_disciplina(Professor *professor, Disciplina *disciplina);
extern Professor *professor_autentica()(Professores *professores, char login[], uint8_t senha[]);


//Alunos
extern Aluno *aluno_novo(char nome[], char login[], uint8_t senha[]);
extern void aluno_adiciona_disciplina(Aluno *aluno, Disciplina *disciplina);

//Disciplinas
extern Disciplina *disciplina_novo(char codigo[], char nome[], char ementa[]);

#endif
