#include "data_structures.h"
#include <stdio.h>
#include "server.h"

int main (int argc, char **argv)
{
    Disciplinas *disciplinas = disciplina_cria_lista();
    disciplina_novo(disciplinas, "MC833", "Laboratório de Redes", "Ementa do laboratório de redes", "Horario um");
    disciplina_novo(disciplinas, "MC102", "Algoritmos", "Ementa de algoritmos", "Horario dois");
    disciplina_novo(disciplinas, "MC202", "Estruturas de dados", "Ementa de estruturas de dados", "Horairo tres");
    disciplina_novo(disciplinas, "MC302", "Orientação a Objetos", "Ementa de orientação a objetos", "Horario quatro");
//    if (prof)
//        printf("%s %s %s\r\n", prof->login, prof->senha, prof->nome);
//    else
//        printf("not found");
//    Disciplina *disc = disciplina_obtem_por_codigo(disciplinas, "MC833");
//    printf("%s %s %s \r\n", disc->codigo, disc->nome, disc->professor->nome);

    server_start_listening(disciplinas);

    return 0;
}
