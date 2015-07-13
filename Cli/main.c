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

        /*
         * Command parse
        if(split(&command, command_buffer)){
            switch (parse_command(command)){

            }
        }else{
            printf("Command invalid\n");
        }
        */

        command.name = "connect";
        command.argv[0] = "";

        if(sock_fd != -1){
            do_connect(command.argv[0], &sock_fd);
        }else{
            printf("You have been connected to server");
        }

        memset(command_buffer, '\0', COMMAND_LINE);
    }
    return 0;
}
