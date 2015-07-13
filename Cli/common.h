#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1025
#define PORT 8000
#define COMMAND_LINE 256
#define MAX_LENGTH
#define MAX_ARG 8

typedef struct{
    char *name;
    char *argv[MAX_ARG];
}command_line;

int split(command_line *command, char command_buffer[]);
int parse_command(command_line command);
