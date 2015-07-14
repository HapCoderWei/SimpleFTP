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
    if(command_part[0] == NULL){
        command_part[0] = (char *)malloc(2);
        strcpy(command_part[0], "A");
        printf("is space:%s\n", command_part[0]);
    }
}

int split(command_line *command, char *command_buffer){
    if(command == NULL || command_buffer == NULL){
        return -1;
    }

    char *command_part[MAX_ARG];
    int amount;

    command->name = NULL;
    for(int i = 0; i < MAX_ARG; ++i){
        command->argv[i] = NULL;
    }
    split_to_part(command_buffer, command_part, &amount);

    command->name = command_part[0];
    for(int i = 1; i < amount; ++i){
        command->argv[i - 1] = command_part[i];
    }

    return 0;
}

int get_dst_filename(const char *src, const char *dst, char *filename){
    if(is_dir(dst)){
        char src_cpy[MAX_LENGTH];
        strcpy(src_cpy, src);
        char *token = strtok(src_cpy, " ");
        char filename_tmp[MAX_LENGTH];
        while(token){
            strcpy(filename_tmp, token);
            token = strtok(NULL, " ");
        }

        strcpy(filename, dst);
        int filename_len = strlen(filename);
        if(filename[filename_len - 1] != '/'){
            filename[filename_len] = '/';
            filename[filename_len + 1] = '\0';
            strcat(filename, filename_tmp);
        }

    }else{
        strcpy(filename, dst);
    }
    return 0;
}

int is_dir(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    if((path_stat.st_mode & S_IFMT) == S_IFDIR){
        return 1;
    }else{
        return 0;
    }
}
