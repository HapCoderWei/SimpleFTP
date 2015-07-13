#include "common.h"
void split_to_part(char *command_buffer, char **command_part, int *amount){
    char command_part_buffer[MAX_LENGTH];
    char *command_pointer = command_buffer;
    int end_flag = 1,start_flag = 0;
    int counter = 0;
    *amount = 0;

    while(end_flag){
        if(*command_pointer != ' ' && *command_pointer != '\0'){
            command_part_buffer[counter++] = *command_pointer;
            start_flag = 1;
        }else{
            if(start_flag){
                command_part_buffer[counter] = '\0';
                command_part[*amount] = (char *)malloc(strlen(command_part_buffer) + 1);
                strcpy(command_part[*amount], command_part_buffer);
                ++(*amount);
                counter = 0;
                start_flag = 0;
            }
        }

        if(*command_pointer == '\0'){
            end_flag = 0;
        }

        ++command_pointer;
    }
}

int split(command_line *command, char *command_buffer){
    if(command == NULL || command_buffer == NULL){
        return -1;
    }

    char *command_part[MAX_ARG];
    int amount;

    split_to_part(command_buffer, command_part, &amount);

    command->name = command_part[0];
    for(int i = 1; i < amount; ++i){
        command->argv[i - 1] = command_part[i];
    }

    return 0;
}
