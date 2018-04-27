#include <stdio.h>
#include <string.h>
#include "protocol_messages.h"

/* Obtem o tipo de usuario - 's' para aluno, 't' para professor */
char get_user();

/* Obtem uma senha de professor */
int get_teacher_password(char *password, int access_number);

/* Constroi uma mensagem com base na requisicao do usuario */
int build_message(char *buffer, char action, char *specification);

/* Separa a opcao inserida em "comando" e "argumento" - todas as opcoes contem exatamente dois campos */
int parse_command(char *command, char *argument);

/* Obtem as informacoes de uma disciplina */
void get_subject_information(char *subject);

/* Obtem uma mensagem para a proxima aula de uma disciplina */
void get_next_class_message(char *message);

/* Interface do usuario */
int teacher_terminal(char *buffer);
int student_terminal(char *buffer);
