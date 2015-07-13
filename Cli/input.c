#include "common.h"

/*
int split(command_line *command,char * command_buffer){
    char *command_cpy = (char *)malloc(COMMAND_LINE);
    command->name = (char *)malloc(MAX_LENGTH);
    strcpy(command_cpy,line);

    char *buf;
    char *delim=" ";
    buf = strtok(command_cpy,delim);
    strcpy(command->name,buf);
    int count = 0;
    buf=strtok(NULL,delim);

    while(buf&&count < MAX_ARG){
        command->argv[count]=(char *)malloc(MAX_LENGTH);
        strcpy(command->argv[count],buf);
        buf=strtok(NULL,delim);
        count++;
    }
    }

    return 0;
}
*/
void split_to_part(char *command_buffer, char **command_part, int *amount){
    char command_part_buffer[MAX_LENGTH];
    char *command_pointer = command_buffer;
    int flag = 1;
    int counter = 0;
    *amount = 0;

    while(flag){
        if(*command_pointer != ' ' && *command_pointer != '\0'){
            command_part_buffer[counter++] = *command_pointer;
        }else{
            command_part_buffer[counter] = '\0';
            command_part[*amount] = (char *)malloc(strlen(command_part_buffer) + 1);
            strcpy(command_part[*amount], command_part_buffer);
            ++(*amount);
            counter = 0;
        }

        if(*command_pointer == '\0'){
            flag = 0;
        }

        ++command_pointer;
    }
}

int split(command_line *command, char *command_buffer){
    char *command_part[MAX_ARG];
    int amount;

    split_to_part(command_buffer, command_part, &amount);

    command->name = command_part[0];
    for(int i = 1; i < amount; ++i){
        command->argv[i - 1] = command_part[i];
    }

    return 1;

}
