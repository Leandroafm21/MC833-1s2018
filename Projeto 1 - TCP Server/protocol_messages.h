#ifndef PROTOCOL_MESSAGES_H
#define PROTOCOL_MESSAGES_H

// Funcionalidades na Interface do Cliente
#define AUTHENTICATE 't'
#define REGISTER_SUBJECT 1
#define LIST_SUBJECTS 2
#define SYLLABUS 3
#define INFO 4
#define INFO_ALL 5
#define CHANGE_MESSAGE 6
#define NEXT 7

// Mensagens Gerais
#define AUTHENTICATION_SUCCESS 128u
#define REGISTER_SUBJECT_SUCCESS 127u
#define REGISTER_MESSAGE_SUCCESS 126u

// Mensagens de Erro
#define AUTHENTICATION_FAILED 129u
#define OPERATION_NOT_ALLOWED 130u
#define INVALID_REQUEST 131u

// Outros
#define SEPARATOR 254 // Separador de Informacoes de Disciplinas
#define DELIMITER 255 // Delimitador de dados

// Tamanhos
#define BUFFER_SIZE 16384
#define PWD_SIZE 25
#define COMMAND_SIZE 17
#define CODE_SIZE 6
#define TITLE_SIZE 64
#define SYLLABUS_SIZE 370
#define SCHEDULE_SIZE 72
#define ARGUMENT_SIZE 9
#define SUBJECT_SIZE 512
#define MESSAGE_SIZE 256

#endif
