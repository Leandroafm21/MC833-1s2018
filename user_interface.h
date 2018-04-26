#include <stdio.h>
#include <string.h>
#include "protocol_messages.h"

char get_user();
int get_teacher_password(char *password, int access_number);
int build_message(char *buffer, char action, char *specification);
int parse_command(char *command, char *argument);
void get_subject_information(char *subject);
void get_next_class_message(char *message);
int teacher_terminal(char *buffer);
