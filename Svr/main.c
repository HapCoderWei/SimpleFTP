#include "common.h"

void *th_func(void *arg);
int main(int argc, char *argv[])
{
    struct sockaddr_in s_addr, c_addr;
    int socket_fd, client_fd;
    int s_addr_len;
    FILE* fd;

    pthread_t pt;
    int res;
    void *retval;
    /* create a socket */
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    s_addr_len = sizeof(s_addr);
    bzero(&s_addr, s_addr_len);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    bind(socket_fd, (struct sockaddr *)&s_addr, s_addr_len);
    listen(socket_fd, 10);          /* max request counts is 10 */

    while (1) {
        client_fd = accept(socket_fd, (struct sockaddr *)&c_addr, &s_addr_len);
        printf("one client connected.\n");
        /* Create a thread to do the request */
        res = pthread_create(&pt, NULL, th_func, (void *)client_fd);
        if(res != 0) {
            perror("Error in create therad ");
            continue;
        }
        /* fd = fopen(buf, "r+"); */
        /* while(fread(sendbuf, sizeof(sendbuf[0]), sizeof(sendbuf), fd)) { */
        /*     send(client_fd, sendbuf, strlen(sendbuf), 0); */
        /* } */
    }
    /* close(socket_fd); */
    return 0;
}
void *th_func(void *arg)
{
    int client_fd = (int)arg;
    char command_buf[MAX_LENGTH] = "";
    char command_arg1[MAX_LENGTH] = "";
    char command_arg2[MAX_LENGTH] = "";

    pthread_detach(pthread_self()); /* pthread_join() */
    while(1) {
        recv(client_fd, command_buf, sizeof(command_buf), 0);
        command_buf[sizeof(command_buf)-1] = '\0';

        if(strncmp(command_buf, "GET", 3) == 0) {
            recv(client_fd, command_arg1, sizeof(command_arg1), 0);
            recv(client_fd, command_arg2, sizeof(command_arg1), 0);
            do_get(command_arg1, command_arg2, client_fd);
        }
        else if(strncmp(command_buf, "PUT", 3) == 0) {
            recv(client_fd, command_arg1, sizeof(command_arg1), 0);
            recv(client_fd, command_arg2, sizeof(command_arg1), 0);
            do_put(command_arg1, command_arg2, client_fd);
        }
        else if(strncmp(command_buf, "CD", 3) == 0) {
            recv(client_fd, command_arg1, sizeof(command_arg1), 0);
            do_cd(command_arg1);
        }
        else if(strncmp(command_buf, "LS", 3) == 0) {
            recv(client_fd, command_arg1, sizeof(command_arg1), 0);
            do_ls(command_arg1);
        }
        else if(strncmp(command_buf, "BYE", 3) == 0) {
            /* BYE BYE */
            //do_get(command_arg1, command_arg2, client_fd);
            close(client_fd);
            pthread_exit(NULL);
            return ;
        }
    }
}