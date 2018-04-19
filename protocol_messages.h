#ifndef PROTOCOL_MESSAGES_H
#define PROTOCOL_MESSAGES_H

//Funcionalidades na interface
#define LIST_SUBJECTS 2
#define SYLLABUS 3
#define INFO 4
#define NEXT 7
#define AUTHENTICATE 't'
#define REGISTER_SUBJECT 1
#define CHANGE_MESSAGE 6
#define INFO_ALL 5

//Mensagens Gerais
#define AUTHENTICATION_SUCCESS 128u
#define REGISTER_SUBJECT_SUCCESS 127u
#define REGISTER_MESSAGE_SUCCESS 126u

//Mensagens de erro
#define AUTHENTICATION_FAILED 129u
#define OPERATION_NOT_ALLOWED 130u
#define INVALID_REQUEST 131u


//Outros
#define DELIMITER 255 //delimitador de dados

//Tamanhos
#define BUFFER_SIZE 16384
#define PWD_SIZE 24

#endif
