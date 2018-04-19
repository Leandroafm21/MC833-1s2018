#include "user_interface.h"

char get_user() {
    char type = '\0';

    while (type != 's' && type != 't') {
        printf("Please, enter \'s\' if you're a student or \'t\' if you're a teacher: ");
        scanf(" %c", &type);

        if (type != 's' && type != 't') {
            printf("Sorry, try again.\n");
        }
    }

    return type;
}

int get_teacher_password(char *password, int access_number) {
    if (access_number == 0) {
        printf("Welcome, Teacher!\n");
    }
    else if (access_number > 3) {
        printf("Three wrong guesses, exiting to prevent attacks.\n");
        return -1;
    }

    printf("Please, enter your password (max: 24 characters): ");
    scanf(" %[^\n]s", password);

    return access_number;
}

int build_message(char *buffer, char action, char *specification) {
    if (specification[0] != '\0') {
        if (strlen(specification) < BUFFER_SIZE) {
            buffer[0] = action; buffer[1] = '\0';
            strcat(buffer, specification);
            return 0;
        }
    }
    else {
        buffer[0] = action;
        buffer[1] = '\0';
        return 0;
    }

    return -1;
}

int parse_command(char *command, char *argument) {
    int i, j;

    i = 0;
    while (command[i] != ' ') i++;
    i++;
    command[i-1] = '\0';

    if (strcmp(command, "register") != 0 && strcmp(command, "list") != 0
        && strcmp(command, "syllabus") != 0 && strcmp(command, "info") != 0
        && strcmp(command, "message") != 0 && strcmp(command, "next") != 0
        && strcmp(command, "exit") != 0) {
        return -1;
    }

    j = 0;
    while (command[i] != '\0') argument[j++] = command[i++];
    argument[j] = '\0';

    return 0;
}

void get_subject_information(char *subject) {
    char code[CODE_SIZE];
    char title[TITLE_SIZE];
    char syllabus[SYLLABUS_SIZE];
    char schedule[SCHEDULE_SIZE];
    int i;

    printf("  Enter the subject code:\n");
    printf(">> ");
    scanf(" %[^\n]s", code);
    printf("  Enter the subject title:\n");
    printf(">> ");
    scanf(" %[^\n]s", title);
    printf("  Enter the subject syllabus:\n");
    printf(">> ");
    scanf(" %[^\n]s", syllabus);
    printf("  Enter the subject schedule:\n");
    printf(">> ");
    scanf(" %[^\n]s", schedule);

    strcpy(subject, "_");
    strcat(subject, code);
    strcat(subject, "_");
    strcat(subject, title);
    strcat(subject, "_");
    strcat(subject, syllabus);
    strcat(subject, "_");
    strcat(subject, schedule);

    for (i = 0; i < strlen(subject); i++) {
        if (subject[i] == '_') {
            subject[i] = '\0';
        }
    }
}

void get_next_class_message(char *message) {
    printf("  Enter the desired one-line message:\n");
    printf(">> ");
    scanf(" %[^\n]s", message);
}

int teacher_terminal(char *buffer) {
    char command[COMMAND_SIZE];
    char argument[ARGUMENT_SIZE];
    char subject_information[SUBJECT_SIZE];
    char class_message[MESSAGE_SIZE];
    int try_number;

    try_number = 0;
    do {
        clear_buffer(command, COMMAND_SIZE);
        clear_buffer(argument, ARGUMENT_SIZE);
        if (try_number > 0) {
            printf("Wrong formated command.\n");
        }
        try_number++;

        printf("Please, enter:\n");
        printf("  register subject - to register a subject;\n");
        printf("  list subjects - to list all registered subjects;\n");
        printf("  syllabus <subject code> - to show the syllabus of a specific subject;\n");
        printf("  info <subject code> - to show the informations of a specific subject\n");
        printf("  info all - to list the informations of all registered subjects;\n");
        printf("  message <subject code> - to write a message to the next class of a specific subject you teach;\n");
        printf("  next <subject code> - to show the message of the next class of a specific subject;\n");
        printf("  exit system - to exit the system;\n");
        printf(">> ");
        scanf(" %[^\n]s", command);
    } while (parse_command(command, argument) < 0);

    clear_buffer(buffer, BUFFER_SIZE);

    if (strcmp(command, "register") == 0) {
        buffer[0] = REGISTER_SUBJECT;
        clear_buffer(subject_information, SUBJECT_SIZE);
        get_subject_information(subject_information);
        strcat(buffer, subject_information);
        return 0;
    }
    else if (strcmp(command, "list") == 0) {
        buffer[0] = LIST_SUBJECTS;
        return 0;
    }
    else if (strcmp(command, "syllabus") == 0) {
        buffer[0] = SYLLABUS;
        strcat(buffer, argument);
        return 0;
    }
    else if (strcmp(command, "info") == 0) {
        if (strcmp(argument, "all") == 0) {
            printf("Info all\n");
            buffer[0] = INFO_ALL;
            printf("buffer = %s\n", buffer);
        }
        else {
            buffer[0] = INFO;
            strcat(buffer, argument);
        }
        return 0;
    }
    else if (strcmp(command, "message") == 0) {
        buffer[0] = MESSAGE;
        strcat(buffer, argument);
        clear_buffer(class_message, MESSAGE_SIZE);
        get_next_class_message(class_message);
        strcat(buffer, class_message);
        return 0;
    }
    else if (strcmp(command, "next") == 0) {
        printf("Next MC102\n");
        buffer[0] = NEXT;
        strcat(buffer, argument);
        printf("buffer = %s\n", buffer);
        return 0;
    }
    else if (strcmp(command, "exit") == 0) {
        return -1;
    }

    return 0;
}

int student_terminal(char *buffer) {
    char command[COMMAND_SIZE];
    char argument[ARGUMENT_SIZE];
    int try_number;

    try_number = 0;
    do {
        clear_buffer(command, COMMAND_SIZE);
        clear_buffer(argument, ARGUMENT_SIZE);
        if (try_number > 0) {
            printf("Wrong formated command.\n");
        }
        try_number++;

        printf("Please, enter:\n");
        printf("  list subjects - to list all registered subjects;\n");
        printf("  syllabus <subject code> - to show the syllabus of a specific subject;\n");
        printf("  info <subject code> - to show the informations of a specific subject\n");
        printf("  info all - to list the informations of all registered subjects;\n");
        printf("  next <subject code> - to show the message of the next class of a specific subject;\n");
        printf("  exit system - to exit the system;\n");
        printf(">> ");

        scanf(" %[^\n]s", command);
    } while (parse_command(command, argument) < 0);

    clear_buffer(buffer, BUFFER_SIZE);

    if (strcmp(command, "list") == 0) {
        buffer[0] = LIST_SUBJECTS;
        return 0;
    }
    else if (strcmp(command, "syllabus") == 0) {
        buffer[0] = SYLLABUS;
        strcat(buffer, argument);
        return 0;
    }
    else if (strcmp(command, "info") == 0) {
        if (strcmp(argument, "all") == 0) {
            buffer[0] = INFO_ALL;
        }
        else {
            buffer[0] = INFO;
            strcat(buffer, argument);
        }
        return 0;
    }
    else if (strcmp(command, "next") == 0) {
        buffer[0] = NEXT;
        strcat(buffer, argument);
        return 0;
    }
    else if (strcmp(command, "exit") == 0) {
        return -1;
    }

    /* isso pode ser um problema... */
    return 0;
}

void clear_buffer(char *buffer, int size) {
    int i;

    for (i = 0; i < size; i++) {
        buffer[i] = '\0';
    }
}
