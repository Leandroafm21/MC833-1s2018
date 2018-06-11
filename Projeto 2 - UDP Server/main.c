#include <stdio.h>
#include "data_structures.h"
#include "server.h"

int main (int argc, char **argv)
{
    Disciplinas *disciplinas = disciplina_cria_lista();
    disciplina_novo(disciplinas, "MC833", "Laboratório de Redes", "Ementa de MC833", "Quinta (10:00h-12:00h)");
    disciplina_novo(disciplinas, "MC102", "Algoritmos e Programação de Computadores", "Ementa de MC102", "Horário de MC102");
    disciplina_novo(disciplinas, "MC202", "Estruturas de dados", "Ementa de MC202", "Horário de MC202");
    disciplina_novo(disciplinas, "MC302", "Orientação a Objetos", "Ementa de MC302", "Horário de MC302");

    server_start_listening(disciplinas);

    return 0;
}
