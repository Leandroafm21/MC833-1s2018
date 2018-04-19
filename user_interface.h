#include <stdio.h>
#include <string.h>

#ifndef PWD_SIZE
#define PWD_SIZE 25
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#ifndef COMMAND_SIZE
#define COMMAND_SIZE 17
#endif

#ifndef CODE_SIZE
#define CODE_SIZE 6
#endif

#ifndef SYLLABUS_SIZE
#define SYLLABUS_SIZE 434
#endif

#ifndef SCHEDULE_SIZE
#define SCHEDULE_SIZE 72
#endif

#ifndef ARGUMENT_SIZE
#define ARGUMENT_SIZE 9
#endif

#ifndef SUBJECT_SIZE
#define SUBJECT_SIZE 512
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 256
#endif

#ifndef REGISTER_SUBJECT
#define REGISTER_SUBJECT 1
#endif

#ifndef LIST_SUBJECTS
#define LIST_SUBJECTS 2
#endif

#ifndef SYLLABUS
#define SYLLABUS 3
#endif

#ifndef INFO
#define INFO 4
#endif

#ifndef INFO_ALL
#define INFO_ALL 5
#endif

#ifndef MESSAGE
#define MESSAGE 6
#endif

#ifndef NEXT
#define NEXT 7
#endif

char get_user();
int get_teacher_password(char *password, int access_number);
int build_message(char *buffer, char action, char *specification);
int parse_command(char *command, char *argument);
void get_subject_information(char *subject);
void get_next_class_message(char *message);
int teacher_terminal(char *buffer);
void clear_buffer(char *buffer, int size);
