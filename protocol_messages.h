#ifndef PROTOCOL_MESSAGES_H
#define PROTOCOL_MESSAGES_H

//Funcionalidades na interface
#define LIST_SUBJECTS 0u
#define SYLLABUS 1u
#define INFO 2u
#define NEXT 3u
#define AUTHENTICATE 4u
#define REGISTER_SUBJECT 5u
#define MESSAGE 6u

//Mensagens Gerais
#define AUTHENTICATION_SUCCESS 128u
#define REGISTER_SUBJECT_SUCCESS 127u
#define REGISTER_MESSAGE_SUCCESS 126u

//Mensagens de erro
#define AUTHENTICATION_FAILED 255u
#define OPERATION_NOT_ALLOWED 254u
#define INVALID_REQUEST 253u

//Tamanhos
#define BUFFER_SIZE 1024
#define PWD_SIZE 24

#endif
