#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE 1025
#define PORT 8000
#define COMMAND_LINE 256
#define MAX_LENGTH 64
#define MAX_ARG 8

typedef struct{
    char *name;
    char *argv[MAX_ARG];
}command_line;

int split(command_line *command, char* command_buffer);
int parse_command(command_line command);
int get_dst_filename(const char *src, const char *dst, char *filename);
int is_dir(const char *dst);
