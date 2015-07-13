#include "common.h"
#include "command.h"

int main(int argc, const char *argv[])
{
    char input_buffer[100];
    command_line command;
    int sock_fd;



    memset(input_buffer, '\0', 100);
    while(1){
        printf("Input command: ");
        fgets(input_buffer, 100, stdin);
        size_t command_len = strlen(input_buffer);
        input_buffer[command_len - 1] = '\0';

        /*
         * Command parse
        if(split(&command, input_buffer)){
            switch (parse_command(command)){

            }
        }else{
            printf("Command invalid\n");
        }
        */

        do_connect("127.0.0.1", &sock_fd);

        memset(input_buffer, '\0', 100);
    }
    return 0;
}
