#include "common.h"
#include "command.h"

int main(int argc, const char *argv[])
{
    char command_buffer[COMMAND_LINE];
    command_line command;
    int sock_fd = -1;

    while(1){
        printf("Input command: ");
        memset(command_buffer, '\0', COMMAND_LINE); //Empty command buffer
        fflush(stdin);
        fgets(command_buffer, COMMAND_LINE, stdin);
        command_buffer[strlen(command_buffer) - 1] = '\0';

        if(split(&command, command_buffer) == 0){
            if(strcmp(command.name, "connect") == 0){
                if(sock_fd == -1){
                    do_connect(command.argv[0], &sock_fd);
                }else{
                    printf("You have been connected to server\n");
                }
            }
            else if(strcmp(command.name, "cd") == 0){
                do_cd(command.argv[0]);
            }
            else if(strcmp(command.name, "ls") == 0){
                do_ls(command.argv[0]);
            }
            else if(strcmp(command.name, "show") == 0){
                do_show();
            }
            else if(strcmp(command.name, "get") == 0){
                if(sock_fd == -1){
                    printf("Please connect to a server\n");
                }else{
                    do_get(command.argv[0], command.argv[1], sock_fd);
                }
            }
            else if(strcmp(command.name, "put") == 0){
                if(sock_fd == -1){
                    printf("Please connect to a server\n");
                }else{
                    do_put(command.argv[0], command.argv[1], sock_fd);
                }
            }
            else if(strcmp(command.name, "!cd") == 0){
                if(sock_fd == -1){
                    printf("Please connect to a server\n");
                }else{
                    do_serv_cd(command.argv[0], sock_fd);
                }
            }
            else if(strcmp(command.name, "!ls") == 0){
                if(sock_fd == -1){
                    printf("Please connect to a server\n");
                }else{
                    do_serv_ls(command.argv[0], sock_fd);
                }
            }
            else if(strcmp(command.name, "bye") == 0){
                if(sock_fd == -1){
                    printf("You didn't connected to any server\n");
                }else{
                    bye(sock_fd);
                    sock_fd = -1;
                }
            }
            else if(strcmp(command.name, " ") == 0){
                if(sock_fd == -1){
                    quit();
                }else{
                    printf("Please disconnect to server\n");
                }
            }
            else{
                printf("Command Invalid\n");
            }

            if(command.name){ // Empty and free pointer in command struct
                free(command.name);
                command.name = NULL;
            }
            for(int i = 0; i < MAX_ARG; ++i){

                if(command.argv[i]){
                    free(command.argv[i]);
                    command.argv[i] = NULL;
                }
            }
       }
        printf("\n");

        memset(command_buffer, '\0', COMMAND_LINE);
    }
    return 0;
}
