#include "common.h"
#include "command.h"

int main(int argc, const char *argv[])
{
    char command_buffer[COMMAND_LINE];
    command_line command;
    int sock_fd = -1;

    memset(command_buffer, '\0', COMMAND_LINE);
    while(1){
        printf("Input command: ");
        fgets(command_buffer, COMMAND_LINE, stdin);
        size_t command_len = strlen(command_buffer);
        command_buffer[command_len - 1] = '\0';

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
                }
            }
            else{
                printf("Command Invalid\n");
            }
       }


        memset(command_buffer, '\0', COMMAND_LINE);
    }
    return 0;
}
