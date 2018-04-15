#include "data_structures.h"
#include <stdio.h>
#include "server.h"

int main (int argc, char **argv)
{
//    Professores *professores = professor_cria_lista();
//    professor_novo(professores, "nome", "login", "senha");
//    professor_novo(professores, "carlos", "carlos", "senha");
//    Professor *prof = professor_autentica(professores, "login", "senha");
//    Disciplinas *disciplinas = disciplina_cria_lista();
//    disciplina_novo(disciplinas, "MC833", "Laboratório de Redes", "Ementa lixosa", prof);
//    if (prof)
//        printf("%s %s %s\r\n", prof->login, prof->senha, prof->nome);
//    else
//        printf("not found");
//    Disciplina *disc = disciplina_obtem_por_codigo(disciplinas, "MC833");
//    printf("%s %s %s \r\n", disc->codigo, disc->nome, disc->professor->nome);

    server_start_listening();

    return 0;
}
